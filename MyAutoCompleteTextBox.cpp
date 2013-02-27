#include "stdafx.h"
#include "MyAutoCompleteTextBox.h"
#include "TextLengthTrigger.h"
#include "ShortCutTrigger.h"
#include "Messages.h"

using namespace jpb;

MyAutoCompleteTextBox::WinHook::WinHook(MyAutoCompleteTextBox^ tbox) {
	this->tb = tbox;
}

/*
 * Look for any kind of mouse activity that is not in the
 * text box itself, and hide the popup if it is visible.
 */
void MyAutoCompleteTextBox::WinHook::WndProc(Message% m) {

	switch (m.Msg)	{
		case Win32::Messages::WM_LBUTTONDOWN:
		case Win32::Messages::WM_LBUTTONDBLCLK:
		case Win32::Messages::WM_MBUTTONDOWN:
		case Win32::Messages::WM_MBUTTONDBLCLK:
		case Win32::Messages::WM_RBUTTONDOWN:
		case Win32::Messages::WM_RBUTTONDBLCLK:
		case Win32::Messages::WM_NCLBUTTONDOWN:
		case Win32::Messages::WM_NCMBUTTONDOWN:
		case Win32::Messages::WM_NCRBUTTONDOWN:
		{
			// Lets check to see where the event took place
			Form^ form = tb->FindForm();
			Point p = form->PointToScreen( Point( ( int )m.LParam ) );
			Point p2 = tb->PointToScreen( Point( 0, 0 ) );
			Rectangle^ rect = gcnew Rectangle( p2, tb->Size );
			// Hide the popup if it is not in the text box
			if ( ! rect->Contains( p ) ) {
				//tb->HideList();
			}
		}
			break;
		case Win32::Messages::WM_SIZE:
		case Win32::Messages::WM_MOVE:
		{
			tb->HideList();
		}
			break;
		// This is the message that gets sent when a childcontrol gets activity
		case Win32::Messages::WM_PARENTNOTIFY:
		{
			switch ((int)m.WParam) {
				case Win32::Messages::WM_LBUTTONDOWN:
				case Win32::Messages::WM_LBUTTONDBLCLK:
				case Win32::Messages::WM_MBUTTONDOWN:
				case Win32::Messages::WM_MBUTTONDBLCLK:
				case Win32::Messages::WM_RBUTTONDOWN:
				case Win32::Messages::WM_RBUTTONDBLCLK:
				case Win32::Messages::WM_NCLBUTTONDOWN:
				case Win32::Messages::WM_NCMBUTTONDOWN:
				case Win32::Messages::WM_NCRBUTTONDOWN:
				{
					// Same thing as before
					Form^ form = tb->FindForm();
					Point p = form->PointToScreen( Point( ( int ) m.LParam ) );
					Point p2 = tb->PointToScreen( Point( 0, 0 ) );
					Rectangle^ rect = gcnew Rectangle( p2, tb->Size );
					if ( ! rect->Contains( p ) ) {
						tb->HideList();
					} else {
						tb->ShowList();
					}
				} break;
			}
		} break;
	}
				
	__super::WndProc( m );
}

void MyAutoCompleteTextBox::WndProc(Message% m) {

	switch (m.Msg)	{
		case Win32::Messages::WM_LBUTTONDOWN:
			{
			this->ShowList();
			}
	}
	__super::WndProc( m );
}

MyAutoCompleteTextBox::MyAutoCompleteTextBox(void) {
	this->mode = EntryMode::Text;
	this->items = gcnew AutoCompleteEntryCollection();
	this->triggers = gcnew AutoCompleteTriggerCollection();
	this->popOffset = gcnew Point(12, 0);
	this->popSelectBackColor = SystemColors::Highlight;
	this->popSelectForeColor = SystemColors::HighlightText;
	this->triggersEnabled = true;

	// Create the form that will hold the list
	this->popup = gcnew Form();
	this->popup->StartPosition = FormStartPosition::Manual;
	this->popup->ShowInTaskbar = false;
	this->popup->FormBorderStyle = FormBorderStyle::None;
	this->popup->TopMost = true;
	this->popup->Deactivate += gcnew System::EventHandler(this, &MyAutoCompleteTextBox::Popup_Deactivate);

	// Create the list box that will hold mathcing items
	this->list = gcnew ListBox();
	this->list->Cursor = Cursors::Hand;
	this->list->BorderStyle = System::Windows::Forms::BorderStyle::None;
	this->list->SelectedIndexChanged += gcnew EventHandler(this, &MyAutoCompleteTextBox::List_SelectedIndexChanged);
	this->list->MouseDown += gcnew MouseEventHandler(this, &MyAutoCompleteTextBox::List_MouseDown);
	this->list->ItemHeight = 14;
	this->list->DrawMode = DrawMode::OwnerDrawFixed;
	this->list->DrawItem += gcnew DrawItemEventHandler(this, &MyAutoCompleteTextBox::List_DrawItem);
	this->list->Dock = DockStyle::Fill;
		
	// Add the list box to the popup form
	this->popup->Controls->Add(this->list);

	// Add default triggers.
	this->triggers->Add(gcnew TextLengthTrigger(2));
	this->triggers->Add(gcnew ShortCutTrigger(Keys::LButton, TriggerState::SelectAndConsume));
	this->triggers->Add(gcnew ShortCutTrigger(Keys::Enter, TriggerState::SelectAndConsume));
	this->triggers->Add(gcnew ShortCutTrigger(Keys::Tab, TriggerState::Select));
	this->triggers->Add(gcnew ShortCutTrigger(Keys::Control | Keys::Space, TriggerState::ShowAndConsume));
	this->triggers->Add(gcnew ShortCutTrigger(Keys::Escape, TriggerState::HideAndConsume));
}

bool MyAutoCompleteTextBox::DefaultCmdKey(Message% msg, Keys keyData) {
	bool val = __super::ProcessCmdKey( msg, keyData );

	if (this->TriggersEnabled) {
		switch (this->triggers->OnCommandKey( keyData ) ) {
			case TriggerState::ShowAndConsume:
			{
				val = true;
				this->ShowList();
			} break;
			case TriggerState::Show:
			{
				this->ShowList();
			} break;
			case TriggerState::HideAndConsume:
			{
				val = true;
				this->HideList();
			} break;
			case TriggerState::Hide:
			{
				this->HideList();
			} break;
			case TriggerState::SelectAndConsume:
			{
				if (this->popup->Visible == true) {
					val = true;
					this->SelectCurrentItem();
				}
			} break;
			case TriggerState::Select:
			{
				if (this->popup->Visible == true) {
					this->SelectCurrentItem();
				}
			} break;
			default:
				break;
		}
	}

	return val;
}

void MyAutoCompleteTextBox::ShowList() {
	if ( this->popup->Visible == false ) {
		this->list->SelectedIndex = -1;
		this->UpdateList();
		Point p = this->PointToScreen( Point( 0, 0 ) );
		p.X += this->PopupOffset->X;
		p.Y += this->Height + this->PopupOffset->Y;
		this->popup->Location = p;
		if (this->list->Items->Count > 0) {
			this->popup->Show();
			if ( this->hook == nullptr ) {
				this->hook = gcnew WinHook( this );
				this->hook->AssignHandle(this->FindForm()->Handle);
			}
			this->Focus();
		}
	} else {
		this->UpdateList();
	}
}

void MyAutoCompleteTextBox::SelectCurrentItem() {
	if (this->list->SelectedIndex == -1) {
		return;
	}

	this->Focus();
	this->Text = this->list->SelectedItem->ToString();
	if (this->Text->Length > 0) {
		this->SelectionStart = this->Text->Length;
	}

	this->HideList();
}

void MyAutoCompleteTextBox::List_DrawItem(Object^ sender, DrawItemEventArgs^ e) {
	Color bColor = e->BackColor;
	if (e->State == DrawItemState::Selected) {
		e->Graphics->FillRectangle( gcnew SolidBrush( this->PopupSelectionBackColor ), e->Bounds );
		e->Graphics->DrawString( this->list->Items[e->Index]->ToString(), e->Font, gcnew SolidBrush( this->PopupSelectionForeColor ), e->Bounds, StringFormat::GenericDefault);
	} else {
		e->DrawBackground();
		e->Graphics->DrawString(this->list->Items[e->Index]->ToString(), e->Font, gcnew SolidBrush( e->ForeColor ), e->Bounds, StringFormat::GenericDefault);
	}
}

bool MyAutoCompleteTextBox::ProcessCmdKey(Message% msg, Keys keyData) {
	switch (keyData) {
		case Keys::Up:
		{
			this->Mode = EntryMode::List;
			if (this->list->SelectedIndex > 0)
			{
				this->list->SelectedIndex--;
			}
			return true;
		} break;
		case Keys::Down:
		{
			this->Mode = EntryMode::List;
			if (this->list->SelectedIndex < this->list->Items->Count - 1)
			{
				this->list->SelectedIndex++;
			}
			return true;
		} break;
		default:
		{
			return DefaultCmdKey(msg, keyData);
		} break;
	}
}

void MyAutoCompleteTextBox::OnTextChanged(EventArgs^ e) {
	__super::OnTextChanged (e);

	if (this->TriggersEnabled) {
		switch (this->triggers->OnTextChanged(this->Text))
		{
			case TriggerState::Show:
			{
				this->ShowList();
			} break;
			case TriggerState::Hide:
			{
				this->HideList();
			} break;
			default:
			{
				this->UpdateList();
			} break;
		}
	}
}

void MyAutoCompleteTextBox::OnLostFocus(EventArgs^ e) {

	__super::OnLostFocus (e);

	if ( !( this->Focused || this->popup->Focused || this->list->Focused ) ) {
		this->HideList();
	}
}

void MyAutoCompleteTextBox::UpdateList() {
	Object^ selectedItem = this->list->SelectedItem;

	this->list->Items->Clear();
	this->list->Items->AddRange(this->FilterList(this->Items)->ToObjectArray());

	if (selectedItem != nullptr && this->list->Items->Contains(selectedItem)) {
		EntryMode oldMode = this->Mode;
		this->Mode = EntryMode::List;
		this->list->SelectedItem = selectedItem;
		this->Mode = oldMode;
	}

	if (this->list->Items->Count == 0) {
		this->HideList();
	} else {
		int visItems = this->list->Items->Count;
		if (visItems > 8)
			visItems = 8;

		this->popup->Height = (visItems * this->list->ItemHeight) + 2;
		switch (this->BorderStyle) {
			case System::Windows::Forms::BorderStyle::FixedSingle:
			{
				this->popup->Height += 2;
			} break;
			case System::Windows::Forms::BorderStyle::Fixed3D:
			{
				this->popup->Height += 4;
			} break;
			case System::Windows::Forms::BorderStyle::None:
			default:
			{
			} break;
		}
				
		this->popup->Width = this->PopupWidth;

		if (this->list->Items->Count > 0 && this->list->SelectedIndex == -1) {
			EntryMode oldMode = this->Mode;
			this->Mode = EntryMode::List;
			this->list->SelectedIndex = 0;
			this->Mode = oldMode;
		}
	}
}

AutoCompleteEntryCollection^ MyAutoCompleteTextBox::FilterList(AutoCompleteEntryCollection^ list) {
	AutoCompleteEntryCollection^ newList = gcnew AutoCompleteEntryCollection();
	array<AutoCompleteEntry^>^ listArray = static_cast< array<AutoCompleteEntry^>^ >( list->ToObjectArray() );

	for (int i = 0; i < listArray->Length; i++ ) {
		AutoCompleteEntry^ entry = listArray[i];
		String^ match = entry->MatchStrings;
		if (match->ToUpper()->StartsWith(this->Text->ToUpper())) {
			newList->Add(entry);
			break;
		}
	}

	//for each (IAutoCompleteEntry^ entry in list) {
	//	for each (String^ match in entry->MatchStrings) {
	//		if (match->ToUpper()->StartsWith(this->Text->ToUpper())) {
	//			newList->Add(entry);
	//			break;
	//		}
	//	}
	//}
	return newList;
}

void MyAutoCompleteTextBox::List_SelectedIndexChanged(Object^ sender, EventArgs^ e) {
	if (this->Mode != EntryMode::List) {
		this->SelectCurrentItem();
	}
}

void MyAutoCompleteTextBox::HideList() {
	this->Mode = EntryMode::Text;
	if (this->hook != nullptr)
		this->hook->ReleaseHandle();
	this->hook = nullptr;
	this->popup->Hide();
}
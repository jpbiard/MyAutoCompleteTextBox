#pragma once

#include "AutoCompleteEntryCollection.h"
#include "AutoCompleteTriggerCollection.h"
#include "IAutoCompleteEntry.h"
#include "EntryMode.h"

namespace jpb {

	using namespace System;
	using namespace System::Collections;
	using namespace System::ComponentModel;
	using namespace System::Drawing;
	using namespace System::Data;
	using namespace System::Windows::Forms;

	public ref class MyAutoCompleteTextBox : System::Windows::Forms::TextBox
	{
		ref class WinHook : public System::Windows::Forms::NativeWindow {

			public:
				WinHook(MyAutoCompleteTextBox^);

			private:
				MyAutoCompleteTextBox^ tb;

			protected:
				virtual void WndProc(Message% m) override;
		};

	public:
		MyAutoCompleteTextBox(void);

	public:
		virtual void HideList();

	private: ListBox^ list;
	protected: Form^ popup;
	private: WinHook^ hook;
	private: EntryMode mode;
	private: AutoCompleteEntryCollection^ items;
	private: AutoCompleteTriggerCollection^ triggers;
	private: Point^ popOffset;
	private: Color popSelectBackColor;
	private: Color popSelectForeColor;
	private: bool triggersEnabled;

	public:
		property EntryMode Mode {
			EntryMode get() {
				return this->mode;
			}
			void set( EntryMode value ) {
				this->mode = value;
			}
		}

	public:
		property AutoCompleteEntryCollection^ Items {
			AutoCompleteEntryCollection^ get() {
				return this->items;
			}
			void set(AutoCompleteEntryCollection^ value) {
				this->items = value;
			}
		}

	public:
		property int PopupWidth	{
			int get() {
				return this->popup->Width;
			}
			void set(int value) {
				if (value == -1) {
					this->popup->Width = this->Width;
				} else {
					this->popup->Width = value;
				}
			}
		}

	public:
		property System::Windows::Forms::BorderStyle PopupBorderStyle {
			System::Windows::Forms::BorderStyle get() {
				return this->list->BorderStyle;
			}
			void set(System::Windows::Forms::BorderStyle value) {
				this->list->BorderStyle = value;
			}
		}

	public:
		property Point^ PopupOffset {
			Point^ get() {
				return this->popOffset;
			}
			void set(Point^ value) {
				this->popOffset = value;
			}
		}

	public:
		property Color PopupSelectionBackColor {
			Color get() {
				return this->popSelectBackColor;
			}
			void set(Color value) {
				this->popSelectBackColor = value;
			}
		}

	public:
		property Color PopupSelectionForeColor {
			Color get() {
				return this->popSelectForeColor;
			}
			void set(Color value) {
				this->popSelectForeColor = value;
			}
		}

	protected:
		property bool TriggersEnabled {
			bool get() {
				return this->triggersEnabled;
			}
			void set(bool value) {
				this->triggersEnabled = value;
			}
		}

	public:
		property String^ Text {
			virtual String^ get() override {
				return TextBox::Text;
			}
			virtual void set(String^ value) override {
				this->TriggersEnabled = false;
				TextBox::Text = value;
				this->TriggersEnabled = true;
			}
		}

	private:
		void Popup_Deactivate(Object^ sender, EventArgs^ e) {
			if ( ! ( this->Focused || this->popup->Focused || this->list->Focused ) ) {
				this->HideList();
			}
		}

	private:
		void List_MouseDown(Object^ sender, MouseEventArgs^ e) {
			for (int i=0; i < this->list->Items->Count; i++) {
				Rectangle rect = this->list->GetItemRectangle(i);
				if ( rect.Contains( e->X, e->Y ) ) {
					this->list->SelectedIndex = i;
					this->SelectCurrentItem();
				}
			}
			this->HideList();
		}

	protected:
		virtual void WndProc(Message% m) override;

	private:
		void List_DrawItem(Object^ , DrawItemEventArgs^ );

	protected:
		virtual bool DefaultCmdKey(Message% , Keys );

	protected:
		virtual void ShowList();

	protected:
		 virtual void SelectCurrentItem();

	protected:
		virtual bool ProcessCmdKey(Message%, Keys ) override;

	protected:
		virtual void OnTextChanged(EventArgs^) override;

	protected:
		virtual void OnLostFocus(EventArgs^) override;

	protected:
		virtual void UpdateList();

	protected:
		virtual AutoCompleteEntryCollection^ FilterList(AutoCompleteEntryCollection^);

	private:
		void List_SelectedIndexChanged(Object^ , EventArgs^ e);
	};

}
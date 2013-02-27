#include "stdafx.h"
#include "AutoCompleteEntryCollection.h"

using namespace jpb;

AutoCompleteEntryCollection::AutoCompleteEntryCollection(void) {
}

void AutoCompleteEntryCollection::Add(IAutoCompleteEntry^ entry) {
	this->InnerList->Add(entry);
}

void AutoCompleteEntryCollection::AddRange(ICollection^ col)	{
	this->InnerList->AddRange(col);
}

void AutoCompleteEntryCollection::Add(AutoCompleteEntry^ entry) {
	this->InnerList->Add(entry);
}

array<Object^>^ AutoCompleteEntryCollection::ToObjectArray() {
	return this->InnerList->ToArray();
}

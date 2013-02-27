#include "stdafx.h"
#include "AutoCompleteEntryCollectionEditor.h"
#include "AutoCompleteEntry.h"

using namespace jpb;

AutoCompleteEntryCollectionEditor::AutoCompleteEntryCollectionEditor(Type^ type) : CollectionEditor(type) {};

bool AutoCompleteEntryCollectionEditor::CanSelectMultipleInstances() {
	return false;
}

Type^ AutoCompleteEntryCollectionEditor::CreateCollectionItemType() {
	return AutoCompleteEntry::typeid;
}


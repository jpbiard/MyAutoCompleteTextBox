#include "stdafx.h"
#include "AutoCompleteTriggerCollectionEditor.h"
#include "ShortCutTrigger.h"
#include "TextLengthTrigger.h"

using namespace jpb;

AutoCompleteTriggerCollectionEditor::AutoCompleteTriggerCollectionEditor(Type^ type) : CollectionEditor(type) {}

bool AutoCompleteTriggerCollectionEditor::CanSelectMultipleInstances() {
	return false;
}

array<Type^>^ AutoCompleteTriggerCollectionEditor::CreateNewItemTypes() {
	array<Type^>^ temp = gcnew array< Type^ >(2);
	temp[0] = ShortCutTrigger::typeid;
	temp[1] = TextLengthTrigger::typeid;
	return temp;
}

Type^ AutoCompleteTriggerCollectionEditor::CreateCollectionItemType() {
	return ShortCutTrigger::typeid;
}

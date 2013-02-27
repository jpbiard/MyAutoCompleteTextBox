#include "stdafx.h"
#include "AutoCompleteTriggerCollection.h"

using namespace jpb;

AutoCompleteTriggerCollection::AutoCompleteTriggerCollection(void) {
}

void AutoCompleteTriggerCollection::Add(AutoCompleteTrigger^ item) {
	this->InnerList->Add(item);
}

void AutoCompleteTriggerCollection::Remove(AutoCompleteTrigger^ item) {
	this->InnerList->Remove(item);
}

TriggerState AutoCompleteTriggerCollection::OnTextChanged(String^ text) {
	for each (AutoCompleteTrigger^ trigger in this->InnerList) {
		TriggerState state = trigger->OnTextChanged(text);
		if (state != TriggerState::None) {
			return state;
		}
	}
	return TriggerState::None;
}
		
TriggerState AutoCompleteTriggerCollection::OnCommandKey(Keys^ keyData) {
	for each (AutoCompleteTrigger^ trigger in this->InnerList) {
		TriggerState state = trigger->OnCommandKey(keyData);
		if (state != TriggerState::None) {
			return state;
		}
	}
	return TriggerState::None;
}
	

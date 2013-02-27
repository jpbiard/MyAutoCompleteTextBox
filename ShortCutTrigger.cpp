#include "stdafx.h"
#include "ShortCutTrigger.h"

using namespace jpb;

ShortCutTrigger::ShortCutTrigger(void) {
	this->result = TriggerState::None;
	this->shortCut = Keys::None;
}

ShortCutTrigger::ShortCutTrigger(Keys shortCutKeys, TriggerState resultState) {
	this->shortCut = shortCutKeys;
	this->result = resultState;
}

TriggerState ShortCutTrigger::OnCommandKey(Keys keyData) {
	if (keyData == this->ShortCut)
		return this->ResultState;

	return TriggerState::None;
}


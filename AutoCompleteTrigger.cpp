#include "stdafx.h"
#include "AutoCompleteTrigger.h"

using namespace jpb;

AutoCompleteTrigger::AutoCompleteTrigger(void)
{
}

TriggerState AutoCompleteTrigger::OnTextChanged(String^ text) {
	return TriggerState::None;
}
		
TriggerState AutoCompleteTrigger::OnCommandKey(Keys^ keyData) {
	return TriggerState::None;
}


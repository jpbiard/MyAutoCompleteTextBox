#include "stdafx.h"
#include "TextLengthTrigger.h"

using namespace jpb;

TextLengthTrigger::TextLengthTrigger(void) {
	this->textLength = 2;
}

TextLengthTrigger::TextLengthTrigger(int length) {
	this->textLength = length;
}

TriggerState TextLengthTrigger::OnTextChanged(String^ text) {
	if (text->Length >= this->TextLength)
		return TriggerState::Show;
	else if (text->Length < this->TextLength)
		return TriggerState::Hide;

	return TriggerState::None;
}


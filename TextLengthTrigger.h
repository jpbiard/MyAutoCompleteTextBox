#pragma once

#include "AutoCompleteTrigger.h"

namespace jpb {

	ref class TextLengthTrigger : AutoCompleteTrigger
	{
	public:
		TextLengthTrigger(void);
		TextLengthTrigger(int length);

	private:
		int textLength;

	public:
		property int TextLength {
			int get() {
				return this->textLength;
			}
			void set(int value) {
				this->textLength = value;
			}
		}

	public:
		virtual TriggerState OnTextChanged(String^) override;

	};

}
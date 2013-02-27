#pragma once

#include "TriggerState.h"
#include "AutoCompleteTrigger.h"

namespace jpb {

	using namespace System;
	using namespace System::Windows::Forms;


	ref class ShortCutTrigger : AutoCompleteTrigger
	{
	public:
		ShortCutTrigger(void);
		ShortCutTrigger(Keys , TriggerState );

	private:
		Keys shortCut;
		TriggerState result;

	public:
		property Keys ShortCut {
			Keys get() {
				return this->shortCut;
			}
			void set( Keys value ) {
				this->shortCut = value;
			}
		}

	public:
		property TriggerState ResultState {
			TriggerState get() {
				return this->result;
			}
			void set( TriggerState value ) {
				this->result = value;
			}
		}

	public:
		virtual TriggerState OnCommandKey(Keys);

	};

}
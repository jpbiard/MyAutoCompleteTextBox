#pragma once

#include "TriggerState.h"

namespace jpb {

	using namespace System;
	using namespace System::Windows::Forms;

	ref class AutoCompleteTrigger
	{
	public:
		AutoCompleteTrigger(void);

	public:
		 virtual TriggerState OnTextChanged(String^ text);
		
	public:
		 virtual TriggerState OnCommandKey(Keys^ keyData);
	};

}
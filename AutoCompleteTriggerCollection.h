#pragma once

#include "TriggerState.h"

#include "AutoCompleteTrigger.h"

namespace jpb {

	using namespace System;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::ComponentModel::Design;

	ref class AutoCompleteTriggerCollection : CollectionBase
	{
	public:
		AutoCompleteTriggerCollection(void);

	//public:
	//	property AutoCompleteTrigger this[int index] {
	//		AutoCompleteTrigger get() {
	//			return this.InnerList[index];
	//		}
	//	}

	public:
		void Add(AutoCompleteTrigger^);

		void Remove(AutoCompleteTrigger^);

		virtual TriggerState OnTextChanged(String^);
		
		virtual TriggerState OnCommandKey(Keys^);
	};

}
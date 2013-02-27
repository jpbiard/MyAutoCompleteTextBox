#pragma once

#include "AutoCompleteEntry.h"
#include "IAutoCompleteEntry.h"

namespace jpb {

	using namespace System::Collections;

	public ref class AutoCompleteEntryCollection : CollectionBase {

	public:
		AutoCompleteEntryCollection(void);
			
	//public:
	//	property IAutoCompleteEntry^ default[int] {
	//		IAutoCompleteEntry^ get(int index);
	//		// {
	//		//	return this->InnerList[index];
	//		//}
	//	}

	public:
		void AddRange(ICollection^ col);

		void Add(AutoCompleteEntry^ entry);
	
		void Add(IAutoCompleteEntry^ entry);

		array<Object^>^  ToObjectArray();
		
	};

}
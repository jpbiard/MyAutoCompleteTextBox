#pragma once

#include "IAutoCompleteEntry.h"

namespace jpb {

	using namespace System::Collections;

	public ref class AutoCompleteEntry : IAutoCompleteEntry
	{
	public:
		AutoCompleteEntry(void);
		AutoCompleteEntry(String^ name, String^ matchList);

	public:
		virtual String^ ToString() override {
			return this->DisplayName;
		}

	private:
		String^ matchStrings;
		String^ displayName;

	public:
		property String^ DisplayName {
			String^ get() {
				return this->displayName;
			}
			void set( String^ value ) {
				this->displayName = value;
			}
		}
		property String^ MatchStrings {
			virtual String^ get() {
				if ( this->matchStrings == nullptr ) {
					this->matchStrings = this->DisplayName;
				}
				return this->matchStrings;
			}
		}
	};
}

#pragma once

namespace jpb {

	using namespace System;

	public interface struct IAutoCompleteEntry {

	public:
	   property String^ MatchStrings {
		  String^ get();
	   }
	};

}
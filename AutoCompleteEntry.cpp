#include "stdafx.h"
#include "AutoCompleteEntry.h"

using namespace jpb;

AutoCompleteEntry::AutoCompleteEntry(void) {
	this->displayName = "";
}

AutoCompleteEntry::AutoCompleteEntry(String^ name, String^ matchList) {
	this->displayName = name;
	this->matchStrings = matchList;
}
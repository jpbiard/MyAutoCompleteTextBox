#pragma once

namespace jpb {

	using namespace System;
	using namespace System::Collections;
	using namespace System::ComponentModel::Design;
	using namespace System::Windows::Forms::Design;

	ref class AutoCompleteEntryCollectionEditor : CollectionEditor
	{
	public:
		AutoCompleteEntryCollectionEditor(Type^ type);

	protected:
		virtual bool CanSelectMultipleInstances() override;

		virtual Type^ CreateCollectionItemType() override;
	};

}
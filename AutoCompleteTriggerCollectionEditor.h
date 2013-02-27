#pragma once

namespace jpb {

	using namespace System;
	using namespace System::Collections;
	//using namespace System::Windows::Forms;
	using namespace System::ComponentModel::Design;

	ref class AutoCompleteTriggerCollectionEditor : CollectionEditor
	{
	public:
		AutoCompleteTriggerCollectionEditor(Type^);

	protected:
		virtual bool CanSelectMultipleInstances() override;

	protected:
		virtual array<Type^>^ CreateNewItemTypes() override;

	protected:
		virtual Type^ CreateCollectionItemType() override;
	};

}
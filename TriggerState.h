#pragma once

namespace jpb {

	public enum class TriggerState
	{
		None = 0,
		Show = 1,
		ShowAndConsume = 2,
		Hide = 3,
		HideAndConsume = 4,
		Select = 5,
		SelectAndConsume = 6
	};

}
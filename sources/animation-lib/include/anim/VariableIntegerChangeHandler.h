#pragma once

#include "anim/IUnknownHelper.h"

#include <UIAnimation.h>

namespace anim
{
	class VariableIntegerChangeHandler : public IUIAnimationVariableIntegerChangeHandler
	{
		_ANIM_IUNKNOWN_DECL

	public:
		VariableIntegerChangeHandler() = default;

		HRESULT OnIntegerValueChanged(
			IUIAnimationStoryboard* storyboard,
			IUIAnimationVariable* variable,
			int newValue,
			int previousValue ) override;

	};
}
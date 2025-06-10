#pragma once

#include "anim/IUnknownHelper.h"

#include <UIAnimation.h>


namespace anim
{
	class VariableChangeHandler : public IUIAnimationVariableChangeHandler
	{
		_ANIM_IUNKNOWN_DECL

	public:
		VariableChangeHandler() = default;

		HRESULT OnValueChanged(
			IUIAnimationStoryboard* storyboard,
			IUIAnimationVariable* variable,
			double newValue,
			double previousValue ) override;
	};
}
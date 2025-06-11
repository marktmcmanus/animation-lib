#pragma once

#include "anim/IUnknownHelper.h"

#include <UIAnimation.h>

namespace anim
{
	/**
	 * @brief Handles variable change events by implementing the IUIAnimationVariableIntegerChangeHandler interface.
	 *
	 * Subclass from `VariableIntegerChangeHandler` and override `OnIntegerValueChanged()`. Pass a pointer to your
	 * implementation class to `AnimationVariable::SetChangeHandler()`.
	 */
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
#pragma once

#include "anim/IUnknownHelper.h"

#include <UIAnimation.h>


namespace anim
{
	/**
	 * @brief Handles variable change events by implementing the IUIAnimationVariableChangeHandler interface.
	 *
	 * Subclass from `VariableChangeHandler` and override `OnValueChanged()`. Pass a pointer to your 
	 * implementation class to `AnimationVariable::SetChangeHandler()`.
	 */
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
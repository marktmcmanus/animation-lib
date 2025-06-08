#pragma once

#include "anim/IUnknownHelper.h"

#include <UIAnimation.h>


namespace anim
{
	class VariableChangeHandler : public IUIAnimationVariableChangeHandler
	{
	public:
		VariableChangeHandler() = default;

		_ANIM_IUNKNOWN_DECL

		HRESULT OnValueChanged(
			IUIAnimationStoryboard* storyboard,
			IUIAnimationVariable* variable,
			double newValue,
			double previousValue ) override;
	private:
		LONG m_Ref{ 0 };
	};
}
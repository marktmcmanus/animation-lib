#pragma once

#include "anim/IUnknownHelper.h"

#include <UIAnimation.h>

namespace anim
{
	class VariableIntegerChangeHandler : public IUIAnimationVariableIntegerChangeHandler
	{
	public:
		VariableIntegerChangeHandler() = default;

		_ANIM_IUNKNOWN_DECL

		HRESULT OnIntegerValueChanged(
			IUIAnimationStoryboard* storyboard,
			IUIAnimationVariable* variable,
			int newValue,
			int previousValue ) override;
	private:
		LONG m_Ref{ 0 };
	};
}
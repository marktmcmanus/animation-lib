#include "anim/VariableChangeHandler.h"

_ANIM_IUNKNOWN_IMPL(anim::VariableChangeHandler, IUIAnimationVariableChangeHandler)

HRESULT anim::VariableChangeHandler::OnValueChanged(
    IUIAnimationStoryboard* storyboard,
    IUIAnimationVariable* variable,
    double newValue,
    double previousValue)
{ 
	return S_OK;
}

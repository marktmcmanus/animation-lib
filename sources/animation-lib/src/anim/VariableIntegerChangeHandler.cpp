#include "anim/VariableIntegerChangeHandler.h"

_ANIM_IUNKNOWN_IMPL(anim::VariableIntegerChangeHandler, IUIAnimationVariableIntegerChangeHandler)

HRESULT anim::VariableIntegerChangeHandler::OnIntegerValueChanged(
    IUIAnimationStoryboard* storyboard,
    IUIAnimationVariable* variable,
    int newValue,
    int previousValue)
{ 
	return S_OK;
}

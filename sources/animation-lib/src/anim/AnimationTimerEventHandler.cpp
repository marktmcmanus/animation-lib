#include "anim/AnimationTimerEventHandler.h"

_ANIM_IUNKNOWN_IMPL(anim::AnimationTimerEventHandler, IUIAnimationTimerEventHandler)

HRESULT anim::AnimationTimerEventHandler::OnPostUpdate()
{
    return S_OK;
}

HRESULT anim::AnimationTimerEventHandler::OnPreUpdate()
{
    return S_OK;
}

HRESULT anim::AnimationTimerEventHandler::OnRenderingTooSlow(UINT32 /* framesPerSecond */)
{
    return S_OK;
}
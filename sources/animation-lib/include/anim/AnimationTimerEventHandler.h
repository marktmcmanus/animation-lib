#pragma once

#include "anim/IUnknownHelper.h"

#include <uianimation.h>

namespace anim
{
    class AnimationTimerEventHandler : public IUIAnimationTimerEventHandler
    {
        _ANIM_IUNKNOWN_DECL

    public:
        AnimationTimerEventHandler() = default;

        // IUIAnimationTimerEventHandler
        virtual HRESULT OnPostUpdate() override;
        virtual HRESULT OnPreUpdate() override;
        virtual HRESULT OnRenderingTooSlow(UINT32 framesPerSecond) override;
    };
}

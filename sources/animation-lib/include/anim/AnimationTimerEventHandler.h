#pragma once

#include "anim/IUnknownHelper.h"

#include <uianimation.h>

namespace anim
{
    class AnimationTimerEventHandler : public IUIAnimationTimerEventHandler
    {
    public:
        AnimationTimerEventHandler() = default;

        _ANIM_IUNKNOWN_DECL

        // IUIAnimationTimerEventHandler
        virtual HRESULT OnPostUpdate() override;
        virtual HRESULT OnPreUpdate() override;
        virtual HRESULT OnRenderingTooSlow(UINT32 framesPerSecond) override;

    private:
        LONG m_Ref{ 0 };
    };
}

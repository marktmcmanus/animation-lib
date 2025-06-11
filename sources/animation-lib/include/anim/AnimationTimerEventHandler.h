#pragma once

#include "anim/IUnknownHelper.h"

#include <uianimation.h>

namespace anim
{
    /**
     * @brief Handles animation timer events by implementing the IUIAnimationTimerEventHandler interface.
     *
     * Subclass from `AnimationTimerEventHandler` and override the functions you need to implement.
     * Basic default behaviour is provided. Pass a pointer to your implementation class to
     * `Animation::SetTimerEventHandler()`.
     */
    class AnimationTimerEventHandler : public IUIAnimationTimerEventHandler
    {
        _ANIM_IUNKNOWN_DECL

    public:
        AnimationTimerEventHandler() = default;

        virtual HRESULT OnPostUpdate() override;
        virtual HRESULT OnPreUpdate() override;
        virtual HRESULT OnRenderingTooSlow(UINT32 framesPerSecond) override;
    };
}

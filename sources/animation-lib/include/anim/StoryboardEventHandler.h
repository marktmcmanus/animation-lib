#pragma once

#include "anim/IUnknownHelper.h"

#include <UIAnimation.h>

namespace anim
{
    /**
     * @brief Handles storyboard events by implementing the IUIAnimationStoryboardEventHandler interface.
     *
     * Subclass from `StoryboardEventHandler` and override the functions you need to implement.
     * Basic default behaviour is provided. Pass a pointer to your implementation class to
     * `Storyboard::SetEventHandler()`.
     */
    class StoryboardEventHandler : public IUIAnimationStoryboardEventHandler
    {
        _ANIM_IUNKNOWN_DECL

    public:
        StoryboardEventHandler() = default;

        virtual HRESULT OnStoryboardStatusChanged(
            IUIAnimationStoryboard* storyboard,
            UI_ANIMATION_STORYBOARD_STATUS newStatus,
            UI_ANIMATION_STORYBOARD_STATUS previousStatus) override;

        virtual HRESULT OnStoryboardUpdated(IUIAnimationStoryboard* storyboard) override;
    };
}
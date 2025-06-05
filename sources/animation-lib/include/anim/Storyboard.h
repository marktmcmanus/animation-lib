#pragma once

#include "anim/AnimationVariable.h"
#include "anim/transition/Transition.h"

#include <uianimation.h>

#include <memory>
#include <optional>

namespace anim
{
    class Storyboard
    {
    public:
        Storyboard(IUIAnimationManager* manager, int id);
        ~Storyboard();

        int GetId() const { return m_Id; }
        bool IsOK() const;

        using TransitionOptRef = std::optional<std::reference_wrapper<anim::transition::Transition>>;
        bool AddTransition( 
            std::weak_ptr<anim::transition::Transition> transition, 
            AnimationVariable& var,
            double offset = 0.0,
            TransitionOptRef afterTransition = std::nullopt );

        bool Start(double now);

    private:
        UI_ANIMATION_KEYFRAME GetOrCreateKeyFrame(double offset);

        int m_Id;
        HRESULT m_Error;
        IUIAnimationStoryboard* m_Storyboard{ nullptr };
        std::unordered_map<double, UI_ANIMATION_KEYFRAME> m_KeyFrames;
    };
}
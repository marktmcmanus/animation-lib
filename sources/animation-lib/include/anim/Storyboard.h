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
        Storyboard(IUIAnimationManager* manager, std::optional<uint32_t> tag);
        ~Storyboard();

        std::uint32_t GetTag() const { return m_Tag; }
		bool IsOk() const { return m_Storyboard != nullptr; }

        using TransitionOptRef = std::optional<std::reference_wrapper<anim::transition::Transition>>;
        bool AddTransition( 
            std::weak_ptr<anim::transition::Transition> transition, 
            AnimationVariable& var,
            double offset = 0.0,
            TransitionOptRef afterTransition = std::nullopt );

        bool Schedule(double now);
        bool Abandon();
		bool Conclude();
		bool Finish( double completionDeadline);
		std::optional<UI_ANIMATION_STORYBOARD_STATUS> GetStatus();
		bool HoldVariable(AnimationVariable& var);
		bool SetLongestAcceptableDelay(double delay);
		HRESULT GetError() const { return m_Error; }

    private:
        std::optional<UI_ANIMATION_KEYFRAME> GetOrCreateKeyFrame(double offset);

        std::uint32_t m_Tag{ 0 };
        HRESULT m_Error;
        IUIAnimationStoryboard* m_Storyboard{ nullptr };
        std::unordered_map<double, UI_ANIMATION_KEYFRAME> m_KeyFrames;

        static std::uint32_t m_NextId;
    };
}
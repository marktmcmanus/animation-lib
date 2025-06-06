#pragma once

#include "anim/transition/Transition.h"

#include <UIAnimation.h>

#include <memory>

namespace anim
{
	class TransitionLibrary
	{
	public:
		TransitionLibrary();
		~TransitionLibrary();

        std::shared_ptr<anim::transition::Transition> CreateAccelerateDecelerateTransition(
            double duration,
            double finalValue,
            double accelerationRatio,
            double decelerationRatio ) const;
        
        std::shared_ptr<anim::transition::Transition> CreateConstantTransition(
            double duration ) const;
        
        std::shared_ptr<anim::transition::Transition> CreateCubicTransition(
            double duration,
            double finalValue,
            double finalVelocity ) const;
        
        std::shared_ptr<anim::transition::Transition> CreateDiscreteTransition(
            double delay,
            double finalValue,
            double hold ) const;

        std::shared_ptr<anim::transition::Transition> CreateInstantaneousTransition(
            double finalValue ) const;

        std::shared_ptr<anim::transition::Transition> CreateLinearTransition(
            double duration,
            double finalValue) const;

        std::shared_ptr<anim::transition::Transition> CreateLinearTransitionFromSpeed(
            double speed,
            double finalValue) const;

        std::shared_ptr<anim::transition::Transition> CreateParabolicTransitionFromAcceleration(
            double finalValue,
            double finalSpeed,
            double acceleration) const;

        std::shared_ptr<anim::transition::Transition> CreateReversalTransition(
            double duration ) const;

        std::shared_ptr<anim::transition::Transition> CreateSinusoidalTransitionFromRange(
            double duration,
            double minimumValue,
            double maximumValue,
            double period,
            UI_ANIMATION_SLOPE slope ) const;

        std::shared_ptr<anim::transition::Transition> CreateSinusoidalTransitionFromVelocity(
            double duration,
            double period ) const;

        std::shared_ptr<anim::transition::Transition> CreateSmoothStopTransition(
            double maximumDuration,
            double finalValue) const;

		IUIAnimationTransitionLibrary* GetTransitionLibrary() const { return m_TransitionLibrary; }

	private:
		IUIAnimationTransitionLibrary* m_TransitionLibrary{ nullptr };
	};
}
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

		IUIAnimationTransitionLibrary* GetTransitionLibrary() const { return m_TransitionLibrary; }

	private:
		IUIAnimationTransitionLibrary* m_TransitionLibrary{ nullptr };
	};
}
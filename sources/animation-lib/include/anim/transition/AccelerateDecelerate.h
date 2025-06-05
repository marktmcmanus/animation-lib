#pragma once

#include "anim/transition/Transition.h"
#include "anim/AnimationVariable.h"

namespace anim::transition
{
	class AccelerateDecelerate : public Transition
	{
	public:
		AccelerateDecelerate(
			IUIAnimationTransitionLibrary* transitionLibrary,
			double duration,
			double finalValue,
			double accelerationRatio,
			double decelerationRatio );

		virtual ~AccelerateDecelerate() = default;

	};
}
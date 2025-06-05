#pragma once

#include "anim/transition/Transition.h"

namespace anim::transition
{
	class Cubic : public Transition
	{
	public:
		Cubic(
			IUIAnimationTransitionLibrary* transitionLibrary, 
			double duration,
			double finalValue,
			double finalVelocity );

		virtual ~Cubic() = default;
	};
}
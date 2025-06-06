#pragma once

#include "anim/transition/Transition.h"

namespace anim::transition
{
	class SmoothStop : public Transition
	{
	public:
		SmoothStop(
			IUIAnimationTransitionLibrary* transitionLibrary, 
			double maximumDuration,
			double finalValue );
		virtual ~SmoothStop() = default;

	};
}
#pragma once
#include "anim/transition/Transition.h"

namespace anim::transition
{
	class SinusoidalFromRange : public Transition
	{
	public:
		SinusoidalFromRange(
			IUIAnimationTransitionLibrary* transitionLibrary,
			double duration,
			double minimumValue,
			double maximumValue,
			double period,
			UI_ANIMATION_SLOPE slope );
		virtual ~SinusoidalFromRange() = default;

	private:
	};
}

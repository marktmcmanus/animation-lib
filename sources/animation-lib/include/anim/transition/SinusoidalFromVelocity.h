#pragma once
#include "anim/transition/Transition.h"

namespace anim::transition
{
	class SinusoidalFromVelocity : public Transition
	{
	public:
		SinusoidalFromVelocity(
			IUIAnimationTransitionLibrary* transitionLibrary,
			double duration,
			double period );
		virtual ~SinusoidalFromVelocity() = default;

	private:
	};
}

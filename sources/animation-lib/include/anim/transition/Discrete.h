#pragma once

#include "anim/transition/Transition.h"

namespace anim::transition
{
	class Discrete : public Transition
	{
	public:
		Discrete(
			IUIAnimationTransitionLibrary* transitionLibrary, 
			double delay,
			double finalValue,
			double hold );
		virtual ~Discrete() = default;

	};
}
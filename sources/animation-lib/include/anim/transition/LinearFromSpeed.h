#pragma once

#include "anim/transition/Transition.h"

namespace anim::transition
{
	class LinearFromSpeed : public Transition
	{
	public:
		LinearFromSpeed(
			IUIAnimationTransitionLibrary* transitionLibrary, 
			double speed,
			double finalValue );
		virtual ~LinearFromSpeed() = default;

	};
}
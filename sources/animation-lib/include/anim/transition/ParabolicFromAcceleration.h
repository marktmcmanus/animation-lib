#pragma once

#include "anim/transition/Transition.h"

namespace anim::transition
{
	class ParabolicFromAcceleration : public Transition
	{
	public:
		ParabolicFromAcceleration(
			IUIAnimationTransitionLibrary* transitionLibrary,
			double finalValue,
			double finalSpeed,
			double acceleration );
		virtual ~ParabolicFromAcceleration() = default;

	};
}
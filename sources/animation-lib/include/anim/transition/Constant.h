#pragma once

#include "anim/transition/Transition.h"
#include "anim/AnimationVariable.h"

namespace anim::transition
{
	class Constant : public Transition
	{
	public:
		Constant(
			IUIAnimationTransitionLibrary* transitionLibrary, 
			double duration );
		virtual ~Constant() = default;

	};
}
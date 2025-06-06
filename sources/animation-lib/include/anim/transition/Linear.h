#pragma once

#include "anim/transition/Transition.h"

namespace anim::transition
{
	class Linear : public Transition
	{
	public:
		Linear(
			IUIAnimationTransitionLibrary* transitionLibrary, 
			double duration,
			double finalValue );
		virtual ~Linear() = default;

	};
}
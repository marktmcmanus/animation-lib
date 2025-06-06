#pragma once

#include "anim/transition/Transition.h"

namespace anim::transition
{
	class Instantaneous : public Transition
	{
	public:
		Instantaneous( 
			IUIAnimationTransitionLibrary* transitionLibrary, 
			double finalValue );
		virtual ~Instantaneous() = default;

	private:
	};
}
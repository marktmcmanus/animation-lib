#pragma once
#include "anim/transition/Transition.h"

namespace anim::transition
{
	class Reversal : public Transition
	{
	public:
		Reversal(
			IUIAnimationTransitionLibrary* transitionLibrary,
			double duration );
		virtual ~Reversal() = default;

	private:
	};
}
#include "anim/transition/Cubic.h"

anim::transition::Cubic::Cubic(
	IUIAnimationTransitionLibrary* transitionLibrary,
	double duration,
	double finalValue,
	double finalVelocity )
{
	HRESULT hr = transitionLibrary->CreateCubicTransition(
		duration,
		finalValue,
		finalVelocity,
		&m_Transition);

	if (FAILED(hr))
	{
		m_Transition = nullptr;
	}
}

#include "anim/transition/Discrete.h"

anim::transition::Discrete::Discrete(
	IUIAnimationTransitionLibrary* transitionLibrary,
	double delay,
	double finalValue,
	double hold)
{
	HRESULT hr = transitionLibrary->CreateDiscreteTransition(
		delay,
		finalValue,
		hold,
		&m_Transition);

	if (FAILED(hr))
	{
		m_Transition = nullptr;
	}
}

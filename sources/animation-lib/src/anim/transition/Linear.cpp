#include "anim/transition/Linear.h"

anim::transition::Linear::Linear(
	IUIAnimationTransitionLibrary* transitionLibrary,
	double duration,
	double finalValue)
{
	HRESULT hr = transitionLibrary->CreateLinearTransition(
		duration,
		finalValue,
		&m_Transition);

	if (FAILED(hr))
	{
		m_Transition = nullptr;
	}
}

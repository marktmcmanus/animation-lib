#include "anim/transition/SinusoidalFromVelocity.h"

anim::transition::SinusoidalFromVelocity::SinusoidalFromVelocity(
	IUIAnimationTransitionLibrary* transitionLibrary,
	double duration,
	double period )
{
	HRESULT hr = transitionLibrary->CreateSinusoidalTransitionFromVelocity(
		duration,
		period,
		&m_Transition);

	if (FAILED(hr))
	{
		m_Transition = nullptr;
	}
}

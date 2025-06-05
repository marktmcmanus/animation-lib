#include "anim/transition/AccelerateDecelerate.h"

anim::transition::AccelerateDecelerate::AccelerateDecelerate(
	IUIAnimationTransitionLibrary* transitionLibrary,
	double duration,
	double finalValue,
	double accelerationRatio,
	double decelerationRatio )
{
	HRESULT hr = transitionLibrary->CreateAccelerateDecelerateTransition(
		duration,
		finalValue,
		accelerationRatio,
		decelerationRatio,
		&m_Transition);

	if (FAILED(hr))
	{
		m_Transition = nullptr;
	}
}

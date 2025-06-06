#include "anim/transition/SmoothStop.h"

anim::transition::SmoothStop::SmoothStop(
	IUIAnimationTransitionLibrary* transitionLibrary,
	double maximumDuration,
	double finalValue)
{
	HRESULT hr = transitionLibrary->CreateSmoothStopTransition(
		maximumDuration,
		finalValue,
		&m_Transition);

	if (FAILED(hr))
	{
		m_Transition = nullptr;
	}
}

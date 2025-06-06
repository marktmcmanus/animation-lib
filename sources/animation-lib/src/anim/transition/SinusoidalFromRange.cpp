#include "anim/transition/SinusoidalFromRange.h"

anim::transition::SinusoidalFromRange::SinusoidalFromRange(
	IUIAnimationTransitionLibrary* transitionLibrary,
	double duration,
	double minimumValue,
	double maximumValue,
	double period,
	UI_ANIMATION_SLOPE slope)
{
	HRESULT hr = transitionLibrary->CreateSinusoidalTransitionFromRange(
		duration,
		minimumValue,
		maximumValue,
		period,
		slope,
		&m_Transition);

	if (FAILED(hr))
	{
		m_Transition = nullptr;
	}
}

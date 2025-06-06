#include "anim/transition/ParabolicFromAcceleration.h"

anim::transition::ParabolicFromAcceleration::ParabolicFromAcceleration(
	IUIAnimationTransitionLibrary* transitionLibrary,
	double finalValue,
	double finalSpeed,
	double acceleration)
{
	HRESULT hr = transitionLibrary->CreateParabolicTransitionFromAcceleration(
		finalValue,
		finalSpeed,
		acceleration,
		&m_Transition);

	if (FAILED(hr))
	{
		m_Transition = nullptr;
	}
}

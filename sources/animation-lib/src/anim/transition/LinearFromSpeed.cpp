#include "anim/transition/LinearFromSpeed.h"

anim::transition::LinearFromSpeed::LinearFromSpeed(
	IUIAnimationTransitionLibrary* transitionLibrary,
	double speed,
	double finalValue)
{
	HRESULT hr = transitionLibrary->CreateLinearTransitionFromSpeed(
		speed,
		finalValue,
		&m_Transition);

	if (FAILED(hr))
	{
		m_Transition = nullptr;
	}
}

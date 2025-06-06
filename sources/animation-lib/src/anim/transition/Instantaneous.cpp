#include "anim/transition/Instantaneous.h"

anim::transition::Instantaneous::Instantaneous( 
	IUIAnimationTransitionLibrary* transitionLibrary, 
	double finalValue )
{

	HRESULT hr = transitionLibrary->CreateInstantaneousTransition(
		finalValue,
		&m_Transition);

	if (FAILED(hr))
	{
		m_Transition = nullptr;
	}
}

#include "anim/transition/Reversal.h"

anim::transition::Reversal::Reversal(
	IUIAnimationTransitionLibrary* transitionLibrary,
	double duration)
{
	HRESULT hr = transitionLibrary->CreateReversalTransition(
		duration,
		&m_Transition);

	if (FAILED(hr))
	{
		m_Transition = nullptr;
	}
}

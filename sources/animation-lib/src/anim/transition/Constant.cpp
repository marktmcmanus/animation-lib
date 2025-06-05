#include "anim/transition/Constant.h"

anim::transition::Constant::Constant(
	IUIAnimationTransitionLibrary* transitionLibrary,
	double duration )
{
	HRESULT hr = transitionLibrary->CreateConstantTransition(
		duration,
		&m_Transition);

	if (FAILED(hr))
	{
		m_Transition = nullptr;
	}
}
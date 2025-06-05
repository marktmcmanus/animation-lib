#include "anim/transition/Transition.h"

anim::transition::Transition::~Transition()
{
	if (m_Transition != nullptr)
	{
		m_Transition->Release();
	}
}

UI_ANIMATION_KEYFRAME anim::transition::Transition::GetOrCreateKeyFrame(
	IUIAnimationStoryboard* storyBoard, 
	double offset )
{
	if (m_KeyFrames.count(0.0) == 0)
	{
		UI_ANIMATION_KEYFRAME transEndKeyFrame;
		HRESULT hr = storyBoard->AddKeyframeAfterTransition(
			m_Transition,
			&transEndKeyFrame);
		m_KeyFrames[0.0] = transEndKeyFrame;
	}

	if (m_KeyFrames.count(offset) > 0)
	{
		return m_KeyFrames[offset];
	}

	UI_ANIMATION_KEYFRAME newKeyFrame;
	HRESULT hr = storyBoard->AddKeyframeAtOffset(m_KeyFrames[0.0], offset, &newKeyFrame);
	m_KeyFrames[offset] = newKeyFrame;

	return newKeyFrame;
}
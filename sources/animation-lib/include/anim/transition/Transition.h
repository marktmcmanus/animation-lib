#pragma once

#include <UIAnimation.h>
#include <unordered_map>

namespace anim::transition
{
	class Transition
	{
	public:
		virtual ~Transition();

		IUIAnimationTransition* GetTransition() { return m_Transition; }
		UI_ANIMATION_KEYFRAME GetOrCreateKeyFrame(IUIAnimationStoryboard* storyBoard, double offset);
	protected:
		IUIAnimationTransition* m_Transition{ nullptr };
		std::unordered_map<double, UI_ANIMATION_KEYFRAME> m_KeyFrames;
	};
}
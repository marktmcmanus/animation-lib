#pragma once

#include "anim/IUnknownHelper.h"

#include <UIAnimation.h>

namespace anim
{
	class StoryboardEventHandler: public IUIAnimationStoryboardEventHandler
	{
		_ANIM_IUNKNOWN_DECL

	public:
		StoryboardEventHandler() = default;

		virtual HRESULT OnStoryboardStatusChanged(
			IUIAnimationStoryboard* storyboard,
			UI_ANIMATION_STORYBOARD_STATUS newStatus,
			UI_ANIMATION_STORYBOARD_STATUS previousStatus ) override;

		virtual HRESULT OnStoryboardUpdated( IUIAnimationStoryboard* storyboard ) override;
	};
}
#include "anim/StoryboardEventHandler.h"

_ANIM_IUNKNOWN_IMPL( anim::StoryboardEventHandler, IUIAnimationStoryboardEventHandler )

HRESULT anim::StoryboardEventHandler::OnStoryboardStatusChanged(
	IUIAnimationStoryboard* storyboard,
	UI_ANIMATION_STORYBOARD_STATUS newStatus,
	UI_ANIMATION_STORYBOARD_STATUS previousStatus )
{
	return S_OK;
}

HRESULT anim::StoryboardEventHandler::OnStoryboardUpdated( IUIAnimationStoryboard* storyboard )
{
	return S_OK;
}
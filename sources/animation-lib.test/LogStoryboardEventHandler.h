#pragma once

#include "anim/StoryboardEventHandler.h"

#include "wx/string.h"

class LogStoryboardEventHandler: public anim::StoryboardEventHandler
{
public:
	LogStoryboardEventHandler() = default;
	virtual ~LogStoryboardEventHandler() = default;

	virtual HRESULT OnStoryboardStatusChanged(
		IUIAnimationStoryboard* storyboard,
		UI_ANIMATION_STORYBOARD_STATUS newStatus,
		UI_ANIMATION_STORYBOARD_STATUS previousStatus ) override;

	virtual HRESULT OnStoryboardUpdated( IUIAnimationStoryboard* storyboard ) override;

private:
	wxString GetStatusString( UI_ANIMATION_STORYBOARD_STATUS status );
};
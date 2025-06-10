#include "LogStoryboardEventHandler.h"

#include "wx/log.h"

HRESULT LogStoryboardEventHandler::OnStoryboardStatusChanged(
	IUIAnimationStoryboard* storyboard,
	UI_ANIMATION_STORYBOARD_STATUS newStatus,
	UI_ANIMATION_STORYBOARD_STATUS previousStatus )
{
	UINT32 tag = 0;
	HRESULT hr = storyboard->GetTag( nullptr, &tag );
	wxLogDebug( wxString::Format( "animation-lib: OnStoryboardStatusChanged: Storyboard - %u, Old Status - %s, New Status - %s",
		tag, GetStatusString(previousStatus), GetStatusString(newStatus) ) );

	return S_OK;
}

HRESULT LogStoryboardEventHandler::OnStoryboardUpdated( IUIAnimationStoryboard* storyboard )
{
	UINT32 tag = 0;
	HRESULT hr = storyboard->GetTag( nullptr, &tag );
	wxLogDebug( wxString::Format( "animation-lib: OnStoryboardUpdated: Storyboard - %u", tag ) );

	return S_OK;
}

wxString LogStoryboardEventHandler::GetStatusString( UI_ANIMATION_STORYBOARD_STATUS status )
{
	wxString statusStr = "Unknown Status";

	switch( status )
	{
		case UI_ANIMATION_STORYBOARD_BUILDING:
		{
			statusStr = "UI_ANIMATION_STORYBOARD_BUILDING";
			break;
		}
		case UI_ANIMATION_STORYBOARD_SCHEDULED:
		{
			statusStr = "UI_ANIMATION_STORYBOARD_SCHEDULED";
			break;
		}
		case UI_ANIMATION_STORYBOARD_CANCELLED:
		{
			statusStr = "UI_ANIMATION_STORYBOARD_CANCELLED";
			break;
		}
		case UI_ANIMATION_STORYBOARD_PLAYING:
		{
			statusStr = "UI_ANIMATION_STORYBOARD_PLAYING";
			break;
		}
		case UI_ANIMATION_STORYBOARD_TRUNCATED:
		{
			statusStr = "UI_ANIMATION_STORYBOARD_TRUNCATED";
			break;
		}
		case UI_ANIMATION_STORYBOARD_FINISHED:
		{
			statusStr = "UI_ANIMATION_STORYBOARD_FINISHED";
			break;
		}
		case UI_ANIMATION_STORYBOARD_READY:
		{
			statusStr = "UI_ANIMATION_STORYBOARD_READY";
			break;
		}
		case UI_ANIMATION_STORYBOARD_INSUFFICIENT_PRIORITY:
		{
			statusStr = "UI_ANIMATION_STORYBOARD_INSUFFICIENT_PRIORITY";
			break;
		}
	}

	return statusStr;
}
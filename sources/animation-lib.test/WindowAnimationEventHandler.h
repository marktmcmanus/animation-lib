#pragma once

#include "anim/AnimationTimerEventHandler.h"

#include "wx/window.h"

class WindowAnimationEventHandler : public anim::AnimationTimerEventHandler
{
public:
	WindowAnimationEventHandler(wxWindow* wnd);

	virtual HRESULT OnPostUpdate() override;

private:
	wxWindow* m_Window{ nullptr };
};
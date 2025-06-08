#include "WindowAnimationEventHandler.h"

WindowAnimationEventHandler::WindowAnimationEventHandler(wxWindow* wnd) :
	m_Window(wnd)
{}

HRESULT WindowAnimationEventHandler::OnPostUpdate()
{
    if (m_Window != nullptr)
    {
        m_Window->Refresh();
    }

    return S_OK;
}
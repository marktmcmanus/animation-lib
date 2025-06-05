#include "MainWindowAnimationEventHandler.h"

#include "MainWindow.h"

MainWindowAnimationEventHandler::MainWindowAnimationEventHandler(MainWindow* mainWindow) :
	m_MainWindow(mainWindow)
{}

HRESULT MainWindowAnimationEventHandler::OnPostUpdate()
{
    if (m_MainWindow != nullptr)
    {
        m_MainWindow->Refresh();
    }

    return S_OK;
}
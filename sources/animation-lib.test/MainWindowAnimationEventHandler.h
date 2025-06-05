#pragma once

#include "anim/AnimationTimerEventHandler.h"

#include "wx/weakref.h"

class MainWindow;


class MainWindowAnimationEventHandler : public anim::AnimationTimerEventHandler
{
public:
	MainWindowAnimationEventHandler(MainWindow* mainWindow);

	virtual HRESULT OnPostUpdate() override;

private:
	wxWeakRef<MainWindow> m_MainWindow;
};
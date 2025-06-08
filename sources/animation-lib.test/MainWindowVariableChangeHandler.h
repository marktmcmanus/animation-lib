#pragma once

#include "anim/VariableIntegerChangeHandler.h"

class MainWindow;

enum VariablIds : int
{
	X = 1,
	Y
};

class MainWindowVariableChangeHandler : public anim::VariableIntegerChangeHandler
{
public:
	MainWindowVariableChangeHandler( MainWindow* wnd ) :
		m_MainWindow(wnd) {}
	~MainWindowVariableChangeHandler() = default;

	HRESULT OnIntegerValueChanged(
		IUIAnimationStoryboard* storyboard,
		IUIAnimationVariable* variable,
		int newValue,
		int previousValue) override;

private:
	MainWindow* m_MainWindow;
};
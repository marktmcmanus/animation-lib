#include "MainWindowVariableChangeHandler.h"

#include "MainWindow.h"

HRESULT MainWindowVariableChangeHandler::OnIntegerValueChanged(
	IUIAnimationStoryboard* storyboard,
	IUIAnimationVariable* variable,
	int newValue,
	int previousValue)
{
	if (m_MainWindow != nullptr && variable != nullptr)
	{
		uint32_t tag{ 0 };
		HRESULT hr = variable->GetTag(nullptr, &tag);

		if (SUCCEEDED(hr))
		{
			if (tag == VariablIds::X)
			{
				m_MainWindow->SetXValue(newValue);
			}
			else if (tag == VariablIds::Y)
			{
				m_MainWindow->SetYValue(newValue);
			}
		}
	}

	return S_OK;
}
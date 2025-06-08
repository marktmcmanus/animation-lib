#include "MainWindow.h"

#include "anim/TransitionLibrary.h"

#include <wx/wx.h>
#include <memory>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();

private:
    std::unique_ptr<anim::TransitionLibrary> m_TransitionLibrary;
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

	m_TransitionLibrary = std::make_unique<anim::TransitionLibrary>();

    MainWindow *frame = new MainWindow( *m_TransitionLibrary, wxDefaultPosition, wxSize(800, 800) );
    frame->Show(true);
    return true;
}

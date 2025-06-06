#include "anim/AnimationManager.h"
#include "MainWindow.h"

#include <wx/wx.h>
#include <memory>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();

private:
    std::unique_ptr<anim::AnimationManager> m_AnimationManager;
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    m_AnimationManager = std::make_unique<anim::AnimationManager>();

    MainWindow *frame = new MainWindow("animation-lib example", wxDefaultPosition, wxSize(800, 800), *m_AnimationManager);
    frame->Show(true);
    return true;
}

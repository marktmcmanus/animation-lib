#include "MainWindow.h"

#include <wx/wx.h>
#include <memory>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

    MainWindow *frame = new MainWindow("animation-lib example", wxDefaultPosition, wxSize(800, 800) );
    frame->Show(true);
    return true;
}

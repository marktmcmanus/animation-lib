#include "MainWindow.h"
#include "MainWindowAnimationEventHandler.h"

#include "anim/transition/Constant.h"
#include "anim/transition/AccelerateDecelerate.h"

#include <wx/wx.h>
#include <wx/dc.h>
#include <wx/dcbuffer.h>
#include <wx/dcgraph.h>
#include <wx/graphics.h>

const UI_ANIMATION_SECONDS DURATION = 1.5;
const DOUBLE ACCELERATION_RATIO = 0.5;
const DOUBLE DECELERATION_RATIO = 0.5;

MainWindow::MainWindow(const wxString &title, const wxPoint &pos, const wxSize &size, anim::AnimationManager &animationManager)
    : wxFrame(NULL, wxID_ANY, title, pos, size),
      m_AnimationManager(animationManager)
{
	SetBackgroundStyle(wxBG_STYLE_PAINT);

    MainWindowAnimationEventHandler* timerHandler = new MainWindowAnimationEventHandler(this);
    m_AnimationManager.SetTimerEventHandler(timerHandler);
    m_VarX = m_AnimationManager.CreateVariable(10.0);
    m_VarY = m_AnimationManager.CreateVariable(10.0);

    Bind(wxEVT_PAINT, &MainWindow::OnPaint, this);

    CreateMenuBar();
    
	SetStatusBar(new wxStatusBar(this, wxID_ANY));
    SetStatusText("Welcome to the Animation Example!");
}

void MainWindow::OnPaint(wxPaintEvent &evt)
{
    wxBufferedPaintDC pdc(this);
	wxGCDC gcdc(pdc);

    gcdc.SetBackground(*wxWHITE_BRUSH);
    gcdc.Clear();

    auto xVar1 = m_VarX.lock();
    if (xVar1 != nullptr)
    {
        auto x = xVar1->GetInteger();
        if (x.has_value())
        {
            wxColour myColour(255, 0, 0, 100);
            gcdc.SetBrush(wxBrush(myColour));
            gcdc.DrawRectangle(*x, 10, 100, 100);
        }
    }

    auto xVar2 = m_VarY.lock();
    if (xVar2 != nullptr)
    {
        auto x = xVar2->GetInteger();
        if (x.has_value())
        {
            wxColour myColour(0, 255, 0, wxALPHA_OPAQUE);
            gcdc.SetBrush(wxBrush(myColour));
            gcdc.DrawRectangle(*x, 120, 100, 100);
        }
    }

    //auto xVar = m_VarX.lock();
    //auto yVar = m_VarY.lock();
    //if (xVar != nullptr && yVar != nullptr)
    //{
    //    auto x = xVar->GetInteger();
    //    if (x.has_value())
    //    {
    //        auto y = yVar->GetInteger();
    //
    //        if (y.has_value())
    //        {
    //            wxColour myColour(255, 0, 0, wxALPHA_OPAQUE);
    //            mydc.SetBrush(wxBrush(myColour, wxSOLID));
    //            mydc.DrawRectangle(*x, *y, 100, 100);
    //        }
    //    }
    //}
}

void MainWindow::CreateMenuBar()
{
    // Create a menu bar
    auto* menuBar = new wxMenuBar();

    // File menu
    auto* fileMenu = new wxMenu();
    fileMenu->Append(wxID_EXIT, "&Exit\tAlt-X", "Quit this program");
    menuBar->Append(fileMenu, "&File");

    // Animation menu
    auto* animationMenu = new wxMenu();
    animationMenu->Append(wxID_ANY, "&Start Animation\tCtrl-A", "Start the animation");
    menuBar->Append(animationMenu, "&Animation");

    // Help menu
    auto* helpMenu = new wxMenu();
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");
    menuBar->Append(helpMenu, "&Help");

    // Attach the menu bar to the frame
    SetMenuBar(menuBar);

    // Bind menu events
    Bind(wxEVT_MENU, [this](wxCommandEvent& event) { Close(true); }, wxID_EXIT);

    Bind(wxEVT_MENU, [this](wxCommandEvent& event) { 
        wxMessageBox("This is a simple animation example using wxWidgets.", "About Animation Example", wxOK | wxICON_INFORMATION); 
        }, wxID_ABOUT);

    Bind(wxEVT_MENU, [this](wxCommandEvent& event) { CreateStoryboard(); }, animationMenu->FindItem("&Start Animation\tCtrl-A"));
}

void MainWindow::CreateStoryboard()
{
    m_Storyboard = m_AnimationManager.CreateStoryboard();

    if (auto sb = m_Storyboard.lock(); sb != nullptr)
    {
        auto ad1 = m_AnimationManager.GetTransitionLibrary().CreateAccelerateDecelerateTransition( 
            DURATION, 600, ACCELERATION_RATIO, DECELERATION_RATIO);
        m_Transitions.push_back(ad1);
        sb->AddTransition(ad1, *m_VarX.lock());

        auto ad2 = m_AnimationManager.GetTransitionLibrary().CreateAccelerateDecelerateTransition( 
            DURATION, 600, ACCELERATION_RATIO, DECELERATION_RATIO);
        m_Transitions.push_back(ad2);
        sb->AddTransition(ad2, *m_VarY.lock(), 0.5, *ad1);

        auto const1 = m_AnimationManager.GetTransitionLibrary().CreateConstantTransition( 1 );
        m_Transitions.push_back(const1);
        sb->AddTransition(const1, *m_VarX.lock());

        auto const2 = m_AnimationManager.GetTransitionLibrary().CreateConstantTransition( 1 );
        m_Transitions.push_back(const2);
        sb->AddTransition(const2, *m_VarY.lock());

        auto ad3 = m_AnimationManager.GetTransitionLibrary().CreateAccelerateDecelerateTransition( 
            DURATION, 10, ACCELERATION_RATIO, DECELERATION_RATIO);
        m_Transitions.push_back(ad3);
        sb->AddTransition(ad3, *m_VarX.lock());

        auto ad4 = m_AnimationManager.GetTransitionLibrary().CreateAccelerateDecelerateTransition( 
            DURATION, 10, ACCELERATION_RATIO, DECELERATION_RATIO);
        m_Transitions.push_back(ad4);
        sb->AddTransition(ad4, *m_VarY.lock());
        

        auto time = m_AnimationManager.GetTime();
        if (time.has_value())
        {
            sb->Start(time.value());
        }
    }
}
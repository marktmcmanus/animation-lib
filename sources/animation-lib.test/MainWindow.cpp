#include "MainWindow.h"
#include "WindowAnimationEventHandler.h"
#include "MainWindowVariableChangeHandler.h"

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

MainWindow::MainWindow(anim::TransitionLibrary& transitionLibrary, const wxPoint &pos, const wxSize &size )
    : wxFrame(NULL, wxID_ANY, "animation-lib example", pos, size),
      m_TransitionLibrary(transitionLibrary)
{
    m_Animation = std::make_unique<anim::Animation>();
	SetBackgroundStyle(wxBG_STYLE_PAINT);

	//Animation (UIAnimationManager) takes ownership of the timer handler, so we don't need to delete it manually 
    WindowAnimationEventHandler* timerHandler = new WindowAnimationEventHandler(this);
    m_Animation->SetTimerEventHandler(timerHandler);

    auto xVar = m_Animation->CreateVariable(10.0, VariablIds::X);
	MainWindowVariableChangeHandler* xChangeHandler = new MainWindowVariableChangeHandler(this);
	xVar.lock()->SetChangeHandler(xChangeHandler);

    auto yVar = m_Animation->CreateVariable(10.0, VariablIds::Y);
    MainWindowVariableChangeHandler* yChangeHandler = new MainWindowVariableChangeHandler(this);
    yVar.lock()->SetChangeHandler(yChangeHandler);

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

    wxColour red(255, 0, 0, 100);
    gcdc.SetBrush(wxBrush(red));
    gcdc.DrawRectangle(m_XValue, 10, 100, 100);

    wxColour green(0, 255, 0, wxALPHA_OPAQUE);
    gcdc.SetBrush(wxBrush(green));
    gcdc.DrawRectangle(m_YValue, 120, 100, 100);
 

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
    m_Storyboard = m_Animation->CreateStoryboard();

    if (auto sb = m_Storyboard.lock(); sb != nullptr)
    {
		auto xVar = m_Animation->GetVariable(VariablIds::X).lock();
		auto yVar = m_Animation->GetVariable(VariablIds::Y).lock();

        if (xVar == nullptr || yVar == nullptr)
        {
            wxLogError("Variables not found. Cannot create storyboard.");
            return;
        }

        auto ad1 = m_TransitionLibrary.CreateAccelerateDecelerateTransition(
            DURATION, 600, ACCELERATION_RATIO, DECELERATION_RATIO);
        m_Transitions.push_back(ad1);

        sb->AddTransition(ad1, *xVar);

        auto ad2 = m_TransitionLibrary.CreateAccelerateDecelerateTransition(
            DURATION, 600, ACCELERATION_RATIO, DECELERATION_RATIO);
        m_Transitions.push_back(ad2);
        sb->AddTransition(ad2, *yVar, 0.5, *ad1);

        auto const1 = m_TransitionLibrary.CreateConstantTransition( 1 );
        m_Transitions.push_back(const1);
        sb->AddTransition(const1, *xVar);

        auto const2 = m_TransitionLibrary.CreateConstantTransition( 1 );
        m_Transitions.push_back(const2);
        sb->AddTransition(const2, *yVar);

        auto ad3 = m_TransitionLibrary.CreateAccelerateDecelerateTransition(
            DURATION, 10, ACCELERATION_RATIO, DECELERATION_RATIO);
        m_Transitions.push_back(ad3);
        sb->AddTransition(ad3, *xVar);

        auto ad4 = m_TransitionLibrary.CreateAccelerateDecelerateTransition(
            DURATION, 10, ACCELERATION_RATIO, DECELERATION_RATIO);
        m_Transitions.push_back(ad4);
        sb->AddTransition(ad4, *yVar);
        

        auto time = m_Animation->GetTime();
        if (time.has_value())
        {
            sb->Schedule(time.value());
        }
    }
}
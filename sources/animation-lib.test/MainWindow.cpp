#include "MainWindow.h"
#include "MainWindowAnimationEventHandler.h"

#include "anim/transition/Constant.h"
#include "anim/transition/AccelerateDecelerate.h"

#include <wx/wx.h>
#include <wx/dc.h>
#include <wx/dcprint.h>

const UI_ANIMATION_SECONDS DURATION = 1.5;
const DOUBLE ACCELERATION_RATIO = 0.5;
const DOUBLE DECELERATION_RATIO = 0.5;

MainWindow::MainWindow(const wxString &title, const wxPoint &pos, const wxSize &size, anim::AnimationManager &animationManager)
    : wxFrame(NULL, wxID_ANY, title, pos, size),
      m_AnimationManager(animationManager)
{
    MainWindowAnimationEventHandler* timerHandler = new MainWindowAnimationEventHandler(this);
    m_AnimationManager.SetTimerEventHandler(timerHandler);
    m_VarX = m_AnimationManager.CreateVariable(10.0);
    m_VarY = m_AnimationManager.CreateVariable(10.0);

    Bind(wxEVT_PAINT, &MainWindow::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &MainWindow::OnLeftDown, this);
}

void MainWindow::OnPaint(wxPaintEvent &evt)
{
    wxPaintDC mydc(this);

    mydc.SetBackground(*wxWHITE_BRUSH);
    mydc.Clear();

    auto xVar1 = m_VarX.lock();
    if (xVar1 != nullptr)
    {
        auto x = xVar1->GetInteger();
        if (x.has_value())
        {
            wxColour myColour(255, 0, 0, wxALPHA_OPAQUE);
            mydc.SetBrush(wxBrush(myColour, wxSOLID));
            mydc.DrawRectangle(*x, 10, 100, 100);
        }
    }

    auto xVar2 = m_VarY.lock();
    if (xVar2 != nullptr)
    {
        auto x = xVar2->GetInteger();
        if (x.has_value())
        {
            wxColour myColour(0, 255, 0, wxALPHA_OPAQUE);
            mydc.SetBrush(wxBrush(myColour, wxSOLID));
            mydc.DrawRectangle(*x, 120, 100, 100);
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

void MainWindow::OnLeftDown(wxMouseEvent &evt)
{
    int i = 0;
    CreateStoryboard();
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
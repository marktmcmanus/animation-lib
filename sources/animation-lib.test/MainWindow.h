#pragma once

#include "anim/Animation.h"
#include "anim/transition/Transition.h"

#include <wx/frame.h>
#include <memory>
#include <vector>

class MainWindow : public wxFrame
{
public:
    MainWindow(
        anim::TransitionLibrary& transitionLibrary,
        const wxPoint &pos,
        const wxSize &size );

    virtual ~MainWindow() = default;

	void SetXValue(int value) { m_XValue = value; }
	void SetYValue(int value) { m_YValue = value; }

private:
    void OnPaint(wxPaintEvent &evt);

	void CreateMenuBar();
    void CreateStoryboard();

	anim::TransitionLibrary& m_TransitionLibrary;
    std::unique_ptr<anim::Animation> m_Animation;
    //std::weak_ptr<anim::AnimationVariable> m_VarX;
    //std::weak_ptr<anim::AnimationVariable> m_VarY;
    std::weak_ptr<anim::Storyboard> m_Storyboard;

    int m_XValue{10};
	int m_YValue{10};

    std::vector<std::shared_ptr<anim::transition::Transition>> m_Transitions;
};
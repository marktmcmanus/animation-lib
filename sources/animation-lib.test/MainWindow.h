#pragma once

#include "anim/AnimationManager.h"
#include "anim/transition/Transition.h"

#include <wx/frame.h>
#include <memory>
#include <vector>

class MainWindow : public wxFrame
{
public:
    MainWindow(
        const wxString &title,
        const wxPoint &pos,
        const wxSize &size,
        anim::AnimationManager &animationManager);

private:
    void OnPaint(wxPaintEvent &evt);
    void OnLeftDown(wxMouseEvent &evt);

    void CreateStoryboard();

    anim::AnimationManager &m_AnimationManager;
    std::weak_ptr<anim::AnimationVariable> m_VarX;
    std::weak_ptr<anim::AnimationVariable> m_VarY;
    std::weak_ptr<anim::Storyboard> m_Storyboard;

    std::vector<std::shared_ptr<anim::transition::Transition>> m_Transitions;
};
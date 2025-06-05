#include "anim/Storyboard.h"

anim::Storyboard::Storyboard(IUIAnimationManager *manager, int id)
    : m_Id(id)
{
    m_Error = manager->CreateStoryboard(&m_Storyboard);
}

anim::Storyboard::~Storyboard()
{
    if (m_Storyboard != nullptr)
    {
        m_Storyboard->Release();
    }
}

bool anim::Storyboard::IsOK() const
{
    return m_Storyboard != nullptr && SUCCEEDED(m_Error);
}

bool anim::Storyboard::AddTransition(
    std::weak_ptr<anim::transition::Transition> transition, 
    AnimationVariable& var,
    double offset,
    TransitionOptRef afterTransition )
{
    bool success = false;
    if (auto transitionPtr = transition.lock(); transitionPtr != nullptr)
    {
        HRESULT hr;
        if (afterTransition.has_value())
        {
            hr = m_Storyboard->AddTransitionAtKeyframe(
                var.GetVariable(),
                transitionPtr->GetTransition(),
                afterTransition->get().GetOrCreateKeyFrame(m_Storyboard, offset));
        }
        else if (offset != 0.0 )
        {
            hr = m_Storyboard->AddTransitionAtKeyframe(
                var.GetVariable(),
                transitionPtr->GetTransition(),
                GetOrCreateKeyFrame(offset));
        }
        else
        {
            hr = m_Storyboard->AddTransition(
                var.GetVariable(),
                transitionPtr->GetTransition());
        }

        success = SUCCEEDED(hr);
    }

    return success;
}


bool anim::Storyboard::Start(double now)
{
    if (m_Storyboard != nullptr)
    {
        HRESULT hr = m_Storyboard->Schedule(now);
        return SUCCEEDED(hr);
    }
    return false;
}

UI_ANIMATION_KEYFRAME anim::Storyboard::GetOrCreateKeyFrame(double offset)
{
    if (m_KeyFrames.count(offset) == 0)
    {
        UI_ANIMATION_KEYFRAME newKeyFrame;
        HRESULT hr = m_Storyboard->AddKeyframeAtOffset(UI_ANIMATION_KEYFRAME_STORYBOARD_START, offset, &newKeyFrame);
        m_KeyFrames[offset] = newKeyFrame;
    }

    return m_KeyFrames[offset];
}
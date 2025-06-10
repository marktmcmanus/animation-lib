#define NOMINMAX

#include "anim/Storyboard.h"

#include <limits>
std::uint32_t anim::Storyboard::m_NextId = std::numeric_limits<uint32_t>::max();

anim::Storyboard::Storyboard(IUIAnimationManager *manager, std::optional<uint32_t> tag)
{
    m_Error = manager->CreateStoryboard(&m_Storyboard);

    if (SUCCEEDED(m_Error) && m_Storyboard != nullptr)
    {
        m_Tag = tag.value_or(m_NextId--);
        m_Error = m_Storyboard->SetTag(nullptr, m_Tag);
        if (FAILED(m_Error))
        {
            m_Storyboard->Release();
            m_Storyboard = nullptr;
        }
    }
    else
    {
        m_Storyboard = nullptr;
    }
}

anim::Storyboard::~Storyboard()
{
    if (m_Storyboard != nullptr)
    {
        m_Storyboard->Release();
    }
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
        if (afterTransition.has_value())
        {
            m_Error = m_Storyboard->AddTransitionAtKeyframe(
                var.GetVariable(),
                transitionPtr->GetTransition(),
                afterTransition->get().GetOrCreateKeyFrame(m_Storyboard, offset));
        }
        else if (offset != 0.0 )
        {
			auto keyFrame = GetOrCreateKeyFrame(offset);
            if (keyFrame.has_value())
            {
                m_Error = m_Storyboard->AddTransitionAtKeyframe(
                    var.GetVariable(),
                    transitionPtr->GetTransition(),
                    keyFrame.value());
            }
        }
        else
        {
            m_Error = m_Storyboard->AddTransition(
                var.GetVariable(),
                transitionPtr->GetTransition());
        }

        success = SUCCEEDED(m_Error);
    }
    else
    {
        m_Error = E_POINTER;
    }
    return success;
}

bool anim::Storyboard::Schedule(double now)
{
    if (IsOk())
    {
        m_Error = m_Storyboard->Schedule(now);
        return SUCCEEDED(m_Error);
    }
    m_Error = E_POINTER;
    return false;
}

bool anim::Storyboard::Abandon()
{
    if (IsOk())
    {
        m_Error = m_Storyboard->Abandon();
        return SUCCEEDED(m_Error);
    }
    m_Error = E_POINTER;
    return false;
}

bool anim::Storyboard::Conclude()
{
    if (IsOk())
    {
        m_Error = m_Storyboard->Conclude();
        return SUCCEEDED(m_Error);
    }
    m_Error = E_POINTER;
    return false;
}

bool anim::Storyboard::Finish(double completionDeadline)
{
    if (IsOk())
    {
        m_Error = m_Storyboard->Finish(completionDeadline);
        return SUCCEEDED(m_Error);
    }
    m_Error = E_POINTER;
    return false;
}

std::optional<UI_ANIMATION_STORYBOARD_STATUS> anim::Storyboard::GetStatus()
{
    if( IsOk() )
    {
        UI_ANIMATION_STORYBOARD_STATUS status;
        m_Error = m_Storyboard->GetStatus(&status);
        if (SUCCEEDED(m_Error))
        {
            return status;
        }
    }
    m_Error = E_POINTER;
	return std::nullopt;
}

bool anim::Storyboard::HoldVariable(anim::AnimationVariable& var)
{
    if (IsOk() && var.IsOk())
    {
		m_Error = m_Storyboard->HoldVariable(var.GetVariable());
        return SUCCEEDED(m_Error);
    }
    m_Error = E_POINTER;
    return false;
}

bool anim::Storyboard::SetLongestAcceptableDelay(double delay)
{
    if (IsOk())
    {
        m_Error = m_Storyboard->SetLongestAcceptableDelay(delay);
        return SUCCEEDED(m_Error);
    }
    m_Error = E_POINTER;
	return false;
}

bool anim::Storyboard::SetEventHandler( IUIAnimationStoryboardEventHandler* eventHandler )
{
    if( IsOk() )
    {
        m_Error = m_Storyboard->SetStoryboardEventHandler( eventHandler );
        return SUCCEEDED( m_Error );
    }
    m_Error = E_POINTER;
    return false;
}

std::optional<UI_ANIMATION_KEYFRAME> anim::Storyboard::GetOrCreateKeyFrame(double offset)
{
    if (m_KeyFrames.count(offset) == 0)
    {
        UI_ANIMATION_KEYFRAME newKeyFrame;
        m_Error = m_Storyboard->AddKeyframeAtOffset(UI_ANIMATION_KEYFRAME_STORYBOARD_START, offset, &newKeyFrame);
        if(SUCCEEDED(m_Error))
        { 
            m_KeyFrames[offset] = newKeyFrame;
        }
        else
        {
            return std::nullopt;
		}
        
    }

    return m_KeyFrames[offset];
}
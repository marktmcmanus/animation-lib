
#define NOMINMAX

#include "anim/AnimationVariable.h"

#include <limits>
std::uint32_t anim::AnimationVariable::m_NextId = std::numeric_limits<uint32_t>::max();

anim::AnimationVariable::AnimationVariable(
    IUIAnimationManager *manager, 
    double initialValue, 
    std::optional<uint32_t> tag )
{
    m_Error = manager->CreateAnimationVariable(
        initialValue,
        &m_AnimationVariable);

    if (SUCCEEDED(m_Error) && m_AnimationVariable != nullptr)
    {
		m_Tag = tag.value_or(m_NextId--);
        m_Error = m_AnimationVariable->SetTag(nullptr, m_Tag);
        if(FAILED(m_Error) )
        {
            m_AnimationVariable->Release();
            m_AnimationVariable = nullptr;
		}
    }
    else
    {
        m_AnimationVariable = nullptr;
    }
}

anim::AnimationVariable::~AnimationVariable()
{
    if (m_AnimationVariable != nullptr)
    {
        m_AnimationVariable->Release();
    }
}

HRESULT anim::AnimationVariable::SetChangeHandler(VariableChangeHandler* handler)
{
    if( m_AnimationVariable != nullptr)
    {
        return m_AnimationVariable->SetVariableChangeHandler(handler);
	}

	return E_POINTER;
}

HRESULT anim::AnimationVariable::SetChangeHandler(VariableIntegerChangeHandler* handler)
{
    if (m_AnimationVariable != nullptr)
    {
        return m_AnimationVariable->SetVariableIntegerChangeHandler(handler);
    }

    return E_POINTER;
}

std::optional<double> anim::AnimationVariable::GetDouble()
{
    double val{0};
    m_Error = m_AnimationVariable->GetValue(&val);
    if (SUCCEEDED(m_Error))
    {
        return val;
    }
    return std::nullopt;
}

std::optional<double> anim::AnimationVariable::GetFinalDouble()
{
    double val{ 0 };
    m_Error = m_AnimationVariable->GetFinalValue(&val);
    if (SUCCEEDED(m_Error))
    {
        return val;
    }
    return std::nullopt;
}

std::optional<double> anim::AnimationVariable::GetPreviousDouble()
{
    double val{ 0 };
    m_Error = m_AnimationVariable->GetPreviousValue(&val);
    if (SUCCEEDED(m_Error))
    {
        return val;
    }
    return std::nullopt;
}

std::optional<int> anim::AnimationVariable::GetInteger()
{
    int val{0};
    m_Error = m_AnimationVariable->GetIntegerValue(&val);
    if (SUCCEEDED(m_Error))
    {
        return val;
    }
    return std::nullopt;
}

std::optional<int> anim::AnimationVariable::GetFinalInteger()
{
    int val{ 0 };
    m_Error = m_AnimationVariable->GetFinalIntegerValue(&val);
    if (SUCCEEDED(m_Error))
    {
        return val;
    }
    return std::nullopt;
}

std::optional<int> anim::AnimationVariable::GetPreviousInteger()
{
    int val{ 0 };
    m_Error = m_AnimationVariable->GetPreviousIntegerValue(&val);
    if (SUCCEEDED(m_Error))
    {
        return val;
    }
    return std::nullopt;
}

IUIAnimationStoryboard* anim::AnimationVariable::GetStoryboard()
{
    if (m_AnimationVariable != nullptr)
    {
        IUIAnimationStoryboard* storyboard = nullptr;
        m_Error = m_AnimationVariable->GetCurrentStoryboard(&storyboard);
        if (SUCCEEDED(m_Error) && storyboard != nullptr)
        {
            return storyboard;
        }
    }
	return nullptr;
}

bool anim::AnimationVariable::SetLowerBounds(double lowerBound)
{
    if (m_AnimationVariable != nullptr)
    {
        m_Error = m_AnimationVariable->SetLowerBound(lowerBound);
        return SUCCEEDED(m_Error);
    }
	return false;
}

bool anim::AnimationVariable::SetUpperBounds(double upperBound)
{
    if (m_AnimationVariable != nullptr)
    {
        m_Error = m_AnimationVariable->SetUpperBound(upperBound);
        return SUCCEEDED(m_Error);
    }
    return false;
}

bool anim::AnimationVariable::SetRoundingMode(UI_ANIMATION_ROUNDING_MODE roundingMode)
{
    if (m_AnimationVariable != nullptr)
    {
        m_Error = m_AnimationVariable->SetRoundingMode(roundingMode);
        return SUCCEEDED(m_Error);
    }
	return false;
}
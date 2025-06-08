
#define NOMINMAX

#include "anim/AnimationVariable.h"

#include <limits>
UINT32 anim::AnimationVariable::m_NextId = std::numeric_limits<uint32_t>::max();

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
    HRESULT hr = m_AnimationVariable->GetValue(&val);
    if (SUCCEEDED(hr))
    {
        return val;
    }
    return std::nullopt;
}

std::optional<int> anim::AnimationVariable::GetInteger()
{
    int val{0};
    HRESULT hr = m_AnimationVariable->GetIntegerValue(&val);
    if (SUCCEEDED(hr))
    {
        return val;
    }
    return std::nullopt;
}

bool anim::AnimationVariable::IsOk() const
{
    return m_AnimationVariable != nullptr && SUCCEEDED(m_Error);
}
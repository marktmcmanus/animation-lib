#include "anim/AnimationVariable.h"

anim::AnimationVariable::AnimationVariable(IUIAnimationManager *manager, double initialValue, int id)
    : m_Id(id)
{
    m_Error = manager->CreateAnimationVariable(
        initialValue,
        &m_AnimationVariable);
}

anim::AnimationVariable::~AnimationVariable()
{
    if (m_AnimationVariable != nullptr)
    {
        m_AnimationVariable->Release();
    }
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
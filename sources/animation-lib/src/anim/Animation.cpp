#include "anim/Animation.h"

anim::Animation::Animation()
{
    CreateAnimationManager();
    CreateAnimationTimer();
    InitializeTimerUpdateHandler();
}

anim::Animation::~Animation()
{
    m_Variables.clear();

    if (m_AnimationTimer != nullptr)
    {
        m_AnimationTimer->Release();
    }

    if (m_AnimationManager != nullptr)
    {
        m_AnimationManager->Release();
    }
}

std::weak_ptr<anim::AnimationVariable> anim::Animation::CreateVariable(
    double initialValue,
    std::optional<uint32_t> tag )
{
    std::weak_ptr<AnimationVariable> ret;

    if (m_AnimationManager != nullptr)
    {
        std::shared_ptr<AnimationVariable> var = std::make_shared<AnimationVariable>(
            m_AnimationManager,
            initialValue,
            tag );

        if (var->IsOk())
        {
			m_Variables.emplace(var->GetTag(), var);
            return m_Variables[var->GetTag()];
        }
    }

    return ret;
}

std::weak_ptr<anim::Storyboard> anim::Animation::CreateStoryboard(std::optional<uint32_t> tag)
{
    std::weak_ptr<Storyboard> ret;

    if (m_AnimationManager != nullptr)
    {
        std::shared_ptr<Storyboard> sb = std::make_shared<Storyboard>(
            m_AnimationManager,
            tag);

        if (sb->IsOk())
        {
            m_Storyboards.emplace(sb->GetTag(), sb);
            return m_Storyboards[sb->GetTag()];
        }
    }

    return ret;
}

bool anim::Animation::SetTimerEventHandler(IUIAnimationTimerEventHandler *eventHandler)
{
    if (m_AnimationTimer != nullptr)
    {
        HRESULT hr = m_AnimationTimer->SetTimerEventHandler(eventHandler);
        return SUCCEEDED(hr);
    }
    return false;
}

std::optional<double> anim::Animation::GetTime()
{
    double secondsNow;
    HRESULT hr = m_AnimationTimer->GetTime(&secondsNow);
    if (SUCCEEDED(hr))
    {
        return secondsNow;
    }
    return std::nullopt;
}

std::weak_ptr<anim::AnimationVariable> anim::Animation::GetVariable(std::uint32_t tag) const
{
    auto it = m_Variables.find(tag);
    if (it != m_Variables.end())
    {
        return it->second;
    }
	return std::weak_ptr<AnimationVariable>();
}

std::weak_ptr<anim::AnimationVariable> anim::Animation::GetVariable(IUIAnimationVariable* variable) const
{
	std::uint32_t tag = 0;
    HRESULT hr = variable->GetTag(nullptr, &tag);
    if(SUCCEEDED(hr))
    {
        return GetVariable(tag);
	}
    
	return std::weak_ptr<AnimationVariable>();
}

std::weak_ptr<anim::Storyboard> anim::Animation::GetStoryboard(std::uint32_t tag) const
{
    auto it = m_Storyboards.find(tag);
    if (it != m_Storyboards.end())
    {
        return it->second;
    }
    return std::weak_ptr<Storyboard>();
}

std::weak_ptr<anim::Storyboard> anim::Animation::GetStoryboard(IUIAnimationStoryboard* variable) const
{
    std::uint32_t tag = 0;
    HRESULT hr = variable->GetTag(nullptr, &tag);
    if (SUCCEEDED(hr))
    {
        return GetStoryboard(tag);
    }
	return std::weak_ptr<Storyboard>();
}

void anim::Animation::CreateAnimationManager()
{
    m_Error = CoCreateInstance(
        CLSID_UIAnimationManager,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&m_AnimationManager));
}

void anim::Animation::CreateAnimationTimer()
{
    if (SUCCEEDED(m_Error))
    {
        m_Error = CoCreateInstance(
            CLSID_UIAnimationTimer,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&m_AnimationTimer));
    }
}

void anim::Animation::InitializeTimerUpdateHandler()
{
    if (SUCCEEDED(m_Error))
    {
        IUIAnimationTimerUpdateHandler *timerUpdateHandler;
        HRESULT hr = m_AnimationManager->QueryInterface(
            IID_PPV_ARGS(&timerUpdateHandler));

        if (SUCCEEDED(hr))
        {
            hr = m_AnimationTimer->SetTimerUpdateHandler(
                timerUpdateHandler,
                UI_ANIMATION_IDLE_BEHAVIOR_DISABLE // timer will shut itself off when there are no animations playing
            );
            timerUpdateHandler->Release();
        }
    }
}
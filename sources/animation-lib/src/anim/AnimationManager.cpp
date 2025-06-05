#include "anim/AnimationManager.h"

anim::AnimationManager::AnimationManager()
{
    CreateAnimationManager();
    CreateAnimationTimer();
    InitializeTimerUpdateHandler();
}

anim::AnimationManager::~AnimationManager()
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

std::weak_ptr<anim::AnimationVariable> anim::AnimationManager::CreateVariable(double initialValue)
{
    std::weak_ptr<AnimationVariable> ret;

    if (m_AnimationManager != nullptr)
    {
        std::shared_ptr<AnimationVariable> var = std::make_shared<AnimationVariable>(
            m_AnimationManager,
            initialValue,
            m_NextVariableId++);

        if (var->IsOk())
        {
            m_Variables.push_back(var);
            ret = var;
        }
    }

    return ret;
}

std::weak_ptr<anim::Storyboard> anim::AnimationManager::CreateStoryboard()
{
    std::weak_ptr<Storyboard> ret;

    if (m_AnimationManager != nullptr)
    {
        std::shared_ptr<Storyboard> sb = std::make_shared<Storyboard>(m_AnimationManager, m_NextStoryBoardId++);
        if (sb->IsOK())
        {
            m_Storyboard = sb;
            ret = m_Storyboard;
        }
    }

    return ret;
}

bool anim::AnimationManager::SetTimerEventHandler(IUIAnimationTimerEventHandler *eventHandler)
{
    if (m_AnimationTimer != nullptr)
    {
        HRESULT hr = m_AnimationTimer->SetTimerEventHandler(eventHandler);
        return SUCCEEDED(hr);
    }
    return false;
}

std::optional<double> anim::AnimationManager::GetTime()
{
    double secondsNow;
    HRESULT hr = m_AnimationTimer->GetTime(&secondsNow);
    if (SUCCEEDED(hr))
    {
        return secondsNow;
    }
    return std::nullopt;
}

void anim::AnimationManager::CreateAnimationManager()
{
    m_Error = CoCreateInstance(
        CLSID_UIAnimationManager,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&m_AnimationManager));
}

void anim::AnimationManager::CreateAnimationTimer()
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

void anim::AnimationManager::InitializeTimerUpdateHandler()
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
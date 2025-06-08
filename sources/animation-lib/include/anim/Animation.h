#pragma once

#include "anim/AnimationVariable.h"
#include "anim/TransitionLibrary.h"
#include "anim/Storyboard.h"

#include <uianimation.h>

#include <memory>
#include <unordered_map>
#include <vector>
#include <optional>

namespace anim
{
    class Animation
    {
    public:
        Animation();
        ~Animation();

        std::weak_ptr<AnimationVariable> CreateVariable(double initialValue, std::optional<uint32_t> tag = std::nullopt);
        std::weak_ptr<Storyboard> CreateStoryboard();
        bool SetTimerEventHandler(IUIAnimationTimerEventHandler* eventHandler);
        std::optional<double> GetTime();

        const anim::TransitionLibrary& GetTransitionLibrary() const { return m_TransitionLibrary; }

    private:
        void CreateAnimationManager();
        void CreateAnimationTimer();
        void InitializeTimerUpdateHandler();

        HRESULT m_Error{ E_NOT_SET };
        IUIAnimationManager* m_AnimationManager{ nullptr };
        IUIAnimationTimer* m_AnimationTimer{ nullptr };
        anim::TransitionLibrary m_TransitionLibrary;

        std::unordered_map<std::int32_t, std::shared_ptr<AnimationVariable>> m_Variables;

        int m_NextStoryBoardId{ 0 };
        std::shared_ptr<Storyboard> m_Storyboard;
    };
}
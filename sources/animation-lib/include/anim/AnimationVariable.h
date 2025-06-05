#pragma once

#include <uianimation.h>

#include <optional>

namespace anim
{
    class AnimationVariable
    {
    public:
        AnimationVariable(IUIAnimationManager* manager, double initialValue, int id);
        ~AnimationVariable();

        int GetId() const { return m_Id; }
        std::optional<double> GetDouble();
        std::optional<int> GetInteger();
        bool IsOk() const;

        IUIAnimationVariable* GetVariable() const { return m_AnimationVariable; }

    private:
        int m_Id;
        HRESULT m_Error;

        IUIAnimationVariable* m_AnimationVariable{ nullptr };
    };
}
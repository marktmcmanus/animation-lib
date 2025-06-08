#pragma once

#include "anim/VariableChangeHandler.h"
#include "anim/VariableIntegerChangeHandler.h"

#include <uianimation.h>

#include <optional>

namespace anim
{
    class AnimationVariable
    {
    public:
        AnimationVariable(IUIAnimationManager* manager, double initialValue, std::optional<uint32_t> tag);
        ~AnimationVariable();

        HRESULT SetChangeHandler(VariableChangeHandler* handler);
        HRESULT SetChangeHandler(VariableIntegerChangeHandler* handler);

        std::uint32_t GetTag() const { return m_Tag; }
        std::optional<double> GetDouble();
        std::optional<int> GetInteger();
        bool IsOk() const;

        IUIAnimationVariable* GetVariable() const { return m_AnimationVariable; }

    private:
        std::uint32_t m_Tag{ 0 };
        HRESULT m_Error;

		static std::uint32_t m_NextId;

        IUIAnimationVariable* m_AnimationVariable{ nullptr };
    };
}
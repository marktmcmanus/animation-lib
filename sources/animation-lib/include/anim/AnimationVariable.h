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
        AnimationVariable(
            IUIAnimationManager* manager, 
            double initialValue, 
            std::optional<uint32_t> tag);
        ~AnimationVariable();

        HRESULT SetChangeHandler(VariableChangeHandler* handler);
        HRESULT SetChangeHandler(VariableIntegerChangeHandler* handler);

        std::uint32_t GetTag() const { return m_Tag; }
        std::optional<double> GetDouble();
        std::optional<double> GetFinalDouble();
        std::optional<double> GetPreviousDouble();
        std::optional<int> GetInteger();
        std::optional<int> GetFinalInteger();
        std::optional<int> GetPreviousInteger();
        IUIAnimationStoryboard* GetStoryboard();
		bool SetLowerBounds(double lowerBound);
		bool SetUpperBounds(double upperBound);
		bool SetRoundingMode(UI_ANIMATION_ROUNDING_MODE roundingMode);

        bool IsOk() const { return m_AnimationVariable != nullptr; }
		HRESULT GetError() const { return m_Error; }

        IUIAnimationVariable* GetVariable() const { return m_AnimationVariable; }

    private:
        std::uint32_t m_Tag{ 0 };
        HRESULT m_Error;

        IUIAnimationVariable* m_AnimationVariable{ nullptr };

        static std::uint32_t m_NextId;
    };
}
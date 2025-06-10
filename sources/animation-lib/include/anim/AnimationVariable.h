#pragma once

#include "anim/VariableChangeHandler.h"
#include "anim/VariableIntegerChangeHandler.h"

#include <uianimation.h>

#include <optional>

namespace anim
{
    /**
     * @brief Represents an animation variable that can be managed by the `Animation` class.
     * 
     * The `AnimationVariable` class creates and managers an `IUIAnimationVariable` object. When contructing an
     * AnimationVariable an optional tag can be given, if the tag is not given one will be generated. Generated tags
     * start with the maximum value of `std::uint32_t` and are decremented for each new `AnimationVariable` created.
     * While you can create an `AnimationVariable` directly is it recommended to use the `Animation::CreateVariable()` 
     * function to create and manage `AnimationVariables`.
     */
    class AnimationVariable
    {
    public:
        /**
         * @brief Constructs an `AnimationVariable` with the given manager and initial value.
         * 
         * If a tag is not provided, a unique tag will be generated.
         * 
         * @param manager The UI Animation Manager to use for this variable.
         * @param initialValue The initial value of the animation variable.
         * @param tag Optional tag for the variable. If not provided, a unique tag will be generated.
         * 
         * @remarks It is recommended to use the `Animation::CreateVariable()` function to create and manage `AnimationVariable` instances.
         */
        AnimationVariable(
            IUIAnimationManager* manager, 
            double initialValue, 
            std::optional<uint32_t> tag);

        /**
        * @brief Destroys the `AnimationVariable` object and releases resources.
        */
        ~AnimationVariable();

        /**
         * @brief Sets the handler to be called when a variable changes.
         * 
         * The `VariableChangeHandler` will receive updated variables as `double` values. 
         * 
         * @param handler A pointer to a `VariableChangeHandler` that will handle variable change notifications.
         * @return An HRESULT value indicating success or failure of setting the handler.
         */
        HRESULT SetChangeHandler(VariableChangeHandler* handler);

        /**
         * @brief Sets the handler to be called when a variable changes.
         *
         * The `VariableIntegerChangeHandler` will receive updated variables as `int` values.
         *
         * @param handler A pointer to a `VariableIntegerChangeHandler` that will handle variable change notifications.
         * @return An HRESULT value indicating success or failure of setting the handler.
         */
        HRESULT SetChangeHandler(VariableIntegerChangeHandler* handler);

        /**
         * @brief Retrieves the value of the tag.
         * 
         * The returned tag can be used to access the variable in the `Animation` class.
         * 
         * @return The current value of the tag as an unsigned 32-bit integer.
         */
        std::uint32_t GetTag() const { return m_Tag; }

        /**
         * @brief Retrieves the value of the variable as a double.
         * @return An optional containing the double value if available; otherwise, an empty optional.
         * @remarks If an empty optional is return call `GetError()` to retrieve the error code.
         */
        std::optional<double> GetDouble();

        /**
         * @brief Retrieves the final value of the variable as a double.
         * @return An optional containing the final double value if available; otherwise, an empty optional.
         * @remarks If an empty optional is returned, call `GetError()` to retrieve the error code.
         */
        std::optional<double> GetFinalDouble();

        /**
         * @brief Retrieves the previous value of the variable as a double.
         * @return An optional containing the previous double value if available; otherwise, an empty optional.
         * @remarks If an empty optional is returned, call `GetError()` to retrieve the error code.
         */
        std::optional<double> GetPreviousDouble();

        /**
         * @brief Retrieves the value of the variable as an integer.
         * @return An optional containing the integer value if available; otherwise, an empty optional.
         * @remarks If an empty optional is returned, call `GetError()` to retrieve the error code.
         */
        std::optional<int> GetInteger();

        /**
         * @brief Retrieves the final value of the variable as an integer.
         * @return An optional containing the final integer value if available; otherwise, an empty optional.
         * @remarks If an empty optional is returned, call `GetError()` to retrieve the error code.
         */
        std::optional<int> GetFinalInteger();

        /**
         * @brief Retrieves the previous value of the variable as an integer.
         * @return An optional containing the previous integer value if available; otherwise, an empty optional.
         * @remarks If an empty optional is returned, call `GetError()` to retrieve the error code.
         */
        std::optional<int> GetPreviousInteger();

        /**
         * @brief Retrieves a pointer to the `IUIAnimationStoryboard` currently animating this variable.
         * 
         * The returned can ve used with the `Animation::GetStoryboard()` function to retrieve the `Storyboard` 
         * instance managed by the `Animation` class.
         * 
         * @return A pointer to an `IUIAnimationStoryboard` currently animating this variable.
         */
        IUIAnimationStoryboard* GetStoryboard();

        /**
         * @brief Sets the lower bounds for this variable.
         * @param lowerBound The lower bounds.
         * @return `true` if the lower bound was set successfully; otherwise, `false`.
         * @remarks If `false` is returned, call `GetError()` to retrieve the error code.
         */
        bool SetLowerBounds(double lowerBound);

        /**
         * @brief Sets the upper bounds for this variable.
         * @param upperBound The upper bounds.
         * @return `true` if the upper bound was set successfully; otherwise, `false`.
         * @remarks If `false` is returned, call `GetError()` to retrieve the error code.
         */
        bool SetUpperBounds(double upperBound);

        /**
         * @brief Sets the rounding mode for UI animation calculations.
         * @param roundingMode The rounding mode to be applied to UI animation values.
         * @return Returns true if the rounding mode was set successfully; otherwise, returns false.
         * @remarks If `false` is returned, call `GetError()` to retrieve the error code.
         */
        bool SetRoundingMode(UI_ANIMATION_ROUNDING_MODE roundingMode);

        /**
         * @brief Checks whether the `AnimationVariable` is valid.
         * @return true if the `AnimationVariable` valid and ready for use; otherwise, false.
         */
        bool IsOk() const { return m_AnimationVariable != nullptr; }

        /**
         * @brief Retrieves the last error code produced for a call to a function in `AnimationVariable`.
         * @return The HRESULT error code indicating the reason for failure.
         * @remarks Call this function if any of the other function call in `AnimationVariable` fail.
         */
        HRESULT GetError() const { return m_Error; }

        /**
         * @brief Retrieves the underlying `IUIAnimationVariable` object.
         * 
         * This function is mostly used internally and should only be called when functinality of the 
         * UI Animation Manager is required that is currently not implemented in animation-lib.
         * 
         * @return A pointer to the `IUIAnimationVariable` object managed by this `AnimationVariable` instance.
         * @remarks If you do call this and plan to store the pointer be sure to call `AddRef()` and `Release()` 
         * on the returned pointer to manage its lifetime correctly.
         */
        IUIAnimationVariable* GetVariable() const { return m_AnimationVariable; }

    private:
        std::uint32_t m_Tag{ 0 };
        HRESULT m_Error;
        IUIAnimationVariable* m_AnimationVariable{ nullptr };
        static std::uint32_t m_NextId;
    };
}
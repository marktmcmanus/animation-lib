#pragma once

#include "anim/AnimationVariable.h"
#include "anim/transition/Transition.h"

#include <uianimation.h>

#include <memory>
#include <optional>

namespace anim
{
    /**
     * @brief Represents a storyboard for managing and controlling UI animation transitions using the Windows Animation Manager.
     * 
     * The `Storyboad` class creates and manages an `IUIAnimationStoryboad` object. When contructing a
     * `Storyboard` an optional tag can be given, if the tag is not given one will be generated. Generated tags
     * start with the maximum value of `std::uint32_t` and are decremented for each new `Storyboard` created.
     * While you can create a `Storyboard` directly is it recommended to use the `Animation::CreateStoryboard()` 
     * function to create and manage `Storyboards`.
     */
    class Storyboard
    {
    public:
        using TransitionOptRef = std::optional<std::reference_wrapper<anim::transition::Transition>>;

        /**
         *  @brief Constructs a `Storyboard` with the given animation manager and initial value.
         * 
         * If a tag is not provided, a unique tag will be generated.
         * 
         * @param manager Pointer to the IUIAnimationManager that manages the storyboard.
         * @param tag An optional tag value to associate with the storyboard. If not provided, a tag will be generated.
         * 
         * @remarks It is recommended to use the `Animation::CreateStoryboard()` function to create and manage `Storyboard` instances.
         */
        Storyboard(IUIAnimationManager* manager, std::optional<uint32_t> tag);

        /**
         * @brief Destroys the `Storyboard` object and releases any associated resources.
         */
        ~Storyboard();

        /**
         * @brief Retrieves the value of the tag.
         *
         * The returned tag can be used to access the storyboard in the `Animation` class.
         *
         * @return The value of the tag.
         */
        std::uint32_t GetTag() const { return m_Tag; }

        /**
         * @brief Checks whether the `Storyboard` is valid.
         * @return true if the `Storyboard` valid and ready for use; otherwise, false.
         */
        bool IsOk() const { return m_Storyboard != nullptr; }

        /**
         * @brief Adds a transition to an animation variable, optionally specifying an offset and a transition to follow.
         * 
         * Add a transition to the storyboard for a specific animation variable. The transition can be applied immediately or 
         * after a specified offset. If `offset` is specified and `afterTransition` is not, the new transition will start at the
         * offset from the beginning of the storyboard. If `offset` and `afterTransition` are both specified, the new transition 
         * will start at the offset from the end of the `afterTransition`.
         * 
         * @param transition A weak pointer to the transition to be added. Use `TransitionLibrary` to create transitions.
         * @param var The animation variable to which the transition will be applied.
         * @param offset The time offset (in seconds) at which the transition should start. Defaults to 0.0.
         * @param afterTransition An optional reference to a transition that this transition should follow. Defaults to no dependency.
         * @return true if the transition was successfully added; false otherwise.
         * @remarks If `false` is returned, call `GetError()` to retrieve the error code.
         */
        bool AddTransition(
            std::weak_ptr<anim::transition::Transition> transition,
            AnimationVariable& var,
            double offset = 0.0,
            TransitionOptRef afterTransition = std::nullopt);

        /**
         * @brief Schedules the Storyboard for play.
         * @param now The current time, this should be from the animation time which can be retreived by calling `Animation::GetTime()`.
         * @return True if the operation was successfully scheduled; otherwise, false.
         * @remarks If `false` is returned, call `GetError()` to retrieve the error code.
         */
        bool Schedule(double now);

        /**
         * @brief Terminates the storyboard.
         * @return true if the abandon operation was successful; otherwise, false.
         * @remarks If `false` is returned, call `GetError()` to retrieve the error code.
         */
        bool Abandon();

        /**
         * @brief Completes the current iteration of a keyframe loop that is in progress and continues with the storyboard
         * @return true if a conclusion was successful; otherwise, false.
         * @remarks If `false` is returned, call `GetError()` to retrieve the error code.
         */
        bool Conclude();

        /**
         * @brief Finishes the storyboard within the specified time, compressing the storyboard if necessary.
         * @param completionDeadline The time limit, in seconds, by which the operation should be completed.
         * @return true if the successful; otherwise, false.
         * @remarks If `false` is returned, call `GetError()` to retrieve the error code.
         */
        bool Finish(double completionDeadline);

        /**
         * @brief Retrieves the current status of the animation storyboard.
         * @return An optional value containing the current UI_ANIMATION_STORYBOARD_STATUS if available; otherwise, an empty optional.
         * @remarks If an empty optional is returned, call `GetError()` to retrieve the error code.
         */
        std::optional<UI_ANIMATION_STORYBOARD_STATUS> GetStatus();

        /**
         * @brief Holds the specified animation variable, preventing it from being updated until the storyboard ends.
         * @param var Reference to the AnimationVariable to be held.
         * @return true if the variable was successfully held; false otherwise.
         * @remarks If `false` is returned, call `GetError()` to retrieve the error code.
         */
        bool HoldVariable(AnimationVariable& var);

        /**
         * @brief Retrieves the elapsed time in seconds.
         * @return An optional containing the elapsed time in seconds as a double, or an empty optional if the elapsed time is not available.
         * @remarks If an empty optional is returned, call `GetError()` to retrieve the error code.
         */
        std::optional<double> GetElapsedTime();

        /**
         * @brief Sets the longest acceptable delay value.
         * @param delay The maximum acceptable delay, in seconds.
         * @return True if the delay was set successfully; otherwise, false.
         * @remarks If `false` is returned, call `GetError()` to retrieve the error code.
         */
        bool SetLongestAcceptableDelay(double delay);

        /**
         * @brief Sets the event handler for storyboard events.
         * 
         * While any object that implements the `IUIAnimationStoryboardEventHandler` interface can be used, 
         * animation-lib provides the `StoryboardEventHandler` class for this purpose.
         * 
         * @param eventHandler A pointer to an object that implements the IUIAnimationStoryboardEventHandler interface to receive storyboard event notifications.
         * @return Returns true if the event handler was set successfully; otherwise, returns false.
         */
        bool SetEventHandler(IUIAnimationStoryboardEventHandler* eventHandler);

        /**
         * @brief Retrieves the last error code produced for a call to a function in `AnimationVariable`.
         * @return The HRESULT error code indicating the reason for failure.
         * @remarks Call this function if any of the other function call in `AnimationVariable` fail.
         */
        HRESULT GetError() const { return m_Error; }

    private:
        std::optional<UI_ANIMATION_KEYFRAME> GetOrCreateKeyFrame(double offset);

        std::uint32_t m_Tag{ 0 };
        HRESULT m_Error;
        IUIAnimationStoryboard* m_Storyboard{ nullptr };
        std::unordered_map<double, UI_ANIMATION_KEYFRAME> m_KeyFrames;

        static std::uint32_t m_NextId;
    };
}
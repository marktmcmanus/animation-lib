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
    /**
     * @brief Represents an animation system that manages animation variables, storyboards, and timer events.
     * 
     * The `Animation` class uses the <a href="https://learn.microsoft.com/en-us/windows/win32/api/_uianimation/">Windows UI Animation Manager</a> to 
     * create and manage animations. It allows for the creation of animation variables and storyboards, and provides methods to set timer event handlers 
     * and retrieve current time.
     * 
     * Animations currently only supports Timer-Driven Animations (rather than Application-Driven Animations).
     */
    class Animation
    {
    public:
        /**
         * @brief Constructs an `Animation` object and initializes the animation manager and timer.
         * 
         * This constructor sets up the necessary components for animation management, including the animation manager and timer.
         */
        Animation();

        /**
         * @brief Destroys the `Animation` object and releases resources.
         * 
         * This destructor cleans up the animation manager and timer, ensuring that all resources are properly released.
         */
        ~Animation();

        /**
         * @brief Creates a new `AnimationVariable` with the specified initial value and an optional tag.
         * @param initialValue The initial value to assign to the `AnimationVariable`.
         * @param tag An optional tag to associate with the `AnimationVariable`. If not provided, a default tag will be used. 
         * For more information see the documentation for `AnimationVariable`.
         * @return A std::weak_ptr to the newly created `AnimationVariable`.
         * @remarks This is the prefered way to create and add an `AnimationVariable` to an animation (rather than 
         * creating the `AnimationVariable` directly).
         */
        std::weak_ptr<AnimationVariable> CreateVariable(double initialValue, std::optional<uint32_t> tag = std::nullopt);

        /**
         * @brief Creates a new `Storyboard` with an optional tag.
         * @param tag An optional tag to associate with the `Storyboard`. If not provided, a default tag will be used.
         * @return A std::weak_ptr to the newly created `Storyboard`.
         * @remarks This is the prefered way to create and add a `Storyboard` to an animation (rather than 
         * creating the `Storyboard` directly).
         */
        std::weak_ptr<Storyboard> CreateStoryboard(std::optional<uint32_t> tag = std::nullopt);

        /**
         * @brief Sets the event handler for timer events.
         * @param eventHandler A pointer to the IUIAnimationTimerEventHandler interface that will handle timer events.
         * @return true if the event handler was set successfully; false otherwise.
         */
        bool SetTimerEventHandler(IUIAnimationTimerEventHandler* eventHandler);

        /**
         * @brief Retrieves the current time from the Animation manager.
         * The time value return here can be used in the `Storyboard::Schedule()` function.
         * @return An optional double containing the current time if it can be determined; otherwise, an empty optional.
         */
        std::optional<double> GetTime();

        /**
         * @brief Retrieves a weak pointer to the `AnimationVariable` associated with the specified tag.
         * @param tag The unique identifier (tag) of the `AnimationVariable` to retrieve.
         * @return A std::weak_ptr to the `AnimationVariable` corresponding to the given tag. If no variable is found, the returned weak pointer will be empty.
         */
        std::weak_ptr<AnimationVariable> GetVariable(std::uint32_t tag) const;

        /**
         * @brief Retrieves a std::weak_ptr to an `AnimationVariable` corresponding to the given `IUIAnimationVariable` pointer.
         * @param variable A pointer to the `IUIAnimationVariable` for which to obtain the `AnimationVariable`.
         * @return A std::weak_ptr to the associated `AnimationVariable` object. If no variable is found, the returned weak pointer will be empty.
         */
        std::weak_ptr<AnimationVariable> GetVariable(IUIAnimationVariable* variable) const;

        /**
         * @brief Retrieves a weak pointer to the `Storyboard` associated with the specified tag.
         * @param tag The tag identifying the desired `Storyboard`.
         * @return A std::weak_ptr to the `Storyboard` corresponding to the given tag. If no such `Storyboard` exists, the returned weak pointer will be empty.
         */
        std::weak_ptr<Storyboard> GetStoryboard(std::uint32_t tag) const;

        /**
         * @brief Retrieves a weak pointer to a `Storyboard` object associated with the given `IUIAnimationStoryboard` pointer.
         * @param variable A pointer to an `IUIAnimationStoryboard` for which to obtain the corresponding `Storyboard`.
         * @return A std::weak_ptr to the associated `Storyboard` object. If no such `Storyboard` exists, the returned weak pointer will be empty.
         */
        std::weak_ptr<Storyboard> GetStoryboard(IUIAnimationStoryboard* variable) const;


    private:
        void CreateAnimationManager();
        void CreateAnimationTimer();
        void InitializeTimerUpdateHandler();

        HRESULT m_Error{ E_NOT_SET };
        IUIAnimationManager* m_AnimationManager{ nullptr };
        IUIAnimationTimer* m_AnimationTimer{ nullptr };

        std::unordered_map<std::uint32_t, std::shared_ptr<AnimationVariable>> m_Variables;
        std::unordered_map<std::uint32_t, std::shared_ptr<Storyboard>> m_Storyboards;
    };
}
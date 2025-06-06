#include "anim/TransitionLibrary.h"

#include "anim/transition/AccelerateDecelerate.h"
#include "anim/transition/Constant.h"
#include "anim/transition/Cubic.h"
#include "anim/transition/Discrete.h"
#include "anim/transition/Instantaneous.h"
#include "anim/transition/Linear.h"
#include "anim/transition/LinearFromSpeed.h"
#include "anim/transition/ParabolicFromAcceleration.h"
#include "anim/transition/Reversal.h"
#include "anim/transition/SinusoidalFromRange.h"
#include "anim/transition/SinusoidalFromVelocity.h"
#include "anim/transition/SmoothStop.h"

anim::TransitionLibrary::TransitionLibrary()
{
    HRESULT hr = CoCreateInstance(
        CLSID_UIAnimationTransitionLibrary,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&m_TransitionLibrary));

    if (FAILED(hr))
    {
        m_TransitionLibrary = nullptr;
    }
}

anim::TransitionLibrary::~TransitionLibrary()
{
    if (m_TransitionLibrary != nullptr)
    {
        m_TransitionLibrary->Release();
    }
}

std::shared_ptr<anim::transition::Transition> anim::TransitionLibrary::CreateAccelerateDecelerateTransition(
    double duration,
    double finalValue,
    double accelerationRatio,
    double decelerationRatio ) const
{
    return std::make_shared <anim::transition::AccelerateDecelerate>(
        m_TransitionLibrary,
        duration,
        finalValue,
        accelerationRatio,
        decelerationRatio );
}

std::shared_ptr<anim::transition::Transition> anim::TransitionLibrary::CreateConstantTransition(
    double duration ) const
{
    return std::make_shared<anim::transition::Constant>(
        m_TransitionLibrary,
        duration );
}

std::shared_ptr<anim::transition::Transition> anim::TransitionLibrary::CreateCubicTransition(
    double duration,
    double finalValue,
    double finalVelocity ) const
{
    return std::make_shared<anim::transition::Cubic>(
        m_TransitionLibrary,
        duration,
        finalValue,
        finalVelocity );
}

std::shared_ptr<anim::transition::Transition> anim::TransitionLibrary::CreateDiscreteTransition(
    double delay,
    double finalValue,
    double hold ) const
{
    return std::make_shared<anim::transition::Discrete>(
        m_TransitionLibrary,
        delay,
        finalValue,
        hold );
}

std::shared_ptr<anim::transition::Transition> anim::TransitionLibrary::CreateInstantaneousTransition(
    double finalValue) const
{
    return std::make_shared<anim::transition::Instantaneous>(
        m_TransitionLibrary,
        finalValue );
}

std::shared_ptr<anim::transition::Transition> anim::TransitionLibrary::CreateLinearTransition(
    double duration,
    double finalValue) const
{
    return std::make_shared<anim::transition::Linear>(
        m_TransitionLibrary,
        duration,
        finalValue);
}

std::shared_ptr<anim::transition::Transition> anim::TransitionLibrary::CreateLinearTransitionFromSpeed(
    double duration,
    double finalValue) const
{
    return std::make_shared<anim::transition::LinearFromSpeed>(
        m_TransitionLibrary,
        duration,
        finalValue);
}

std::shared_ptr<anim::transition::Transition> anim::TransitionLibrary::CreateParabolicTransitionFromAcceleration(
    double finalValue,
    double finalSpeed,
    double acceleration) const
{
    return std::make_shared<anim::transition::ParabolicFromAcceleration>(
        m_TransitionLibrary,
        finalValue,
        finalSpeed,
        acceleration);
}

std::shared_ptr<anim::transition::Transition> anim::TransitionLibrary::CreateReversalTransition(
    double duration) const
{
    return std::make_shared<anim::transition::Reversal>(
        m_TransitionLibrary,
        duration);
}

std::shared_ptr<anim::transition::Transition> anim::TransitionLibrary::CreateSinusoidalTransitionFromRange(
    double duration,
    double minimumValue,
    double maximumValue,
    double period,
    UI_ANIMATION_SLOPE slope) const
{
    return std::make_shared<anim::transition::SinusoidalFromRange>(
        m_TransitionLibrary,
        duration,
        minimumValue,
        maximumValue,
        period,
        slope);
}

std::shared_ptr<anim::transition::Transition> anim::TransitionLibrary::CreateSinusoidalTransitionFromVelocity(
    double duration,
    double period ) const
{
    return std::make_shared<anim::transition::SinusoidalFromVelocity>(
        m_TransitionLibrary,
        duration,
        period);
}

std::shared_ptr<anim::transition::Transition> anim::TransitionLibrary::CreateSmoothStopTransition(
    double maximumDuration,
    double finalValue) const
{
    return std::make_shared<anim::transition::SmoothStop>(
        m_TransitionLibrary,
        maximumDuration,
        finalValue);
}
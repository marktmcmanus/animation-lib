#include "anim/TransitionLibrary.h"

#include "anim/transition/AccelerateDecelerate.h"
#include "anim/transition/Constant.h"
#include "anim/transition/Cubic.h"
#include "anim/transition/Discrete.h"

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
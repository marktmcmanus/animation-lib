#include "anim/AnimationTimerEventHandler.h"


ULONG anim::AnimationTimerEventHandler::AddRef()
{
    return InterlockedIncrement(&m_Ref);
}

ULONG anim::AnimationTimerEventHandler::Release()
{
    ULONG refCount = InterlockedDecrement(&m_Ref);
    if (0 == refCount)
    {
        delete this;
    }
    return refCount;
}

HRESULT anim::AnimationTimerEventHandler::QueryInterface(REFIID riid, LPVOID *ppvObj)
{
    if (!ppvObj)
    {
        return E_INVALIDARG;
    }

    *ppvObj = NULL;

    if (riid == IID_IUnknown || riid == IID_IUIAnimationTimerEventHandler)
    {
        *ppvObj = (LPVOID)this;
        AddRef();
        return NOERROR;
    }

    return E_NOINTERFACE;
}

HRESULT anim::AnimationTimerEventHandler::OnPostUpdate()
{
    return S_OK;
}

HRESULT anim::AnimationTimerEventHandler::OnPreUpdate()
{
    return S_OK;
}

HRESULT anim::AnimationTimerEventHandler::OnRenderingTooSlow(UINT32 /* framesPerSecond */)
{
    return S_OK;
}
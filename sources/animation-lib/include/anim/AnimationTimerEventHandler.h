#pragma once

#include <uianimation.h>

namespace anim
{
    class AnimationTimerEventHandler : public IUIAnimationTimerEventHandler
    {
    public:
        AnimationTimerEventHandler() = default;

        // IUnknown
        ULONG AddRef() override;
        ULONG Release() override;
        HRESULT QueryInterface(REFIID riid, LPVOID* ppvObj) override;

        // IUIAnimationTimerEventHandler
        virtual HRESULT OnPostUpdate() override;
        virtual HRESULT OnPreUpdate() override;
        virtual HRESULT OnRenderingTooSlow(UINT32 framesPerSecond) override;

    private:
        //wxWeakRef<MainWindow> m_MainWindow;
        LONG m_Ref{ 0 };
    };
}

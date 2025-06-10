#pragma once

#define _ANIM_IUNKNOWN_DECL											\
public:																\
	ULONG AddRef() override;										\
	ULONG Release() override;										\
	HRESULT QueryInterface(REFIID riid, LPVOID* ppvObj) override;	\
private:															\
	LONG m_Ref{ 0 };

#define _ANIM_IUNKNOWN_IMPL(className, iface)						\
	ULONG className::AddRef()										\
	{																\
			return InterlockedIncrement(&m_Ref);					\
	}																\
	ULONG className::Release()										\
	{																\
		LONG ref = InterlockedDecrement(&m_Ref);					\
		if (ref == 0)												\
		{															\
			delete this;											\
		}															\
		return ref;													\
	}																\
	HRESULT className::QueryInterface(REFIID riid, LPVOID* ppvObj)	\
	{																\
		if (riid == IID_IUnknown || riid == __uuidof(iface))		\
		{															\
			*ppvObj = static_cast<iface*>(this);					\
			AddRef();												\
			return S_OK;											\
		}															\
		*ppvObj = nullptr;											\
		return E_NOINTERFACE;										\
	}
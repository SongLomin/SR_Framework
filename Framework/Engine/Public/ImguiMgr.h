#pragma once
#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CImguiMgr final : public CBase
{
	DECLARE_SINGLETON(CImguiMgr)

public:
	CImguiMgr();
	virtual ~CImguiMgr() = default;

public:
	HRESULT Initialize();
	void Tick(float fTimeDelta);
	HRESULT Render();

public:
	HRESULT ImGuiImplHandle(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	bool show_demo_window;	

public:
	virtual void Free();
};

END
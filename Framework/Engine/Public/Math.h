#pragma once
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CMath final : public CBase
{
public:
	CMath();
	~CMath();

public:
	static HRESULT WorldToScreen(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3* pos, D3DXVECTOR3* out);
	static HRESULT ScreenToWorld(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3* pos, D3DXVECTOR3* out);
};

END
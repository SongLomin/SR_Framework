#pragma once

#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CMath_Utillity final : public CBase
{
public:
	CMath_Utillity();
	~CMath_Utillity();

public:
	static HRESULT WorldToScreen(D3DXVECTOR3* pos, D3DXVECTOR3* out);
	static HRESULT ScreenToWorld(D3DXVECTOR3* pos, D3DXVECTOR3* out);
};

END
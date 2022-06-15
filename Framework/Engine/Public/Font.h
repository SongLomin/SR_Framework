#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CFont final : public CComponent
{
public:
	CFont();
	virtual ~CFont() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);


private:
	//LPD3DXFONT				m_pFont = nullptr;

public:
	static CFont* Create();
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END
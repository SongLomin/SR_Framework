#pragma once
#include "Base.h"

BEGIN(Engine)

class Get_Lucky
{
	DECLARE_SINGLETON(Get_Lucky)

public:
	Get_Lucky() = default;
	virtual ~Get_Lucky() = default;

public:
	void Team_EverSpace();

private:
	LPD3DXBUFFER	m_pAdj = nullptr;
	LPD3DXBUFFER	m_pMtrl = nullptr;
	LPD3DXBUFFER	m_pEffectInstances = nullptr;
	DWORD			m_iNumMtrl = 0;
	ID3DXMesh* m_pMesh = nullptr;
	_ulong			m_dwNumSubsets = 0;

public:
	virtual void Free();
};

END

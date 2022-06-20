#pragma once

#include "Base.h"

BEGIN(Engine)

class CPicking final : public CBase
{
	DECLARE_SINGLETON(CPicking);
public:
	CPicking();
	virtual ~CPicking() = default;

public:
	HRESULT Initialize(HWND hWnd, LPDIRECT3DDEVICE9 pGraphic_Device);
	void Compute_RayInWorldSpace();

	_bool Picking(class CVIBuffer* pVIBuffer, class CTransform* pTransform, _float3* pOut);

private:
	HWND				m_hWnd;
	LPDIRECT3DDEVICE9	m_pGraphic_Device = nullptr;

private:
	_float3				m_vRayDir, m_vRayPos;


public:
	virtual void Free() override;
};

END
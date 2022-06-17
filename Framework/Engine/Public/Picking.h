#pragma once

#include "Base.h"

BEGIN(Engine)

class CPicking final : public CBase
{
	DECLARE_SINGLETON(CPicking);
public:
	explicit CPicking();
	virtual ~CPicking() = default;

public:
	HRESULT Initialize(HWND hWnd);
	void Compute_RayInWorldSpace();

	_bool Picking(class CVIBuffer* pVIBuffer, class CTransform* pTransform, _float3* pOut);

private:
	HWND    m_hWnd;
	
private:
	_float3   m_vRayDir, m_vRayPos;

public:
	virtual void Free() override;
};

END


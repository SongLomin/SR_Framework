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
	HRESULT Compute_RayInWorldSpace(RAY* _Out);

	_bool Picking_VIBuffer(class CVIBuffer* pVIBuffer, class CTransform* pTransform, _float3* pOut);
	
private:

public:
	virtual void Free() override;
};

END


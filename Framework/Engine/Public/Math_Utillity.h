#pragma once

#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CMath_Utillity final : public CBase
{
public:
	CMath_Utillity();
	~CMath_Utillity();

public:
	static HRESULT		WorldToScreen(D3DXVECTOR3* pos, D3DXVECTOR3* out);
	static HRESULT		ScreenToWorld(D3DXVECTOR3* pos, D3DXVECTOR3* out);

	static HRESULT		Compute_RayInWorldSpace(RAY* _Out, _float _fLength);
	static RAY			Get_MouseRayInWorldSpace();
	static _bool		Picking_VIBuffer(class CVIBuffer* pVIBuffer, class CTransform* pTransform, RAY _Ray, _float3* pOut);
	static _bool		Picking_Mesh
	(
		LPD3DXBASEMESH pMesh,
		CTransform* pTransform,
		RAY _Ray,
		_float3* pOut,
		DWORD* pFaceIndex = nullptr,
		FLOAT* pU = nullptr, 
		FLOAT* pV = nullptr,
		LPD3DXBUFFER* ppAllHits = nullptr, 
		DWORD* pCountOfHits = nullptr
	);

public:
	static _float4x4 Get_Rotation_Matrix(const _float4x4& _Mat);
	static _float4x4 Get_Scale_Matrix(const _float4x4& _Mat);
	static _float4x4 Get_Position_Matrix(const _float4x4& _Mat);

public:
	static DWORD FtoDw(float f);

};

END
#include "Math_Utillity.h"
#include "GameInstance.h"


CMath_Utillity::CMath_Utillity()
{
}

CMath_Utillity::~CMath_Utillity()
{
}

HRESULT CMath_Utillity::WorldToScreen(D3DXVECTOR3* pos, D3DXVECTOR3* out)
{
    D3DVIEWPORT9 viewPort;
    D3DXMATRIX view, projection, world;

    DEVICE->GetViewport(&viewPort);
    DEVICE->GetTransform(D3DTS_VIEW, &view);
    DEVICE->GetTransform(D3DTS_PROJECTION, &projection);
    D3DXMatrixIdentity(&world);

    D3DXVec3Project(out, pos, &viewPort, &projection, &view, &world);
    if (out->z < 1) {
        return S_OK;
    }
    
	return E_FAIL;
}

HRESULT CMath_Utillity::ScreenToWorld(D3DXVECTOR3* pos, D3DXVECTOR3* out)
{
    D3DVIEWPORT9 viewPort;
    D3DXMATRIX view, projection;


    DEVICE->GetViewport(&viewPort);
    DEVICE->GetTransform(D3DTS_VIEW, &view);
    DEVICE->GetTransform(D3DTS_PROJECTION, &projection);

    _float3 vProjPos = *pos;

    _float3     vViewPos;
    _float4x4	ProjMatrixInv;

    DEVICE->GetTransform(D3DTS_PROJECTION, &ProjMatrixInv);
    D3DXMatrixInverse(&ProjMatrixInv, nullptr, &ProjMatrixInv);
    D3DXVec3TransformCoord(&vViewPos, &vProjPos, &ProjMatrixInv);
   
    _float4x4	ViewMatrixInv;
    DEVICE->GetTransform(D3DTS_VIEW, &ViewMatrixInv);
    D3DXMatrixInverse(&ViewMatrixInv, nullptr, &ViewMatrixInv);

    D3DXVec3TransformCoord(out, pos, &ViewMatrixInv);

    return S_OK;
}

HRESULT CMath_Utillity::Compute_RayInWorldSpace(RAY* _Out, _float _fLength)
{
	if (!_Out)
		return E_FAIL;

	/* 1. 뷰포트 상의 마우스 좌표 구하기 */
	POINT  ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(GAMEINSTANCE->Get_Window_Handle(), &ptMouse);

	D3DVIEWPORT9   ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));
	DEVICE->GetViewport(&ViewPort);

	/* 2. 투영 스페이스 상의 마우스 좌표 구하기 */
	_float3  vProjPos;

	vProjPos.x = ptMouse.x / (ViewPort.Width * 0.5f) - 1.f;
	vProjPos.y = ptMouse.y / -(ViewPort.Height * 0.5f) + 1.f;
	vProjPos.z = 0.0f;

	/* 3.뷰스페이스상의 마우스 좌표를 구하자. */
	_float3		vViewPos;

	_float4x4	ProjMatrixInv;
	DEVICE->GetTransform(D3DTS_PROJECTION, &ProjMatrixInv);
	D3DXMatrixInverse(&ProjMatrixInv, nullptr, &ProjMatrixInv);
	D3DXVec3TransformCoord(&vViewPos, &vProjPos, &ProjMatrixInv);

	/* 4.마우스레이와 마우스Pos를구하자.  */
	_float3		vRayDir, vRayPos;

	vRayDir = vViewPos - _float3(0.f, 0.f, 0.f);
	vRayPos = _float3(0.f, 0.f, 0.f);

	/* 5.월드로가자. */
	_float4x4	ViewMatrixInv;
	DEVICE->GetTransform(D3DTS_VIEW, &ViewMatrixInv);
	D3DXMatrixInverse(&ViewMatrixInv, nullptr, &ViewMatrixInv);

	D3DXVec3TransformNormal(&_Out->Dir, &vRayDir, &ViewMatrixInv);
	D3DXVec3TransformCoord(&_Out->Pos, &vRayPos, &ViewMatrixInv);
	_Out->fLength = _fLength;

	return S_OK;
}

RAY CMath_Utillity::Get_MouseRayInWorldSpace()
{
	POINT  ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(GAMEINSTANCE->Get_Window_Handle(), &ptMouse);

	D3DVIEWPORT9   ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));
	DEVICE->GetViewport(&ViewPort);

	/* 2. 투영 스페이스 상의 마우스 좌표 구하기 */
	_float3  vProjPos;

	vProjPos.x = ptMouse.x / (ViewPort.Width * 0.5f) - 1.f;
	vProjPos.y = ptMouse.y / -(ViewPort.Height * 0.5f) + 1.f;
	vProjPos.z = 0.0f;

	/* 3.뷰스페이스상의 마우스 좌표를 구하자. */
	_float3		vViewPos;

	_float4x4	ProjMatrixInv;
	DEVICE->GetTransform(D3DTS_PROJECTION, &ProjMatrixInv);
	D3DXMatrixInverse(&ProjMatrixInv, nullptr, &ProjMatrixInv);
	D3DXVec3TransformCoord(&vViewPos, &vProjPos, &ProjMatrixInv);

	/* 4.마우스레이와 마우스Pos를구하자.  */
	_float3		vRayDir, vRayPos;

	vRayDir = vViewPos - _float3(0.f, 0.f, 0.f);
	vRayPos = _float3(0.f, 0.f, 0.f);

	/* 5.월드로가자. */
	_float4x4	ViewMatrixInv;
	DEVICE->GetTransform(D3DTS_VIEW, &ViewMatrixInv);
	D3DXMatrixInverse(&ViewMatrixInv, nullptr, &ViewMatrixInv);

	RAY MouseRay;

	D3DXVec3TransformNormal(&MouseRay.Dir, &vRayDir, &ViewMatrixInv);
	D3DXVec3TransformCoord(&MouseRay.Pos, &vRayPos, &ViewMatrixInv);
	MouseRay.fLength = 10000.0f; //무한
	return MouseRay;
}

_bool CMath_Utillity::Picking_VIBuffer(CVIBuffer* pVIBuffer, CTransform* pTransform, RAY _Ray , _float3* pOut)
{
	_float4x4		WorldMatrix = pTransform->Get_WorldMatrix();                 // 월드 메트릭스 가져옴
	D3DXMatrixInverse(&WorldMatrix, nullptr, &WorldMatrix);    // 열행렬 곱해 로컬스페이스로 감

	_float3			vRayPos, vRayDir;                                           //  Ray위치백터, Ray방향백터 

	D3DXVec3TransformCoord(&vRayPos, &_Ray.Pos, &WorldMatrix);      // Ray위치백터 -> 로컬스페이스로보냄 
	D3DXVec3TransformNormal(&vRayDir, &_Ray.Dir, &WorldMatrix);     // Ray방향백터 -> 로컬스페이스로보냄
	D3DXVec3Normalize(&vRayDir, &vRayDir);                              // Ray방향백터 정규화
	
	_uint iNumFaces = pVIBuffer->Get_NumPrimitive();                           // VIBuffer에있는 폴리곤 수 가져옴
	const _float3* pVerticesPos = pVIBuffer->Get_VerticesPos();                // VIBuffer에있는 버텍스 위치 가져옴

	_float  fU, fV, fDist;

	for (_uint i = 0; i < iNumFaces; ++i)                                     // 폴리곤 수만큼 반복
	{
		_uint3 iIndices = pVIBuffer->Get_Indices(i);                    // 해당 폴리곤 인덱스 가져옴

		_float3		vPickedPos;

		if (TRUE == D3DXIntersectTri(&pVerticesPos[iIndices.ix], &pVerticesPos[iIndices.iy], &pVerticesPos[iIndices.iz], &vRayPos, &vRayDir, &fU, &fV, &fDist))
		{
			if (fDist < _Ray.fLength)
			{
				vPickedPos = vRayPos + *D3DXVec3Normalize(&vRayDir, &vRayDir) * fDist;
				D3DXVec3TransformCoord(pOut, &vPickedPos, &pTransform->Get_WorldMatrix());

				return true;
			}

		}

	}

	return false;
}

_bool CMath_Utillity::Picking_Mesh(LPD3DXBASEMESH pMesh, CTransform* pTransform, RAY _Ray, _float3* pOut, DWORD* pFaceIndex, FLOAT* pU, FLOAT* pV, LPD3DXBUFFER* ppAllHits, DWORD* pCountOfHits)
{
	_float4x4		WorldMatrix = pTransform->Get_WorldMatrix();                 // 월드 메트릭스 가져옴
	D3DXMatrixInverse(&WorldMatrix, nullptr, &WorldMatrix);    // 열행렬 곱해 로컬스페이스로 감

	_float3			vRayPos, vRayDir;                                           //  Ray위치백터, Ray방향백터 

	D3DXVec3TransformCoord(&vRayPos, &_Ray.Pos, &WorldMatrix);      // Ray위치백터 -> 로컬스페이스로보냄 
	D3DXVec3TransformNormal(&vRayDir, &_Ray.Dir, &WorldMatrix);     // Ray방향백터 -> 로컬스페이스로보냄
	D3DXVec3Normalize(&vRayDir, &vRayDir);                              // Ray방향백터 정규화

	_float3		vPickedPos;
	_float fDist;
	BOOL bIsHit;

	DWORD FaceIndex;
	_float U;
	_float V;
	LPD3DXBUFFER pAllHits;
	DWORD CountOfHits;

	D3DXIntersect(pMesh, &vRayPos, &vRayDir, &bIsHit, &FaceIndex, &U, &V, &fDist, &pAllHits, &CountOfHits);

	if (pFaceIndex)
		*pFaceIndex = FaceIndex;

	if (pU)
		*pU = U;

	if (pV)
		*pV = V;

	if (ppAllHits)
		*ppAllHits = pAllHits;

	if (pCountOfHits)
		*pCountOfHits = CountOfHits;


	if (TRUE == bIsHit)
	{
		if (fDist > _Ray.fLength && fabs(_Ray.fLength) > DBL_EPSILON)
		{
			return false;
		}

		vPickedPos = vRayPos + *D3DXVec3Normalize(&vRayDir, &vRayDir) * fDist;
		D3DXVec3TransformCoord(pOut, &vPickedPos, &pTransform->Get_WorldMatrix());

		return true;
	}



	return false;
}

_float4x4 CMath_Utillity::Get_Rotation_Matrix(const _float4x4& _Mat)
{
	_float4x4 ResultMat;
	D3DXMatrixIdentity(&ResultMat);

	_float3 Right = *(_float3*)_Mat.m[0];
	_float3 Up = *(_float3*)_Mat.m[1];
	_float3 Look = *(_float3*)_Mat.m[2];

	D3DXVec3Normalize(&Right, &Right);
	D3DXVec3Normalize(&Up, &Up);
	D3DXVec3Normalize(&Look, &Look);

	memcpy(&ResultMat.m[0][0], &Right, sizeof(_float3));
	memcpy(&ResultMat.m[1][0], &Up, sizeof(_float3));
	memcpy(&ResultMat.m[2][0], &Look, sizeof(_float3));

	return ResultMat;
}

_float4x4 CMath_Utillity::Get_Scale_Matrix(const _float4x4& _Mat)
{
	_float4x4 ResultMat;
	D3DXMatrixIdentity(&ResultMat);

	_float3 Right = *(_float3*)_Mat.m[0];
	_float3 Up = *(_float3*)_Mat.m[1];
	_float3 Look = *(_float3*)_Mat.m[2];
	_float Scale[3];

	Scale[0] = D3DXVec3Length(&Right);
	Scale[1] = D3DXVec3Length(&Up);
	Scale[2] = D3DXVec3Length(&Look);

	ResultMat._11 = Scale[0];
	ResultMat._22 = Scale[1];
	ResultMat._33 = Scale[2];

	return ResultMat;
}


_float4x4 CMath_Utillity::Get_Position_Matrix(const _float4x4& _Mat)
{
	_float4x4 ResultMat;
	D3DXMatrixIdentity(&ResultMat);

	_float3 Position = *(_float3*)_Mat.m[3];
	memcpy(&ResultMat.m[3][0], &Position, sizeof(_float3));

	return ResultMat;
}

_float3 CMath_Utillity::Rotate_Vec3(const _float3& _Rotation, const _float3& _Vec3)
{
	D3DXMATRIX RotateMat;
	_float3 _ResultVec;

	D3DXMatrixRotationYawPitchRoll(&RotateMat, _Rotation.y, _Rotation.x, _Rotation.z);

	D3DXVec3TransformCoord(&_ResultVec, &_Vec3, &RotateMat);

	return _ResultVec;
}

DWORD CMath_Utillity::FtoDw(float f)
{
	return *((DWORD*)&f);
}


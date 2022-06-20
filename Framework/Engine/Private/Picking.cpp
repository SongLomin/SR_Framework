#include "Picking.h"
#include "GameInstance.h"
#include "VIBuffer.h"
#include "Transform.h"

IMPLEMENT_SINGLETON(CPicking)

CPicking::CPicking()
{
}

HRESULT CPicking::Initialize(HWND hWnd)
{
	m_hWnd = hWnd;

	return S_OK;
}

HRESULT CPicking::Compute_RayInWorldSpace(RAY* _Out)
{
	/* 로컬스페이스 -> 월드스페이스 -> 뷰스페이스 -> 투영스페이스 -> 뷰포트 */

	/* 1. 뷰포트 상의 마우스 좌표 구하기 */
	POINT  ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(m_hWnd, &ptMouse);

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

	D3DXVec3TransformNormal(&m_vRayDir, &vRayDir, &ViewMatrixInv);
	D3DXVec3TransformCoord(&m_vRayPos, &vRayPos, &ViewMatrixInv);
	

}

_bool CPicking::Picking_VIBuffer(CVIBuffer* pVIBuffer, CTransform* pTransform, _float3* pOut)
{

	_float4x4		WorldMatrix = pTransform->Get_WorldMatrix();                 // 월드 메트릭스 가져옴
	D3DXMatrixInverse(&WorldMatrix, nullptr, &WorldMatrix);    // 열행렬 곱해 로컬스페이스로 감

	_float3			vRayPos, vRayDir;                                           //  Ray위치백터, Ray방향백터 

	D3DXVec3TransformCoord(&vRayPos, &m_vRayPos, &WorldMatrix);      // Ray위치백터 -> 로컬스페이스로보냄 
	D3DXVec3TransformNormal(&vRayDir, &m_vRayDir, &WorldMatrix);     // Ray방향백터 -> 로컬스페이스로보냄
	D3DXVec3Normalize(&vRayDir, &vRayDir);                              // Ray방향백터 정규화

	_uint iNumFaces = pVIBuffer->Get_NumPrimitive();                           // VIBuffer에있는 폴리곤 수 가져옴
	const _float3* pVerticesPos = pVIBuffer->Get_VerticesPos();                // VIBuffer에있는 버텍스 위치 가져옴

	_float  fU, fV, fDist;

	for (_uint i = 0; i < iNumFaces; ++i)                                     // 폴리곤 수만큼 반복
	{
		_uint3 iIndices = pVIBuffer->Get_Indices(i);                    // 해당 폴리곤 인덱스 가져옴

		_float3		vPickedPos;

		if (true == D3DXIntersectTri(&pVerticesPos[iIndices.ix], &pVerticesPos[iIndices.iy], &pVerticesPos[iIndices.iz], &vRayPos, &vRayDir, &fU, &fV, &fDist))
		{
			vPickedPos = vRayPos + *D3DXVec3Normalize(&vRayDir, &vRayDir) * fDist;
			D3DXVec3TransformCoord(pOut, &vPickedPos, &pTransform->Get_WorldMatrix());

			return true;
		}

	}

	return false;
}


void CPicking::Free()
{
	__super::Free();

	delete this;
}

#include "..\Public\Picking.h"
#include "VIBuffer.h"
#include "Transform.h"

IMPLEMENT_SINGLETON(CPicking)

CPicking::CPicking()
{
}

HRESULT CPicking::Initialize(HWND hWnd, LPDIRECT3DDEVICE9 pGraphic_Device)
{
	m_hWnd = hWnd;

	m_pGraphic_Device = pGraphic_Device;

	Safe_AddRef(m_pGraphic_Device);

	return S_OK;
}

void CPicking::Compute_RayInWorldSpace()
{
	if (nullptr == m_pGraphic_Device)
		return;
	
	/*1. 뷰포트 상의 마우스 좌표를 구하자.  */
	POINT		ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(m_hWnd, &ptMouse);

	D3DVIEWPORT9		Viewport;
	ZeroMemory(&Viewport, sizeof(D3DVIEWPORT9));
	m_pGraphic_Device->GetViewport(&Viewport);
	
	/* 2. 투영 스페이스 상의 마우스 좌표를 구하자. */
	_float3		vProjPos;

	vProjPos.x = ptMouse.x / (Viewport.Width * 0.5f) - 1.f;
	vProjPos.y = ptMouse.y / -(Viewport.Height * 0.5f) + 1.f;
	vProjPos.z = 0.0f;

	/* 3.뷰스페이스상의 마우스 좌표를 구하자. */
	_float3		vViewPos;

	_float4x4	ProjMatrixInv;
	m_pGraphic_Device->GetTransform(D3DTS_PROJECTION, &ProjMatrixInv);
	D3DXMatrixInverse(&ProjMatrixInv, nullptr, &ProjMatrixInv);
	D3DXVec3TransformCoord(&vViewPos, &vProjPos, &ProjMatrixInv);

	/* 4.마우스레이와 마우스Pos를구하자.  */
	_float3		vRayDir, vRayPos;

	vRayDir = vViewPos - _float3(0.f, 0.f, 0.f);
	vRayPos = _float3(0.f, 0.f, 0.f);

	/* 5.월드로가자. */
	_float4x4	ViewMatrixInv;
	m_pGraphic_Device->GetTransform(D3DTS_VIEW, &ViewMatrixInv);
	D3DXMatrixInverse(&ViewMatrixInv, nullptr, &ViewMatrixInv);

	D3DXVec3TransformNormal(&m_vRayDir, &vRayDir, &ViewMatrixInv);
	D3DXVec3TransformCoord(&m_vRayPos, &vRayPos, &ViewMatrixInv);
}

_bool CPicking::Picking(CVIBuffer * pVIBuffer, CTransform * pTransform, _float3 * pOut)
{
	_float4x4		WorldMatrix = pTransform->Get_WorldMatrix();
	D3DXMatrixInverse(&WorldMatrix, nullptr, &WorldMatrix);

	_float3			vRayPos, vRayDir;

	D3DXVec3TransformCoord(&vRayPos, &m_vRayPos, &WorldMatrix);
	D3DXVec3TransformNormal(&vRayDir, &m_vRayDir, &WorldMatrix);
	D3DXVec3Normalize(&vRayDir, &vRayDir);

	_uint			iNumFaces = pVIBuffer->Get_NumPrimitive();
	const _float3*	pVerticesPos = pVIBuffer->Get_VerticesPos();
	_uint			iIndexSize = pVIBuffer->Get_IndexSize();

	_float		fU, fV, fDist;

	for (_uint i = 0; i < iNumFaces; ++i)
	{		
		_uint3		iIndices = pVIBuffer->Get_Indices(i);		

		// *(iIndices + 1) == iIndices[1]

		/*memcpy(iIndices, ((_byte*)pIndices + (i * iIndexSize * 3)) + iIndexSize * 0, iIndexSize);
		memcpy(iIndices + 1, ((_byte*)pIndices + (i * iIndexSize * 3)) + iIndexSize * 1, iIndexSize);
		memcpy(iIndices + 2, ((_byte*)pIndices + (i * iIndexSize * 3)) + iIndexSize * 2, iIndexSize);		*/

		/*memcpy(&iIndices[0], ((_byte*)pIndices + (i * iIndexSize * 3)) + iIndexSize * 0, iIndexSize);
		memcpy(&iIndices[1], ((_byte*)pIndices + (i * iIndexSize * 3)) + iIndexSize * 1, iIndexSize);
		memcpy(&iIndices[2], ((_byte*)pIndices + (i * iIndexSize * 3)) + iIndexSize * 2, iIndexSize);*/

		// D3DXIntersectTri(pVerticesPos + iIndices[0], pVerticesPos + iIndices[1], pVerticesPos + iIndices[2], );

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
	Safe_Release(m_pGraphic_Device);
}

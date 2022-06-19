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

void CPicking::Compute_RayInWorldSpace()
{
	/* ���ý����̽� -> ���彺���̽� -> �佺���̽� -> ���������̽� -> ����Ʈ */

	/* 1. ����Ʈ ���� ���콺 ��ǥ ���ϱ� */
	POINT  ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(m_hWnd, &ptMouse);

	D3DVIEWPORT9   ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));
	DEVICE->GetViewport(&ViewPort);

	/* 2. ���� �����̽� ���� ���콺 ��ǥ ���ϱ� */
	_float3  vProjPos;

	vProjPos.x = ptMouse.x / (ViewPort.Width * 0.5f) - 1.f;
	vProjPos.y = ptMouse.y / -(ViewPort.Height * 0.5f) + 1.f;
	vProjPos.z = 0.0f;

	/* 3.�佺���̽����� ���콺 ��ǥ�� ������. */
	_float3		vViewPos;

	_float4x4	ProjMatrixInv;
	DEVICE->GetTransform(D3DTS_PROJECTION, &ProjMatrixInv);
	D3DXMatrixInverse(&ProjMatrixInv, nullptr, &ProjMatrixInv);
	D3DXVec3TransformCoord(&vViewPos, &vProjPos, &ProjMatrixInv);

	/* 4.���콺���̿� ���콺Pos��������.  */
	_float3		vRayDir, vRayPos;

	vRayDir = vViewPos - _float3(0.f, 0.f, 0.f);
	vRayPos = _float3(0.f, 0.f, 0.f);

	/* 5.����ΰ���. */
	_float4x4	ViewMatrixInv;
	DEVICE->GetTransform(D3DTS_VIEW, &ViewMatrixInv);
	D3DXMatrixInverse(&ViewMatrixInv, nullptr, &ViewMatrixInv);

	D3DXVec3TransformNormal(&m_vRayDir, &vRayDir, &ViewMatrixInv);
	D3DXVec3TransformCoord(&m_vRayPos, &vRayPos, &ViewMatrixInv);
	

}



void CPicking::Free()
{
}

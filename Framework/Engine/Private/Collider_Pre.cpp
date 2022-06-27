#include "Collider_Pre.h"
#include "GameInstance.h"
#include "Math_Utillity.h"

CCollider_Pre::CCollider_Pre(const CCollider_Pre& Prototype)
{
	*this = Prototype;

}

HRESULT CCollider_Pre::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCollider_Pre::Initialize(void* pArg)
{
	return S_OK;
}

void CCollider_Pre::Tick(_float fTimeDelta)
{

}

void CCollider_Pre::LateTick(_float fTimeDelta)
{
	m_vColliderPosition = m_pMyTransformCom->Get_State(CTransform::STATE_POSITION, true);
}

HRESULT CCollider_Pre::Debug_Render()
{
	DEVICE->SetRenderState(D3DRS_FILLMODE, _D3DFILLMODE::D3DFILL_WIREFRAME);

	_float4x4 MatBindedWorld;
	DEVICE->GetTransform(D3DTS_WORLD, &MatBindedWorld);

	_float4x4 MatMyObjectWorld = m_pMyTransformCom->Get_WorldMatrix();
	_float4x4 MatColliderWorld;
	D3DXMatrixIdentity(&MatColliderWorld);

	MatColliderWorld._41 = MatMyObjectWorld._41;
	MatColliderWorld._42 = MatMyObjectWorld._42;
	MatColliderWorld._43 = MatMyObjectWorld._43;


	DEVICE->SetTransform(D3DTS_WORLD, &MatColliderWorld);
	//m_pMesh->DrawSubset(0);

	DEVICE->SetRenderState(D3DRS_FILLMODE, _D3DFILLMODE::D3DFILL_SOLID);
	DEVICE->SetTransform(D3DTS_WORLD, &MatBindedWorld);

	return S_OK;
}

void CCollider_Pre::Set_Collider_Size(const _float3& _Size)
{
	m_fSize = _Size.x;
	//D3DXCreateSphere(DEVICE, m_fSize, 10, 10, &m_pMesh, nullptr);
}

_float3 CCollider_Pre::Get_Collider_Size()
{
	return _float3(m_fSize, m_fSize, m_fSize);
}

_float3 CCollider_Pre::Get_Collider_Position()
{
	return m_vColliderPosition;
}

CCollider_Pre* CCollider_Pre::Create()
{
	CREATE_PIPELINE(CCollider_Pre);
}

CComponent* CCollider_Pre::Clone(void* pArg)
{
	CLONE_PIPELINE(CCollider_Pre);
}

void CCollider_Pre::Free()
{
	__super::Free();

	delete this;
}

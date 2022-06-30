#include "Collier_Sphere.h"
#include "GameInstance.h"

CCollider_Shpere::CCollider_Shpere(const CCollider_Shpere& Prototype)
{
	*this = Prototype;
}

HRESULT CCollider_Shpere::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCollider_Shpere::Initialize(void* pArg)
{
	return S_OK;
}

void CCollider_Shpere::Tick(_float fTimeDelta)
{
}

void CCollider_Shpere::LateTick(_float fTimeDelta)
{
	m_vColliderPosition = m_pMyTransformCom->Get_State(CTransform::STATE_POSITION, true);
}

HRESULT CCollider_Shpere::Debug_Render()
{
	DEVICE->SetRenderState(D3DRS_FILLMODE, _D3DFILLMODE::D3DFILL_WIREFRAME);

	_float4x4 MatBindedWorld;
	DEVICE->GetTransform(D3DTS_WORLD, &MatBindedWorld);

	_float4x4 MatMyObjectWorld = m_pMyTransformCom->Get_WorldMatrix();
	_float4x4 MatColliderWorld;
	D3DXMatrixIdentity(&MatColliderWorld);

	//MatColliderWorld._41 = MatMyObjectWorld._41;
	//MatColliderWorld._42 = MatMyObjectWorld._42;
	//MatColliderWorld._43 = MatMyObjectWorld._43;

	MatColliderWorld._41 = m_vColliderPosition.x;
	MatColliderWorld._42 = m_vColliderPosition.y;
	MatColliderWorld._43 = m_vColliderPosition.z;

	DEVICE->SetTransform(D3DTS_WORLD, &MatColliderWorld);
	//m_pMesh->DrawSubset(0);

	DEVICE->SetRenderState(D3DRS_FILLMODE, _D3DFILLMODE::D3DFILL_SOLID);
	DEVICE->SetTransform(D3DTS_WORLD, &MatBindedWorld);

	return S_OK;
}

void CCollider_Shpere::Set_Collider_Size(const _float3& _Size)
{
	m_fSize = _Size.x;
	//D3DXCreateSphere(DEVICE, m_fSize, 10, 10, &m_pMesh, nullptr);
}

_float3 CCollider_Shpere::Get_Collider_Size()
{
	return _float3(m_fSize, m_fSize, m_fSize);
}

_float3 CCollider_Shpere::Get_Collider_Position()
{
	return m_vColliderPosition;
}

CCollider_Shpere* CCollider_Shpere::Create()
{
	CREATE_PIPELINE(CCollider_Shpere);
}

CComponent* CCollider_Shpere::Clone(void* pArg)
{
	CLONE_PIPELINE(CCollider_Shpere);
}

void CCollider_Shpere::Free()
{
	__super::Free();

	delete this;
}

#include "Collier_Sphere.h"
#include "GameInstance.h"

CCollider_Sphere::CCollider_Sphere(const CCollider_Sphere& Prototype)
{
	*this = Prototype;
}

HRESULT CCollider_Sphere::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCollider_Sphere::Initialize(void* pArg)
{
	
	m_iID = ++g_iNextID;
	m_eCollision_Type = *(COLLISION_TYPE*)pArg;

	return S_OK;
}

void CCollider_Sphere::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CCollider_Sphere::LateTick(_float fTimeDelta)
{
	m_vColliderPosition = m_pMyTransformCom->Get_State(CTransform::STATE_POSITION, true);
}

HRESULT CCollider_Sphere::Debug_Render()
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

void CCollider_Sphere::Set_Collider_Size(const _float3& _Size)
{
	m_fSize = _Size.x;
	//D3DXCreateSphere(DEVICE, m_fSize, 10, 10, &m_pMesh, nullptr);
}

_float3 CCollider_Sphere::Get_Collider_Size()
{
	return _float3(m_fSize, m_fSize, m_fSize);
}

_float3 CCollider_Sphere::Get_Collider_Position()
{
	return m_vColliderPosition;
}

CCollider_Sphere* CCollider_Sphere::Create()
{
	CREATE_PIPELINE(CCollider_Sphere);
}

CComponent* CCollider_Sphere::Clone(void* pArg)
{
	CLONE_PIPELINE(CCollider_Sphere);
}

void CCollider_Sphere::Free()
{
	__super::Free();

	delete this;
}

#include "Collider_Mesh.h"
#include "GameInstance.h"
#include "GameObject.h"

CCollider_Mesh::CCollider_Mesh(const CCollider_Mesh& Prototype)
{
	*this = Prototype;
}

HRESULT CCollider_Mesh::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCollider_Mesh::Initialize(void* pArg)
{

	m_iID = ++g_iNextID;
	m_eCollision_Type = *(COLLISION_TYPE*)pArg;
	m_eShape = COLLIDER_SHAPE::MESH;

	return S_OK;
}

void CCollider_Mesh::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CCollider_Mesh::LateTick(_float fTimeDelta)
{
	m_vColliderPosition = m_pMyTransformCom->Get_State(CTransform::STATE_POSITION, true);
}

HRESULT CCollider_Mesh::Debug_Render()
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

void CCollider_Mesh::Set_Collider_Size(const _float3& _Size)
{
	m_vSize = _Size;
	
}

_float3 CCollider_Mesh::Get_Collider_Size()
{
	return m_vSize;
}

_float3 CCollider_Mesh::Get_Collider_Position()
{
	return m_vColliderPosition;
}

ID3DXMesh* CCollider_Mesh::Get_Collider_Mesh()
{
	return m_pOwner->Get_Component_FromType<CMesh>()->Get_Mesh();
}


CCollider_Mesh* CCollider_Mesh::Create()
{
	CREATE_PIPELINE(CCollider_Mesh);
}

CComponent* CCollider_Mesh::Clone(void* pArg)
{
	CLONE_PIPELINE(CCollider_Mesh);
}

void CCollider_Mesh::Free()
{
	__super::Free();

	delete this;
}

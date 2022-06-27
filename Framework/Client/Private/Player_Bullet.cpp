#include "stdafx.h"
#include "Player_Bullet.h"
#include "GameInstance.h"
#include "Collider_OBB.h"


CPlayer_Bullet::CPlayer_Bullet()
{
}

CPlayer_Bullet::CPlayer_Bullet(const CPlayer_Bullet& Prototype)
{
	*this = Prototype;
	//m_szName = L"Bullet";
	Add_Component<CTransform>();
}

HRESULT CPlayer_Bullet::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CPlayer_Bullet::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	return S_OK;
}

void CPlayer_Bullet::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	m_fLifeTime -= fTimeDelta;

	if (m_fLifeTime < 0.f)
	{
		Set_Dead();
	}
}

void CPlayer_Bullet::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
	m_pRigidBodyCom->Update_Transform(fTimeDelta);
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CPlayer_Bullet::Render()
{
	m_pColliderCom->Debug_Render();
	m_pPreColliderCom->Debug_Render();

	m_pTransformCom->Scaling(_float3(0.2f, 0.1f, 10.f));
	m_pTransformCom->Bind_WorldMatrix();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pRendererCom->Bind_Texture(1);
	__super::Render();
	m_pMeshCom->Render_Mesh(5);
	m_pRendererCom->UnBind_Texture();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}



void CPlayer_Bullet::Link_PosinTransform(CTransform* _pTransform)
{
	m_pPosinTransformCom = _pTransform;

	m_pPosinTransformCom->Set_WeakPtr(&m_pPosinTransformCom);

	m_pTransformCom->Set_State(CTransform::STATE::STATE_RIGHT, m_pPosinTransformCom->Get_State(CTransform::STATE::STATE_RIGHT, true));
	m_pTransformCom->Set_State(CTransform::STATE::STATE_UP, m_pPosinTransformCom->Get_State(CTransform::STATE::STATE_UP, true));
	m_pTransformCom->Set_State(CTransform::STATE::STATE_LOOK, m_pPosinTransformCom->Get_State(CTransform::STATE::STATE_LOOK, true));
	m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, m_pPosinTransformCom->Get_State(CTransform::STATE::STATE_POSITION, true));

	m_pTransformCom->Update_WorldMatrix();
	m_pRigidBodyCom->Set_DirVector();
	m_pRigidBodyCom->Add_Dir(CRigid_Body::FRONT);
}

void CPlayer_Bullet::On_Collision_Enter(CCollider* _Other_Collider)
{
	if (_Other_Collider->Get_Collision_Type() == COLLISION_TYPE::MONSTER)
	{
		Set_Dead();
	}

}

void CPlayer_Bullet::On_Collision_Stay(CCollider* _Other_Collider)
{
	
}

void CPlayer_Bullet::On_Collision_Exit(CCollider* _Other_Collider)
{
}

inline HRESULT CPlayer_Bullet::SetUp_Components()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr((void**)&m_pTransformCom);

	//m_pTransformCom->Scaling(_float3(0.2f, 10.0f, 0.2f));

	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.m_fOwnerSpeed = 150.f;
	RigidBodyDesc.m_fOwnerAccel = 150.f;
	RigidBodyDesc.m_fOwnerRadSpeed = D3DXToRadian(90.0f);
	RigidBodyDesc.m_fOwnerRadAccel = 0.3f;
	RigidBodyDesc.m_fOwnerJump = 0.f;
	RigidBodyDesc.m_fOwnerJumpScale = 1.f;

	RigidBodyDesc.m_fFrictional = 0.05f;
	RigidBodyDesc.m_fRadFrictional = 0.02f;
	RigidBodyDesc.m_fRadZ = 0.01f;


	RigidBodyDesc.m_fOwnerLiftSpeed = 3.f;
	RigidBodyDesc.m_fOwnerLiftAccel = 0.3f;
	RigidBodyDesc.m_fRadDrag = 1.f;
	RigidBodyDesc.m_fDirDrag = 0.05f;

	m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);


	m_pMeshCom = Add_Component<CMesh_Cube>();
	m_pMeshCom->Set_WeakPtr(&m_pMeshCom);
	m_pMeshCom->Set_Texture(TEXT("Mesh_Cube"), MEMORY_TYPE::MEMORY_STATIC);


	m_pPreColliderCom = Add_Component<CCollider_Pre>();
	WEAK_PTR(m_pPreColliderCom);
	m_pPreColliderCom->Link_Transform(m_pTransformCom);
	//구체라서 x만 받는다.
	m_pPreColliderCom->Set_Collider_Size(_float3(1.f, 0.f, 0.f));

	COLLISION_TYPE eCollisionType = COLLISION_TYPE::PLAYER_ATTACK;
	m_pColliderCom = Add_Component<CCollider_OBB>(&eCollisionType);
	m_pColliderCom->Set_WeakPtr(&m_pColliderCom);
	m_pColliderCom->Link_Transform(m_pTransformCom);
	m_pColliderCom->Link_Pre_Collider(m_pPreColliderCom);

	_float3 ColliderSize = m_pTransformCom->Get_Scaled();
	_float3 RenderScale = _float3(0.2f, 0.1f, 0.2f);
	ColliderSize.x *= RenderScale.x;
	ColliderSize.y *= RenderScale.y;
	ColliderSize.z *= RenderScale.z;

	m_pColliderCom->Set_Collider_Size(ColliderSize);

	return S_OK;
}



CPlayer_Bullet* CPlayer_Bullet::Create()
{
	CREATE_PIPELINE(CPlayer_Bullet);
}

CGameObject* CPlayer_Bullet::Clone(void* pArg)
{
	CLONE_PIPELINE(CPlayer_Bullet);
}

void CPlayer_Bullet::Free()
{
	if (m_pPosinTransformCom)
		m_pPosinTransformCom->Return_WeakPtr(&m_pPosinTransformCom);

	if (m_pMeshCom)
		m_pMeshCom->Return_WeakPtr(&m_pMeshCom);

	if (m_pRendererCom)
		m_pRendererCom->Return_WeakPtr(&m_pRendererCom);

	__super::Free();

	


	delete this;
}

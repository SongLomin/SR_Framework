#include "stdafx.h"
#include "Bullet.h"
#include "stdafx.h"
#include "Bullet.h"
#include "GameInstance.h"
#include "CameraPosin.h"
#include "Collider_OBB.h"


CBullet::CBullet()
{
}

CBullet::CBullet(const CBullet& Prototype)
{
	*this = Prototype;
	//m_szName = L"Bullet";
	Add_Component<CTransform>();
}

HRESULT CBullet::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CBullet::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);


	m_pMeshCom = Add_Component<CMesh_Cube>();
	m_pMeshCom->Set_WeakPtr(&m_pMeshCom);
	m_pMeshCom->Set_Texture(TEXT("Mesh_Cube"), MEMORY_TYPE::MEMORY_STATIC);


	COLLISION_TYPE eCollisionType = COLLISION_TYPE::PLAYER_ATTACK;
	m_pColliderCom = Add_Component<CCollider_OBB>(&eCollisionType);
	m_pColliderCom->Set_WeakPtr(&m_pColliderCom);
	m_pColliderCom->Link_Transform(m_pTransformCom);

	_float3 ColliderSize = m_pTransformCom->Get_Scaled();
	_float3 RenderScale = _float3(0.2f, 0.1f, 10.f);
	ColliderSize.x *= RenderScale.x;
	ColliderSize.y *= RenderScale.y;
	ColliderSize.z *= RenderScale.z;

	m_pColliderCom->Set_Collider_Size(ColliderSize);

	return S_OK;
}

void CBullet::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


	/*m_pTransformCom->Go_BackAndForth(80.f, fTimeDelta);
	m_pTransformCom->Turn(m_pTransformCom->Get_State(CTransform::STATE_LOOK), 10.f, fTimeDelta);*/
}

void CBullet::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
	m_pRigidBodyCom->Update_Transform(fTimeDelta);
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CBullet::Render()
{
	
	m_pTransformCom->Scaling(_float3(0.2f, 0.1f, 10.f));
	m_pTransformCom->Bind_WorldMatrix();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pRendererCom->Bind_Texture(1);
	__super::Render();
	m_pMeshCom->Render_Mesh();
	m_pRendererCom->UnBind_Texture();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}



void CBullet::Link_PosinTransform(CTransform* pTransform)
{
	m_pPosinTransformCom = pTransform;

	m_pPosinTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pTransformCom->Set_State(CTransform::STATE::STATE_RIGHT, m_pPosinTransformCom->Get_State(CTransform::STATE::STATE_RIGHT, true));
	m_pTransformCom->Set_State(CTransform::STATE::STATE_UP, m_pPosinTransformCom->Get_State(CTransform::STATE::STATE_UP, true));
	m_pTransformCom->Set_State(CTransform::STATE::STATE_LOOK, m_pPosinTransformCom->Get_State(CTransform::STATE::STATE_LOOK, true));
	m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, m_pPosinTransformCom->Get_State(CTransform::STATE::STATE_POSITION, true));

	m_pTransformCom->Update_WorldMatrix();
	m_pRigidBodyCom->Set_DirVector();
	m_pRigidBodyCom->Add_Dir(CRigid_Body::FRONT);
	m_pRigidBodyCom->Add_Dir(CRigid_Body::JUMP);
}

void CBullet::On_Collision_Enter(CCollider* _Other_Collider)
{
	if (_Other_Collider->Get_Collision_Type() == COLLISION_TYPE::MONSTER)
	{
		Set_Dead();
	}

}

void CBullet::On_Collision_Stay(CCollider* _Other_Collider)
{
}

void CBullet::On_Collision_Exit(CCollider* _Other_Collider)
{
}

inline HRESULT CBullet::SetUp_Components()
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

	return S_OK;
}



CBullet* CBullet::Create()
{
	CREATE_PIPELINE(CBullet);
}

CGameObject* CBullet::Clone(void* pArg)
{
	CLONE_PIPELINE(CBullet);
}

void CBullet::Free()
{
	__super::Free();

	delete this;
}

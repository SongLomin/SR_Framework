#include "stdafx.h"
#include "Normal_Bullet.h"
#include "GameInstance.h"
#include "Collider_OBB.h"


CNormal_Bullet::CNormal_Bullet()
{
}

CNormal_Bullet::CNormal_Bullet(const CNormal_Bullet& Prototype)
{
	*this = Prototype;

	Add_Component<CTransform>();
}

HRESULT CNormal_Bullet::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CNormal_Bullet::Initialize(void* pArg)
{
	COLLISION_TYPE eCollisionType = *(COLLISION_TYPE*)pArg;

	if (FAILED(SetUp_Components(eCollisionType)))
		return E_FAIL;

	return S_OK;
}

void CNormal_Bullet::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	//불빛이 미사일 뒤로 나감
	//_float3 Light_Look_Dir = -m_pTransformCom->Get_State(CTransform::STATE_LOOK, true);
	//D3DXVec3Normalize(&Light_Look_Dir, &Light_Look_Dir);

	//m_pLight->Set_LooK_Dir(Light_Look_Dir);

}

void CNormal_Bullet::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
	m_pRigidBodyCom->Update_Transform(fTimeDelta);


	if (GAMEINSTANCE->IsIn(&(m_pTransformCom->Get_World_State(CTransform::STATE_POSITION))))
	{
		m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
	}
}

HRESULT CNormal_Bullet::Render_Begin(ID3DXEffect** Shader)
{
	m_pTransformCom->Scaling(_float3(0.2f, 0.2f, 0.2f), true);
	m_pTransformCom->Bind_WorldMatrix();

	/*D3DXHANDLE ColorHandle = (*Shader)->GetParameterByName(0, "Color");


	float floatArray[3];
	floatArray[0] = 1.f;
	floatArray[1] = 1.f;
	floatArray[2] = 1.f;

	(*Shader)->SetFloatArray(ColorHandle, floatArray, 3);*/


	return S_OK;
}

HRESULT CNormal_Bullet::Render()
{
	//m_pColliderCom->Debug_Render();
	//m_pPreColliderCom->Debug_Render();

	

	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//m_pRendererCom->Bind_Texture(1);
	__super::Render();
	m_pMeshCom->Render_Mesh();

	
	//m_pRendererCom->UnBind_Texture();

	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}

void CNormal_Bullet::Init_BulletPosition(_float4x4* _pWorldMat)
{
	__super::Init_BulletPosition(_pWorldMat);

	m_pTransformCom->Go_BackAndForth(2.f, 1.f);

	m_pTransformCom->Update_WorldMatrix();
	m_pRigidBodyCom->Set_DirVector();
	m_pRigidBodyCom->Add_Dir(CRigid_Body::FRONT);

}

void CNormal_Bullet::On_Collision_Enter(CCollider* _Other_Collider)
{
	if (_Other_Collider->Get_Collision_Type() == COLLISION_TYPE::MONSTER)
	{
		//Set_Dead();
		Set_Enable(false);
	}

}

void CNormal_Bullet::On_Collision_Stay(CCollider* _Other_Collider)
{
	
}

void CNormal_Bullet::On_Collision_Exit(CCollider* _Other_Collider)
{
}

void CNormal_Bullet::OnEnable(void* _Arg)
{
	__super::OnEnable(_Arg);

	m_pColliderCom->OnEnable(_Arg);
	m_pLight->Set_Preset_PowLight();
	m_pLight->Set_Enable(true);
}

void CNormal_Bullet::OnDisable()
{
	__super::OnDisable();

	m_pColliderCom->OnDisable();
}

CNormal_Bullet* CNormal_Bullet::Create()
{
	CREATE_PIPELINE(CNormal_Bullet);
}

CGameObject* CNormal_Bullet::Clone(void* pArg)
{
	CLONE_PIPELINE(CNormal_Bullet);
}

void CNormal_Bullet::Free()
{
	

	if (m_pRendererCom)
		m_pRendererCom->Return_WeakPtr(&m_pRendererCom);

	if (m_pMeshCom)
		m_pMeshCom->Return_WeakPtr(&m_pMeshCom);

	RETURN_WEAKPTR(m_pLight);

	__super::Free();

	


	delete this;
}

HRESULT CNormal_Bullet::SetUp_Components_For_Child(COLLISION_TYPE _eCollisionType)
{
	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.m_fOwnerSpeed = 200.f;
	RigidBodyDesc.m_fOwnerAccel = 200.f;
	RigidBodyDesc.m_fOwnerRadSpeed = D3DXToRadian(90.0f);
	RigidBodyDesc.m_fOwnerRadAccel = 0.3f;
	RigidBodyDesc.m_fOwnerJump = 0.f;
	RigidBodyDesc.m_fOwnerJumpScale = 1.f;

	RigidBodyDesc.m_fFrictional = 0.f;
	RigidBodyDesc.m_fRadFrictional = 0.02f;
	RigidBodyDesc.m_fRadZ = 0.01f;


	RigidBodyDesc.m_fOwnerLiftSpeed = 3.f;
	RigidBodyDesc.m_fOwnerLiftAccel = 0.3f;
	RigidBodyDesc.m_fRadDrag = 1.f;
	RigidBodyDesc.m_fDirDrag = 0.05f;

	m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);

	COLLISION_TYPE eCollisionType = _eCollisionType;
	m_pColliderCom = Add_Component<CCollider_Sphere>(&eCollisionType);
	m_pColliderCom->Set_WeakPtr(&m_pColliderCom);
	m_pColliderCom->Link_Transform(m_pTransformCom);

	_float3 ColliderSize = m_pTransformCom->Get_Scaled();
	_float3 RenderScale = _float3(0.2f, 0.2f, 0.2f);
	ColliderSize.x *= RenderScale.x;
	ColliderSize.y *= RenderScale.y;
	ColliderSize.z *= RenderScale.z;

	m_pColliderCom->Set_Collider_Size(ColliderSize);

	m_pMeshCom = Add_Component<CMesh_Cube>();
	m_pMeshCom->Set_WeakPtr(&m_pMeshCom);
	m_pMeshCom->Set_Texture(TEXT("Mesh_Cube"), MEMORY_TYPE::MEMORY_STATIC);

	m_pLight = Add_Component<CPointLight>();
	WEAK_PTR(m_pLight);
	m_pLight->Set_Preset_PowLight();

	return S_OK;
}

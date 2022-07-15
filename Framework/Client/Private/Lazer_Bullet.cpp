#include "stdafx.h"
#include "Lazer_Bullet.h"
#include "GameInstance.h"
#include "Collider_OBB.h"


CLazer_Bullet::CLazer_Bullet()
{
}

CLazer_Bullet::CLazer_Bullet(const CLazer_Bullet& Prototype)
{
	*this = Prototype;
	
	Add_Component<CTransform>();
}

HRESULT CLazer_Bullet::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CLazer_Bullet::Initialize(void* pArg)
{
	COLLISION_TYPE eCollisionType = *(COLLISION_TYPE*)pArg;

	if (FAILED(SetUp_Components(eCollisionType)))
		return E_FAIL;

	m_fMaxTime = m_fLifeTime = -0.1f;

	return S_OK;
}

void CLazer_Bullet::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	//불빛이 미사일 뒤로 나감
	_float3 Light_Look_Dir = -m_pTransformCom->Get_State(CTransform::STATE_LOOK, true);
	D3DXVec3Normalize(&Light_Look_Dir, &Light_Look_Dir);

	m_pLight->Set_LooK_Dir(Light_Look_Dir);

}

void CLazer_Bullet::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
	m_pRigidBodyCom->Update_Transform(fTimeDelta);
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CLazer_Bullet::Render_Begin(ID3DXEffect** Shader)
{
	m_pTransformCom->Scaling(_float3(0.3f, 0.3f, 100.f), true);
	m_pTransformCom->Bind_WorldMatrix();

	/*D3DXHANDLE ColorHandle = (*Shader)->GetParameterByName(0, "Color");


	float floatArray[3];
	floatArray[0] = 1.0f;
	floatArray[1] = 1.0f;
	floatArray[2] = 0.0f;

	(*Shader)->SetFloatArray(ColorHandle, floatArray, 3);*/


	return S_OK;
}

HRESULT CLazer_Bullet::Render()
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

void CLazer_Bullet::Init_BulletPosition(_float4x4* _pWorldMat)
{
	__super::Init_BulletPosition(_pWorldMat);

	m_pTransformCom->Go_BackAndForth(100.f, 1.f);

	m_pColliderCom->Set_OffSet(-m_pTransformCom->Get_State(CTransform::STATE_LOOK, true) * 50.f);

	m_pTransformCom->Update_WorldMatrix();
	m_pRigidBodyCom->Set_DirVector();


}

void CLazer_Bullet::On_Collision_Enter(CCollider* _Other_Collider)
{
	if (_Other_Collider->Get_Collision_Type() == COLLISION_TYPE::MONSTER)
	{
		//Set_Enable(false);
	}
}

void CLazer_Bullet::On_Collision_Stay(CCollider* _Other_Collider)
{
	if (_Other_Collider->Get_Collision_Type() == COLLISION_TYPE::MONSTER)
	{
		_Other_Collider->Get_Owner()->On_Collision_Enter(m_pColliderCom);
	}
}

void CLazer_Bullet::On_Collision_Exit(CCollider* _Other_Collider)
{
}

CLazer_Bullet* CLazer_Bullet::Create()
{
	CREATE_PIPELINE(CLazer_Bullet);
}

CGameObject* CLazer_Bullet::Clone(void* pArg)
{
	CLONE_PIPELINE(CLazer_Bullet);
}

void CLazer_Bullet::Free()
{
	if (m_pMeshCom)
		m_pMeshCom->Return_WeakPtr(&m_pMeshCom);

	if (m_pRendererCom)
		m_pRendererCom->Return_WeakPtr(&m_pRendererCom);

	RETURN_WEAKPTR(m_pLight);

	__super::Free();

	delete this;
}

HRESULT CLazer_Bullet::SetUp_Components_For_Child(COLLISION_TYPE _eCollisionType)
{
	//m_pTransformCom->Scaling(_float3(0.2f, 10.0f, 0.2f));

	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.m_fOwnerSpeed = 800.f;
	RigidBodyDesc.m_fOwnerAccel = 80.f;
	RigidBodyDesc.m_fOwnerRadSpeed = D3DXToRadian(90.0f);
	RigidBodyDesc.m_fOwnerRadAccel = 0.3f;
	//RigidBodyDesc.m_fOwnerJump = 0.f;
	//RigidBodyDesc.m_fOwnerJumpScale = 1.f;

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


	m_pMeshCom = Add_Component<CMesh_Test>();

	m_pMeshCom->Set_WeakPtr(&m_pMeshCom);
	m_pMeshCom->Set_Texture(TEXT("Mesh_Cube"), MEMORY_TYPE::MEMORY_STATIC);

	COLLISION_TYPE eCollisionType = _eCollisionType;
	m_pColliderCom = Add_Component<CCollider_Ray>(&eCollisionType);
	m_pColliderCom->Set_WeakPtr(&m_pColliderCom);
	m_pColliderCom->Link_Transform(m_pTransformCom);



	m_pLight = Add_Component<CSpotLight>();
	WEAK_PTR(m_pLight);
	m_pLight->Set_LightRange(12.f);

	return S_OK;
}

void CLazer_Bullet::OnEnable(void* _Arg)
{
	__super::OnEnable(_Arg);
	m_pColliderCom->OnEnable(_Arg);
}

void CLazer_Bullet::OnDisable()
{
	__super::OnDisable();
	m_pColliderCom->OnDisable();
}

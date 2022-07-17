#include "stdafx.h"
#include "Hong_Ship_Body.h"
#include "GameInstance.h"
#include "Normal_Turret.h"
#include "Trajectory.h"

CHong_Ship_Body::CHong_Ship_Body()
{
}

CHong_Ship_Body::CHong_Ship_Body(const CHong_Ship_Body& Prototype)
{
	*this = Prototype;

}

HRESULT CHong_Ship_Body::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CHong_Ship_Body::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;


	return S_OK;
}

void CHong_Ship_Body::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CHong_Ship_Body::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
}

HRESULT CHong_Ship_Body::Render_Begin(ID3DXEffect** Shader)
{
	m_pTransformCom->Scaling(_float3(1.f, 1.f, 1.f), true);
	m_pTransformCom->Bind_WorldMatrix();

	D3DXHANDLE ColorHandle = (*Shader)->GetParameterByName(0, "Color");

	float floatArray[3];
	floatArray[0] = 0.2f;
	floatArray[1] = 0.5f;
	floatArray[2] = 0.2f;

	(*Shader)->SetFloatArray(ColorHandle, floatArray, 3);

	return S_OK;
}

HRESULT CHong_Ship_Body::Render()
{	
	__super::Render();

	m_pMeshCom->Render_Mesh();

	return S_OK;
}

void CHong_Ship_Body::SetUp_Components_For_Child()
{
	m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(0.f, 1.f, 0.f));

#pragma region Mesh Setting

	m_pMeshCom = Add_Component<CMesh_HongShip>();
	m_pMeshCom->Set_WeakPtr(&m_pMeshCom);
	m_pMeshCom->Set_Texture(TEXT("Mesh_Cube"), MEMORY_TYPE::MEMORY_STATIC);

#pragma endregion Mesh Setting

#pragma region Status Setting
	CStatus::STATUS		Status;
	Status.fHp = 10.f;
	Status.fAttack = 7.f;
	Status.fArmor = 5.f;

	m_pStatusCom = Add_Component<CStatus>(&Status);
	m_pStatusCom->Set_WeakPtr(&m_pStatusCom);
#pragma endregion Status Setting

#pragma region Rigid_Body Setting
	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.m_fOwnerSpeed = 100.f;
	RigidBodyDesc.m_fOwnerAccel = 10.f;
	RigidBodyDesc.m_fOwnerRadSpeed = D3DXToRadian(90.0f);
	RigidBodyDesc.m_fOwnerRadAccel = 0.3f;
	RigidBodyDesc.m_fOwnerJump = 5.f;
	RigidBodyDesc.m_fOwnerJumpScale = 1.f;

	RigidBodyDesc.m_fFrictional = 0.05f;
	RigidBodyDesc.m_fRadFrictional = 0.02f;
	RigidBodyDesc.m_fRadZ = 0.01f;

	RigidBodyDesc.m_fOwnerLiftSpeed = 100.f;
	RigidBodyDesc.m_fOwnerLiftAccel = 10.f;
	RigidBodyDesc.m_fRadDrag = 1.f;
	RigidBodyDesc.m_fDirDrag = 0.05f;
	RigidBodyDesc.m_fBoosterSpeed = 500.f;
	RigidBodyDesc.m_fBoosterAccel = 50.f;

	m_pRigid_BodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigid_BodyCom->Set_WeakPtr(&m_pRigid_BodyCom);
	m_pRigid_BodyCom->Link_TransformCom(m_pTransformCom);

#pragma endregion Rigid_Body Setting

#pragma region Posin Setting

	CNormal_Turret* Posin = static_cast<CNormal_Turret*>(GAMEINSTANCE->Add_GameObject<CNormal_Turret>(LEVEL_STATIC, TEXT("Normal_Turret"), m_pTransformCom));
	Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(0.f, 1.f, 0.f));
	m_pMyTurretList.push_back(Posin);
	Posin->Set_WeakPtr(&m_pMyTurretList.back());


#pragma endregion Posin Setting

#pragma region Controller Setting

	m_pAI_ControllerCom->Link_Object(this);
	m_pAI_ControllerCom->Set_Enable(false);


	m_pPlayer_ControllerCom->Link_Object(this);
	m_pPlayer_ControllerCom->Set_Enable(false);

#pragma endregion Controller Setting 

#pragma region State Setting

	m_pStateCom->Link_RigidBody(m_pRigid_BodyCom);
	m_pStateCom->Link_AI_Transform(m_pTransformCom);

#pragma endregion State Setting

	Set_Controller(CONTROLLER::AI);

}

void CHong_Ship_Body::On_Change_Controller(const CONTROLLER& _IsAI)
{
	__super::On_Change_Controller(_IsAI);
}

void CHong_Ship_Body::On_Collision_Enter(CCollider* _Other_Collider)
{
	__super::On_Collision_Enter(_Other_Collider);
}

void CHong_Ship_Body::On_Collision_Stay(CCollider* _Other_Collider)
{
	__super::On_Collision_Stay(_Other_Collider);
}

void CHong_Ship_Body::On_Collision_Exit(CCollider* _Other_Collider)
{
	__super::On_Collision_Exit(_Other_Collider);
}

CHong_Ship_Body* CHong_Ship_Body::Create()
{
	CREATE_PIPELINE(CHong_Ship_Body);
}

CGameObject* CHong_Ship_Body::Clone(void* pArg)
{
	CLONE_PIPELINE(CHong_Ship_Body);
}

void CHong_Ship_Body::Free()
{
	__super::Free();

	delete this;
}

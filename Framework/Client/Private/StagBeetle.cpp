#include "stdafx.h"
#include "StagBeetle.h"
#include "GameInstance.h"
#include "Normal_Turret.h"
#include "Rocket_Turret.h"

CStagBeetle::CStagBeetle(const CStagBeetle& Prototype)
{
	*this = Prototype;
}

HRESULT CStagBeetle::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CStagBeetle::Initialize(void* pArg)
{
	
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	__super::Initialize(pArg);

	return S_OK;
}

void CStagBeetle::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CStagBeetle::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
}

HRESULT CStagBeetle::Render_Begin(ID3DXEffect** Shader)
{
	m_pTransformCom->Scaling(_float3(0.01f, 0.01f, 0.01f), true);
	m_pTransformCom->Bind_WorldMatrix();

	D3DXHANDLE ColorHandle = (*Shader)->GetParameterByName(0, "Color");

	float floatArray[3];
	floatArray[0] = 0.7f;
	floatArray[1] = 0.0f;
	floatArray[2] = 0.0f;

	(*Shader)->SetFloatArray(ColorHandle, floatArray, 3);


	return S_OK;
}

HRESULT CStagBeetle::Render()
{
	__super::Render();

	m_pMeshCom->Render_Mesh();

	return S_OK;
}

void CStagBeetle::Update_Target(CGameObject* _Target)
{
}

void CStagBeetle::SetUp_Components_For_Child()
{
	CStatus::STATUS Status;
	Status.fAttack = 1.f;
	Status.fArmor = 5.f;
	Status.fMaxHp = 500.f;
	Status.fHp = Status.fMaxHp;


	m_pStatusCom = Add_Component<CStatus>(&Status);
	m_pStatusCom->Set_WeakPtr(&m_pStatusCom);

	m_pMeshCom = Add_Component<CMesh_Ship2>();
	m_pMeshCom->Set_WeakPtr((void**)&m_pMeshCom);
	m_pMeshCom->Set_Texture(TEXT("Red_Cube"), MEMORY_TYPE::MEMORY_STATIC);

	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.Set_Preset_Scouge();

	m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);


	COLLISION_TYPE eBulletCollisionType = COLLISION_TYPE::MONSTER_ATTACK;

	CNormal_Turret* Posin = static_cast<CNormal_Turret*>(GAMEINSTANCE->Add_GameObject<CNormal_Turret>(CURRENT_LEVEL, TEXT("Normal_Turret"), m_pTransformCom, &eBulletCollisionType));
	Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(2.f, 1.0f, 2.f));
	m_pPosinList.push_back(Posin);
	Posin->Set_WeakPtr(&m_pPosinList.back());

	Posin = static_cast<CNormal_Turret*>(GAMEINSTANCE->Add_GameObject<CNormal_Turret>(CURRENT_LEVEL, TEXT("Normal_Turret"), m_pTransformCom, &eBulletCollisionType));
	Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(-2.f, 1.0f, 2.f));
	m_pPosinList.push_back(Posin);
	Posin->Set_WeakPtr(&m_pPosinList.back());


	m_pStateCom->Link_RigidBody(m_pRigidBodyCom);
	m_pStateCom->Link_AI_Transform(m_pTransformCom);
	

	m_pAIControllerCom->Link_Object(this);
	m_pAIControllerCom->Set_Enable(false);
	m_pAIControllerCom->Set_UsableStates(m_pAIControllerCom->Get_States_Preset_AI_Default());


	m_pColliderCom->Link_Transform(m_pTransformCom);
	m_pColliderCom->Set_Collider_Size(_float3(3.f, 3.f, 3.f));
	m_pColliderCom->Set_WeakPtr(&m_pColliderCom);

	Set_Controller(CONTROLLER::AI);
}

void CStagBeetle::On_Change_Controller(const CONTROLLER& _IsAI)
{
	__super::On_Change_Controller(_IsAI);
}

void CStagBeetle::On_Collision_Enter(CCollider* _Other_Collider)
{
	__super::On_Collision_Enter(_Other_Collider);
}

void CStagBeetle::On_Collision_Stay(CCollider* _Other_Collider)
{
	__super::On_Collision_Stay(_Other_Collider);
}

void CStagBeetle::On_Collision_Exit(CCollider* _Other_Collider)
{
	__super::On_Collision_Exit(_Other_Collider);
}

CStagBeetle* CStagBeetle::Create()
{
	CREATE_PIPELINE(CStagBeetle);
}

CGameObject* CStagBeetle::Clone(void* pArg)
{
	CLONE_PIPELINE(CStagBeetle);
}

void CStagBeetle::Free()
{
	__super::Free();

	delete this;
}

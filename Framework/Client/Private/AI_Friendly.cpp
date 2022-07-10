#include "stdafx.h"
#include "AI_Friendly.h"
#include "GameInstance.h"
#include "Normal_Turret.h"
#include <Fire_PSystem.h>
#include <Bomb_Effect.h>

CAI_Friendly::CAI_Friendly()
{
}

CAI_Friendly::CAI_Friendly(const CAI_Friendly& Prototype)
{
	*this = Prototype;

	Add_Component<CTransform>();
}

HRESULT CAI_Friendly::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CAI_Friendly::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;


	return S_OK;
}

void CAI_Friendly::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

}

void CAI_Friendly::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);


	ISVALID(m_pRendererCom, );

	m_fTime -= fTimeDelta;
	if (m_fTime < 0.f)
	{
		m_pTargetingCom->Make_TargetList_Distance(GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("Monster")), m_pTransformCom->Get_State(CTransform::STATE_POSITION, true), 10000.f);
		

		auto TargetList = m_pTargetingCom->Get_Targetting();

		if (!TargetList->empty())
		{
			Update_PosinTarget(TargetList->begin()->second);
		}

		m_fTime = 3.f;
	}

	m_pRigidBodyCom->Update_Transform(fTimeDelta);

	_float3 vPos = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);

	if (GAMEINSTANCE->IsIn(&vPos))
		m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_DEFERRED, this);
}

HRESULT CAI_Friendly::Render_Begin(ID3DXEffect** Shader)
{
	m_pTransformCom->Bind_WorldMatrix();

	D3DXHANDLE ColorHandle = (*Shader)->GetParameterByName(0, "Color");

	float floatArray[3];
	floatArray[0] = 0.0f;
	floatArray[1] = 0.7f;
	floatArray[2] = 0.0f;

	(*Shader)->SetFloatArray(ColorHandle, floatArray, 3);

	return S_OK;
}

HRESULT CAI_Friendly::Render()
{
	/*m_pColliderCom->Debug_Render();
	m_pPreColliderCom->Debug_Render();*/


	__super::Render();

	m_pMeshCom->Render_Mesh();


	return S_OK;
}

void CAI_Friendly::On_Change_Controller(const CONTROLLER& _IsAI)
{
	if (_IsAI == CONTROLLER::PLAYER)
	{
		//m_pAIControllerCom->Set_Enable(false);
		//m_pPlayerController->Set_Enable(true);
		//이 게임오브젝트가 플레이어라면, 카메라에게 이 게임 오브젝트를 보도록 하겠다.
		//GAMEINSTANCE->Set_Camera_Target(m_pTransformCom, TEXT("FPS"));
		//GAMEINSTANCE->Set_Camera_Target(m_pTransformCom, TEXT("Shoulder"));
		//GAMEINSTANCE->Set_Camera_Target(m_pTransformCom, TEXT("TPS"));
	}
	else
	{
		m_pAIControllerCom->Set_Enable(true);
		m_pPlayerController->Set_Enable(false);
	}
}

void CAI_Friendly::On_Collision_Enter(CCollider* _Other_Collider)
{
	if (_Other_Collider->Get_Collision_Type() == COLLISION_TYPE::MONSTER_ATTACK)
	{
		m_pStatusCom->Add_Status(CStatus::STATUSID::STATUS_HP, -1.f);
		((CFire_PSystem*)GAMEINSTANCE->Add_GameObject<CFire_PSystem>(CURRENT_LEVEL, TEXT("Particle_Fire"), nullptr, nullptr, true))->AddParticle(50, m_pTransformCom->Get_World_State(CTransform::STATE_POSITION));

		if (m_pStatusCom->Get_Status().fHp <= DBL_EPSILON)
		{
			Set_Dead();
			_float3 MyPos = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);
			((CBomb_Effect*)GAMEINSTANCE->Add_GameObject<CBomb_Effect>(CURRENT_LEVEL, TEXT("Bomb"), nullptr, nullptr, false))->Set_Pos(MyPos);

		}
	}
}

void CAI_Friendly::On_Collision_Stay(CCollider* _Other_Collider)
{
}

void CAI_Friendly::On_Collision_Exit(CCollider* _Other_Collider)
{
}

HRESULT CAI_Friendly::SetUp_Components()
{
	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);
	m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(rand() % 20, rand() % 20, rand() % 20));

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);

	m_pTargetingCom = Add_Component<CTargeting>();
	m_pTargetingCom->Set_WeakPtr(&m_pTargetingCom);

	m_pMeshCom = Add_Component<CMesh_KangShip>();
	m_pMeshCom->Set_WeakPtr(&m_pMeshCom);
	m_pMeshCom->Set_Texture(TEXT("Mesh_Cube"), MEMORY_TYPE::MEMORY_STATIC);

	
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
	RigidBodyDesc.m_fOwnerSpeed = 80.f;
	RigidBodyDesc.m_fOwnerAccel = 8.f;
	RigidBodyDesc.m_fOwnerRadSpeed = D3DXToRadian(90.0f);
	RigidBodyDesc.m_fOwnerRadAccel = 0.3f;
	RigidBodyDesc.m_fOwnerJump = 5.f;
	RigidBodyDesc.m_fOwnerJumpScale = 1.f;

	RigidBodyDesc.m_fFrictional = 0.05f;
	RigidBodyDesc.m_fRadFrictional = 0.02f;
	RigidBodyDesc.m_fRadZ = 0.01f;

	RigidBodyDesc.m_fOwnerLiftSpeed = 20.f;
	RigidBodyDesc.m_fOwnerLiftAccel = 0.3f;
	RigidBodyDesc.m_fRadDrag = 1.f;
	RigidBodyDesc.m_fDirDrag = 0.05f;
	m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);

#pragma endregion Rigid_Body Setting

#pragma region Collider Setting


	COLLISION_TYPE eCollisionType = COLLISION_TYPE::PLAYER;
	m_pColliderCom = Add_Component<CCollider_OBB>(&eCollisionType);
	m_pColliderCom->Link_Transform(m_pTransformCom);
	m_pColliderCom->Set_Collider_Size(_float3(1.f, 1.f, 1.f));
	m_pColliderCom->Set_WeakPtr(&m_pColliderCom);


#pragma endregion Collider Setting

#pragma region Posin Setting

	CNormal_Turret* Posin = static_cast<CNormal_Turret*>(GAMEINSTANCE->Add_GameObject<CNormal_Turret>(CURRENT_LEVEL, TEXT("Normal_Turret"), m_pTransformCom));
	Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(0.f, 1.f, 0.f));
	m_pMyPosinList.push_back(Posin);
	Posin->Set_WeakPtr(&m_pMyPosinList.back());


#pragma endregion Posin Setting

	m_pStateCom = Add_Component<CState_Move>();
	m_pStateCom->Set_WeakPtr(&m_pStateCom);
	m_pStateCom->Link_RigidBody(m_pRigidBodyCom);
	m_pStateCom->Link_AI_Transform(m_pTransformCom);


	m_pAIControllerCom = Add_Component<CAI_Controller>();
	m_pAIControllerCom->Set_WeakPtr(&m_pAIControllerCom);
	m_pAIControllerCom->Link_Object(this);
	m_pAIControllerCom->Set_Enable(false);
	m_pAIControllerCom->Set_UsableStates(m_pAIControllerCom->Get_States_Preset_AI_Default());

	m_pPlayerController = Add_Component<CPlayer_Controller>();
	m_pPlayerController->Set_WeakPtr(&m_pPlayerController);
	m_pPlayerController->Link_Object(this);
	m_pPlayerController->Set_Enable(false);

	Set_Controller(CONTROLLER::AI);

	return S_OK;
}

void CAI_Friendly::Update_PosinTarget(CGameObject* _Target)
{

	if (!_Target)
		return;

	for (auto& elem : m_pMyPosinList)
	{
		elem->Set_AI_Target(_Target);
	}
}

CAI_Friendly* CAI_Friendly::Create()
{
	CREATE_PIPELINE(CAI_Friendly);
}

CGameObject* CAI_Friendly::Clone(void* pArg)
{
	CLONE_PIPELINE(CAI_Friendly);
}

void CAI_Friendly::Free()
{
	__super::Free();

	delete this;
}

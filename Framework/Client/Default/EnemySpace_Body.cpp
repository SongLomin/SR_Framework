#include "stdafx.h"
#include "EnemySpace_Body.h"
#include "GameInstance.h"
#include "Normal_Turret.h"
#include "State_Move.h"
#include "MovingCamera.h"
#include <TargetingBox.h>
#include "Math_Utillity.h"
#include "Mesh_EnemySpace.h"
#include <Fire_PSystem.h>

CEnemySpace_Body::CEnemySpace_Body(const CEnemySpace_Body& Prototype)
{
	*this = Prototype;

	m_pTransformCom = Add_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);
	//m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(rand()% 100, rand() % 20, rand() % 100));
	//m_pTransformCom->Update_WorldMatrix();
}

HRESULT CEnemySpace_Body::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CEnemySpace_Body::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

#pragma region 초기 위치 설정


	m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(rand() % 100, rand() % 20, 900.f + 20.f));
	m_pTransformCom->Update_WorldMatrix();

#pragma endregion 초기 위치 설정

	GAMEINSTANCE->Add_GameObject<CTargetingBox>(CURRENT_LEVEL,
		TEXT("Targeting"), m_pTransformCom)->Set_Enable(false);

	return S_OK;
}

void CEnemySpace_Body::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


	ISVALID(m_pTransformCom);

	
	/*_float3 MyScreenPos;
	CMath_Utillity::WorldToScreen(&m_pTransformCom->Get_State(CTransform::STATE::STATE_POSITION, true), &MyScreenPos);

	GAMEINSTANCE->Add_Text(
		_point{ (long)MyScreenPos.x, (long)MyScreenPos.y },
		D3DCOLOR_ARGB(255, 0, 0, 255),
		0.0f,
		L"HP : %d / 10",
		1,
		(_int)m_pStatusCom->Get_Status().fHp);*/
    
}

void CEnemySpace_Body::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);


	m_fTime -= fTimeDelta;
	if (m_fTime < 0.f)
	{
		m_pTargetingCom->Make_AI_TargetList(GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("Player")), m_pTransformCom);
		Update_Target();
		m_fTime = 1.f;
	}


	m_pRigidBodyCom->Update_Transform(fTimeDelta);
	_float3 vPos = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);

	if(GAMEINSTANCE->IsIn(&vPos))
		m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_DEFERRED, this);

}

HRESULT CEnemySpace_Body::Render_Begin(ID3DXEffect** Shader)
{
	m_pTransformCom->Scaling(_float3(0.05f, 0.05f, 0.05f), true);
	m_pTransformCom->Bind_WorldMatrix();

	D3DXHANDLE ColorHandle = (*Shader)->GetParameterByName(0, "Color");

	float floatArray[3];
	floatArray[0] = 0.7f;
	floatArray[1] = 0.0f;
	floatArray[2] = 0.0f;

	(*Shader)->SetFloatArray(ColorHandle, floatArray, 3);


	return S_OK;
}

HRESULT CEnemySpace_Body::Render()
{


	/*m_pColliderCom->Debug_Render();
	m_pColliderPreCom->Debug_Render();*/

	__super::Render();

	m_pMeshCom->Render_Mesh();

	return S_OK;
}

HRESULT CEnemySpace_Body::SetUp_Components()
{

	CStatus::STATUS Status;
	Status.fHp = 20.f;
	Status.fAttack = 1.f;
	Status.fArmor = 5.f;

	m_pStatusCom = Add_Component<CStatus>(&Status);
	m_pStatusCom->Set_WeakPtr(&m_pStatusCom);


	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr((void**)&m_pRendererCom);
	//m_pRendererCom->Set_Textures_From_Key(TEXT("Test"), MEMORY_TYPE::MEMORY_DYNAMIC);


	m_pMeshCom = Add_Component<CMesh_EnemySpace>();
	m_pMeshCom->Set_WeakPtr((void**)&m_pMeshCom);
	m_pMeshCom->Set_Texture(TEXT("Red_Cube"), MEMORY_TYPE::MEMORY_STATIC);

	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.m_fOwnerSpeed = 10.f;
	RigidBodyDesc.m_fOwnerAccel = 0.5f;
	RigidBodyDesc.m_fOwnerRadSpeed = D3DXToRadian(90.0f);
	RigidBodyDesc.m_fOwnerRadAccel = 0.3f;
	RigidBodyDesc.m_fOwnerJump = 5.f;
	RigidBodyDesc.m_fOwnerJumpScale = 1.f;

	RigidBodyDesc.m_fFrictional = 0.05f;
	RigidBodyDesc.m_fRadFrictional = 0.02f;
	RigidBodyDesc.m_fRadZ = 0.01f;


	RigidBodyDesc.m_fOwnerLiftSpeed = 10.f;
	RigidBodyDesc.m_fOwnerLiftAccel = 0.3f;
	RigidBodyDesc.m_fRadDrag = 1.f;
	RigidBodyDesc.m_fDirDrag = 0.05f;
	RigidBodyDesc.m_fOwnerAccel = 0.1f;

	m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);

	
	m_pStateCom = Add_Component<CState_Move>();
	m_pStateCom->Set_WeakPtr((void**)m_pStateCom);
	m_pStateCom->Link_RigidBody(m_pRigidBodyCom);
	m_pStateCom->Link_AI_Transform(m_pTransformCom);


	m_pTargetingCom = Add_Component<CTargeting>();
	m_pTargetingCom->Set_WeakPtr(&m_pTargetingCom);

	
	COLLISION_TYPE eBulletCollisionType = COLLISION_TYPE::MONSTER_ATTACK;

	CNormal_Turret* Posin = static_cast<CNormal_Turret*>(GAMEINSTANCE->Add_GameObject<CNormal_Turret>(CURRENT_LEVEL, TEXT("Normal_Turret"), m_pTransformCom, &eBulletCollisionType));
	Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(2.f, 1.5f, 0.f));
	m_pPosinList.push_back(Posin);
	Posin->Set_WeakPtr(&m_pPosinList.back());

	Posin = static_cast<CNormal_Turret*>(GAMEINSTANCE->Add_GameObject<CNormal_Turret>(CURRENT_LEVEL, TEXT("Normal_Turret"), m_pTransformCom, &eBulletCollisionType));
	Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(0.f, 1.5f, 0.f));
	m_pPosinList.push_back(Posin);
	Posin->Set_WeakPtr(&m_pPosinList.back());

	m_pAIControllerCom = Add_Component<CAI_Controller>();
	m_pAIControllerCom->Set_WeakPtr(&m_pAIControllerCom);
	m_pAIControllerCom->Link_Object(this);
	m_pAIControllerCom->Set_Enable(false);


	COLLISION_TYPE eCollisionType = COLLISION_TYPE::MONSTER;
	m_pColliderCom = Add_Component<CCollider_Sphere>(&eCollisionType);
	m_pColliderCom->Link_Transform(m_pTransformCom);
	m_pColliderCom->Set_Collider_Size(_float3(3.f, 3.f, 3.f));
	m_pColliderCom->Set_WeakPtr(&m_pColliderCom);

	Set_Controller(CONTROLLER::AI);

	return S_OK;
}

void CEnemySpace_Body::Update_Target()
{
	map<_float, CGameObject*>* TargetList = m_pTargetingCom->Get_Targetting();

	if (TargetList->empty())
	{
		/*for (auto iter = m_pPosinList.begin(); iter != m_pPosinList.end();)
		{
			(*iter)->Set_Target(nullptr);
			++iter;
		}*/
		return;
	}

	for (auto& elem : m_pPosinList)
	{
		
		elem->Set_Target((*TargetList->begin()).second);
	}

}

void CEnemySpace_Body::On_Change_Controller(const CONTROLLER& _IsAI)
{
	if (_IsAI == CONTROLLER::AI)
	{
		m_pAIControllerCom->Set_Enable(true);
	}
	else
	{
		return;
	}
}


CEnemySpace_Body* CEnemySpace_Body::Create()
{
	CREATE_PIPELINE(CEnemySpace_Body);
}

CGameObject* CEnemySpace_Body::Clone(void* pArg)
{
	CLONE_PIPELINE(CEnemySpace_Body);
}

void CEnemySpace_Body::Free()
{
	__super::Free();

	delete this;
}

void CEnemySpace_Body::On_Collision_Enter(CCollider* _Other_Collider)
{
	if (_Other_Collider->Get_Collision_Type() == COLLISION_TYPE::PLAYER_ATTACK)
	{
		m_pStatusCom->Add_Status(CStatus::STATUSID::STATUS_HP, -1.f);
		((CFire_PSystem*)GAMEINSTANCE->Add_GameObject<CFire_PSystem>(CURRENT_LEVEL, TEXT("Particle"), nullptr, nullptr, true))->AddParticle(50, m_pTransformCom->Get_World_State(CTransform::STATE_POSITION));

		if (m_pStatusCom->Get_Status().fHp <= DBL_EPSILON)
		{
			Set_Dead();	
		}
	}
}

void CEnemySpace_Body::On_Collision_Stay(CCollider* _Other_Collider)
{
}

void CEnemySpace_Body::On_Collision_Exit(CCollider* _Other_Collider)
{
}

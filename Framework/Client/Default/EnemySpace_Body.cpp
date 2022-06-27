#include "stdafx.h"
#include "EnemySpace_Body.h"
#include "GameInstance.h"
#include "EnemySpace_RightBody.h"
#include "EnemySpace_Posin.h"
#include "State_Move.h"
#include "MovingCamera.h"
#include <TargetingBox.h>


CEnemySpace_Body::CEnemySpace_Body(const CEnemySpace_Body& Prototype)
{
	*this = Prototype;
	m_pTransformCom = Add_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);
	m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(rand()% 100, rand() % 20, rand() % 100));
	m_pTransformCom->Update_WorldMatrix();
}

HRESULT CEnemySpace_Body::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CEnemySpace_Body::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;


	
	GAMEINSTANCE->Add_GameObject<CTargetingBox>(CURRENT_LEVEL,
		TEXT("Targeting"), m_pTransformCom)->Set_Enable(false);

	return S_OK;
}

void CEnemySpace_Body::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


	ISVALID(m_pTransformCom);

	if (KEY_INPUT(KEY::SPACE, KEY_STATE::TAP))
	{
		CMovingCamera* pMovingCam = (CMovingCamera*)GAMEINSTANCE->Get_MovingCam();
		pMovingCam->Boss_Cinematic(m_pTransformCom);
	}

 
	m_pStateCom->State_Change(m_pPlayerTransformCom,fTimeDelta);


	/*m_pRigidBodyCom->Add_Dir(CRigid_Body::FRONT);
	m_pRigidBodyCom->Add_Dir(CRigid_Body::RIGHT);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, m_pPlayerTransformCom->Get_State(CTransform::STATE_LOOK, true), true);*/

	//m_pStateCom->State_Tagetting(m_pPlayerTransformCom, fTimeDelta, 1);
    
 
	map<_float, CGameObject*>* TargetList = m_pTargetingCom->Get_Targetting();
	
	if (TargetList->empty())
	{
		m_pStateCom->State_Change(m_pTransformCom, fTimeDelta);
	}
	else
	{
		CGameObject* TargetCheck = TargetList->begin()->second;
		if (!TargetCheck)
		{
			return;
		}
		m_pStateCom->State_Tagetting(TargetList->begin()->second->Get_Component<CTransform>(), fTimeDelta, 7.f);
	}


	/*m_pRigidBodyCom->Add_Dir(CRigid_Body::FRONT);
	m_pRigidBodyCom->Add_Dir(CRigid_Body::RIGHT);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, m_pPlayerTransformCom->Get_State(CTransform::STATE_LOOK, true), true);*/

	//m_pStateCom->State_Tagetting(m_pPlayerTransformCom, fTimeDelta, 1);
    
}

void CEnemySpace_Body::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);


	m_fTime -= fTimeDelta;
	if (m_fTime < 0.f)
	{
		m_pTargetingCom->Make_AI_TargetList(GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("Player_Body")), m_pTransformCom);
		Update_Target();
		m_fTime = 1.f;
	}


 	m_pRigidBodyCom->Update_Transform(fTimeDelta);


	m_fTime -= fTimeDelta;
	if (m_fTime < 0.f)
	{
		m_pTargetingCom->Make_AI_TargetList(GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("AI_Player")), m_pTransformCom);
		Update_Target();
		m_fTime = 1.f;
	}


	m_pRigidBodyCom->Update_Transform(fTimeDelta);
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);

}

HRESULT CEnemySpace_Body::Render()
{
	//m_pColliderCom->Debug_Render();
	//m_pColliderPreCom->Debug_Render();

	__super::Render();

	m_pTransformCom->Bind_WorldMatrix();


	m_pRendererCom->Bind_Texture(1);
	m_pMeshCom->Render_Mesh(0);
	m_pRendererCom->UnBind_Texture();

	return S_OK;
}

HRESULT CEnemySpace_Body::SetUp_Components()
{

	CStatus::STATUS Status;
	Status.fHp = 20.f;
	Status.fAttack = 1.f;
	Status.fArmor = 5.f;
	CStatus::STATUS Status;
	Status.fHp = 20.f;
	Status.fAttack = 1.f;
	Status.fArmor = 5.f;

	m_pStatusCom = Add_Component<CStatus>(&Status);
	m_pStatusCom->Set_WeakPtr(&m_pStatusCom);


	m_pStatusCom = Add_Component<CStatus>(&Status);
	m_pStatusCom->Set_WeakPtr(&m_pStatusCom);


	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr((void**)&m_pRendererCom);
	//m_pRendererCom->Set_Textures_From_Key(TEXT("Test"), MEMORY_TYPE::MEMORY_DYNAMIC);


	m_pMeshCom = Add_Component<CMesh_Cube>();
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
	m_pStateCom->Link_AiTransform(m_pTransformCom);
	m_pStateCom->Link_AI_Transform(m_pTransformCom);


	m_pTargetingCom = Add_Component<CTargeting>();
	m_pTargetingCom->Set_WeakPtr(&m_pTargetingCom);


	m_pTargetingCom = Add_Component<CTargeting>();
	m_pTargetingCom->Set_WeakPtr(&m_pTargetingCom);


	GAMEINSTANCE->Add_GameObject<CEnemySpace_RightBody>(CURRENT_LEVEL, TEXT("EnemySpace_RightBody"), m_pTransformCom);


	CEnemySpace_Posin* Posin = static_cast<CEnemySpace_Posin*>(GAMEINSTANCE->Add_GameObject<CEnemySpace_Posin>(CURRENT_LEVEL, TEXT("EnemySpace_Posin"), m_pTransformCom));
	Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(2.f, 1.5f, 0.f));
	m_pPosinList.push_back(Posin);
	Posin->Set_WeakPtr(&m_pPosinList.back());

	Posin = static_cast<CEnemySpace_Posin*>(GAMEINSTANCE->Add_GameObject<CEnemySpace_Posin>(CURRENT_LEVEL, TEXT("EnemySpace_Posin"), m_pTransformCom));
	Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(0.f, 1.5f, 0.f));
	m_pPosinList.push_back(Posin);
	Posin->Set_WeakPtr(&m_pPosinList.back());


	COLLISION_TYPE eCollisionType = COLLISION_TYPE::MONSTER;
	m_pColliderCom = Add_Component<CCollider_OBB>(&eCollisionType);
	m_pColliderCom->Link_Transform(m_pTransformCom);
	m_pColliderCom->Set_Collider_Size(_float3(1.f, 1.f, 1.f));
	m_pColliderCom->Set_WeakPtr(&m_pColliderCom);

	CEnemySpace_Posin* Posin = static_cast<CEnemySpace_Posin*>(GAMEINSTANCE->Add_GameObject<CEnemySpace_Posin>(CURRENT_LEVEL, TEXT("EnemySpace_Posin"), m_pTransformCom));
	Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(2.f, 1.5f, 0.f));
	m_pPosinList.push_back(Posin);
	Posin->Set_WeakPtr(&m_pPosinList.back());

	Posin = static_cast<CEnemySpace_Posin*>(GAMEINSTANCE->Add_GameObject<CEnemySpace_Posin>(CURRENT_LEVEL, TEXT("EnemySpace_Posin"), m_pTransformCom));
	Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(0.f, 1.5f, 0.f));
	m_pPosinList.push_back(Posin);
	Posin->Set_WeakPtr(&m_pPosinList.back());



	m_pColliderPreCom = Add_Component<CCollider_Pre>();
	WEAK_PTR(m_pColliderPreCom);
	m_pColliderPreCom->Link_Transform(m_pTransformCom);
	//구체라서 x만 받는다.
	m_pColliderPreCom->Set_Collider_Size(_float3(4.5f, 0.f, 0.f));


	COLLISION_TYPE eCollisionType = COLLISION_TYPE::MONSTER;
	m_pColliderCom = Add_Component<CCollider_OBB>(&eCollisionType);
	m_pColliderCom->Link_Transform(m_pTransformCom);
	m_pColliderCom->Link_Pre_Collider(m_pColliderPreCom);
	m_pColliderCom->Set_Collider_Size(_float3(3.f, 3.f, 3.f));
	m_pColliderCom->Set_WeakPtr(&m_pColliderCom);



	return S_OK;
}

void CEnemySpace_Body::Update_Target()
{
	map<_float, CGameObject*>* TargetList = m_pTargetingCom->Get_Targetting();

	if (TargetList->empty())
	{
		for (auto iter = m_pPosinList.begin(); iter != m_pPosinList.end();)
		{
			(*iter)->Set_Target(nullptr);
			++iter;
		}
		return;
	}

	vector<CGameObject*> TargetVec;

	for (auto& elem : *TargetList)
	{
		TargetVec.push_back(elem.second);
	}

	for (auto& elem : m_pPosinList)
	{
		
		elem->Set_Target(TargetVec.front());
	}

}

void CEnemySpace_Body::Update_Target()
{
	map<_float, CGameObject*>* TargetList = m_pTargetingCom->Get_Targetting();

	if (TargetList->empty())
	{
		for (auto iter = m_pPosinList.begin(); iter != m_pPosinList.end();)
		{
			(*iter)->Set_Target(nullptr);
			++iter;
		}
		return;
	}

	vector<CGameObject*> TargetVec;

	for (auto& elem : *TargetList)
	{
		TargetVec.push_back(elem.second);
	}

	for (auto& elem : m_pPosinList)
	{
		
		elem->Set_Target(TargetVec.front());
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

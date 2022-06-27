#include "stdafx.h"
#include "AI_Player.h"
#include "GameInstance.h"
#include "EnemySpace_Posin.h"

CAI_Player::CAI_Player()
{
}

CAI_Player::CAI_Player(const CAI_Player& Prototype)
{
	*this = Prototype;

	Add_Component<CTransform>();
}

HRESULT CAI_Player::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CAI_Player::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;


	return S_OK;
}

void CAI_Player::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	map<_float, CGameObject*>* TargetList = m_pTargetingCom->Get_Targetting();

	if (TargetList->empty())
	{
		m_pStateCom->State_Change(m_pTransformCom, fTimeDelta);
	}
	else
	{
		CGameObject* Target = TargetList->begin()->second;
		if (!Target)
		{
			return;
		}
		m_pStateCom->State_Tagetting(Target->Get_Component<CTransform>(), fTimeDelta, 7.f);
	}

	//m_pStateCom->State_Change(m_pTransformCom, fTimeDelta);
}

void CAI_Player::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);


	ISVALID(m_pRendererCom, );

	m_fTime -= fTimeDelta;
	if (m_fTime < 0.f)
	{
		m_pTargetingCom->Make_AI_TargetList(GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("EnemySpace_Body")), m_pTransformCom);
		Update_PosinTarget();
		m_fTime = 1.f;
	}

	m_pRigidBodyCom->Update_Transform(fTimeDelta);
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CAI_Player::Render_Begin()
{
	return S_OK;
}

HRESULT CAI_Player::Render()
{
	//m_pColliderCom->Debug_Render();
	//m_pPreColliderCom->Debug_Render();

	m_pTransformCom->Bind_WorldMatrix();

	__super::Render();

	m_pRendererCom->Bind_Texture(1);

	m_pMeshCom->Render_Mesh(5);

	m_pRendererCom->UnBind_Texture();


	return S_OK;
}

void CAI_Player::On_Change_Controller(const CONTROLLER& _IsAI)
{
}

void CAI_Player::On_Collision_Enter(CCollider* _Other_Collider)
{
}

void CAI_Player::On_Collision_Stay(CCollider* _Other_Collider)
{
}

void CAI_Player::On_Collision_Exit(CCollider* _Other_Collider)
{
}

HRESULT CAI_Player::SetUp_Components()
{
	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);
	m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(rand() % 20, rand() % 20, rand() % 20));

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);

	m_pTargetingCom = Add_Component<CTargeting>();
	m_pTargetingCom->Set_WeakPtr(&m_pTargetingCom);

	m_pMeshCom = Add_Component<CMesh_Cube>();
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
	RigidBodyDesc.m_fOwnerSpeed = 20.f;
	RigidBodyDesc.m_fOwnerAccel = 0.5f;
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


	m_pPreColliderCom = Add_Component<CCollider_Pre>();
	WEAK_PTR(m_pPreColliderCom);
	m_pPreColliderCom->Link_Transform(m_pTransformCom);
	//구체라서 x만 받는다.
	m_pPreColliderCom->Set_Collider_Size(_float3(4.5f, 0.f, 0.f));

	COLLISION_TYPE eCollisionType = COLLISION_TYPE::PLAYER;
	m_pColliderCom = Add_Component<CCollider_OBB>(&eCollisionType);
	m_pColliderCom->Link_Transform(m_pTransformCom);
	m_pColliderCom->Set_Collider_Size(_float3(1.f, 1.f, 1.f));
	m_pColliderCom->Set_WeakPtr(&m_pColliderCom);
	m_pColliderCom->Link_Pre_Collider(m_pPreColliderCom);


#pragma endregion Collider Setting

#pragma region Posin Setting

	CEnemySpace_Posin* Posin = static_cast<CEnemySpace_Posin*>(GAMEINSTANCE->Add_GameObject<CEnemySpace_Posin>(CURRENT_LEVEL, TEXT("EnemySpace_Posin"), m_pTransformCom));
	Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(0.f, 1.f, 0.f));
	m_pMyPosinList.push_back(Posin);
	Posin->Set_WeakPtr(&m_pMyPosinList.back());


#pragma endregion Posin Setting

	m_pStateCom = Add_Component<CState_Move>();
	m_pStateCom->Set_WeakPtr(&m_pStateCom);
	m_pStateCom->Link_RigidBody(m_pRigidBodyCom);
	m_pStateCom->Link_AI_Transform(m_pTransformCom);
	Set_Controller(CONTROLLER::AI);

	return S_OK;
}

void CAI_Player::Update_PosinTarget()
{
	map<_float, CGameObject*>* TargetList = m_pTargetingCom->Get_Targetting();
	
	if (TargetList->empty())
	{
		for (auto iter = m_pMyPosinList.begin(); iter != m_pMyPosinList.end();)
		{
			if (!(*iter))
			{
				iter = m_pMyPosinList.erase(iter);
				continue;
			}

			(*iter)->Set_Target(nullptr);
			iter++;
		}

		return;
	}

	vector<CGameObject*> TargetVec;

	for (auto& elem : *TargetList)
	{
		TargetVec.push_back(elem.second);
	}

	//멀티 타겟 모드
	if (m_bTargetMode)
	{
		_uint Index = 0;

		for (auto iter = m_pMyPosinList.begin(); iter != m_pMyPosinList.end();)
		{
			if (!(*iter))
			{
				iter = m_pMyPosinList.erase(iter);
				continue;
			}

			(*iter)->Set_Target(TargetVec[Index % TargetVec.size()]);
			Index++;
			iter++;
		}
	}

	//싱글 타겟 모드
	else
	{
		for (auto iter = m_pMyPosinList.begin(); iter != m_pMyPosinList.end();)
		{
			if (!(*iter))
			{
				iter = m_pMyPosinList.erase(iter);
				continue;
			}

			(*iter)->Set_Target(TargetVec.front());

			iter++;
		}

	}
}

CAI_Player* CAI_Player::Create()
{
	CREATE_PIPELINE(CAI_Player);
}

CGameObject* CAI_Player::Clone(void* pArg)
{
	CLONE_PIPELINE(CAI_Player);
}

void CAI_Player::Free()
{
	__super::Free();

	delete this;
}

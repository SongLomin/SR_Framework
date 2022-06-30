#include "stdafx.h"
#include "Test_Player.h"
#include "GameInstance.h"
#include "Normal_Turret.h"

CTest_Player::CTest_Player()
{
}

CTest_Player::CTest_Player(const CTest_Player& Prototype)
{
	*this = Prototype;

	Add_Component<CTransform>();


}

HRESULT CTest_Player::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CTest_Player::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(5.f, 1.f, 0.f));

	return S_OK;
}

void CTest_Player::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

}

void CTest_Player::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);


	ISVALID(m_pRendererCom, );

	m_fTime -= fTimeDelta;
	if (m_fTime < 0.f)
	{
		m_pTargetingCom->Make_AI_TargetList(GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("EnemySpace_Body")), m_pTransformCom);
		Update_PosinTarget(m_pTargetingCom->Get_TargetMode());
		m_fTime = 1.f;
	}

	m_pRigidBodyCom->Update_Transform(fTimeDelta);
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_DEFERRED, this);
}

HRESULT CTest_Player::Render_Begin(ID3DXEffect** Shader)
{
	m_pTransformCom->Bind_WorldMatrix();

	D3DXHANDLE ColorHandle = (*Shader)->GetParameterByName(0, "Color");

	float floatArray[3];
	floatArray[0] = 0.2f;
	floatArray[1] = 0.5f;
	floatArray[2] = 0.7f;

	(*Shader)->SetFloatArray(ColorHandle, floatArray, 3);

	return S_OK;
}

HRESULT CTest_Player::Render()
{
	/*m_pColliderCom->Debug_Render();
	m_pPreColliderCom->Debug_Render();

	m_pTransformCom->Bind_WorldMatrix();*/

	__super::Render();


	m_pMeshCom->Render_Mesh();


	return S_OK;
}

void CTest_Player::On_Change_Controller(const CONTROLLER& _IsAI)
{
	if (_IsAI == CONTROLLER::PLAYER)
	{
		m_pAIControllerCom->Set_Enable(false);
		m_pPlayerController->Set_Enable(true);
		m_pRigidBodyCom->Set_Mouse(true);
		//이 게임오브젝트가 플레이어라면, 카메라에게 이 게임 오브젝트를 보도록 하겠다.
		GAMEINSTANCE->Set_Camera_Target(m_pTransformCom, TEXT("FPS"));
		GAMEINSTANCE->Set_Camera_Target(m_pTransformCom, TEXT("Shoulder"));
		GAMEINSTANCE->Set_Camera_Target(m_pTransformCom, TEXT("TPS"));
	}
	else
	{
		m_pRigidBodyCom->Set_Mouse(false);
		m_pAIControllerCom->Set_Enable(true);
		m_pPlayerController->Set_Enable(false);
	}
}

void CTest_Player::On_Collision_Enter(CCollider* _Other_Collider)
{
}

void CTest_Player::On_Collision_Stay(CCollider* _Other_Collider)
{
}

void CTest_Player::On_Collision_Exit(CCollider* _Other_Collider)
{
}

HRESULT CTest_Player::SetUp_Components()
{
	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);
	m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(rand() % 20, rand() % 20, rand() % 20));

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);

	m_pTargetingCom = Add_Component<CTargeting>();
	m_pTargetingCom->Set_WeakPtr(&m_pTargetingCom);

	m_pMeshCom = Add_Component<CMesh_SongShip>();
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

	m_pPlayerController = Add_Component<CPlayer_Controller>();
	m_pPlayerController->Set_WeakPtr(&m_pPlayerController);
	m_pPlayerController->Link_Object(this);
	m_pPlayerController->Set_Enable(false);

	Set_Controller(CONTROLLER::AI);

	return S_OK;
}

void CTest_Player::Update_PosinTarget(TARGETMODE _TargetMode)
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
	if (_TargetMode == TARGETMODE::TARGET_MULTIRAY)
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
	if (_TargetMode == TARGETMODE::TARGET_SINGLE)
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

	if (_TargetMode == TARGETMODE::TARGET_MULTIWIDE)
	{
		// 전체 타겟팅 코드
	}
}

CTest_Player* CTest_Player::Create()
{
	CREATE_PIPELINE(CTest_Player);
}

CGameObject* CTest_Player::Clone(void* pArg)
{
	CLONE_PIPELINE(CTest_Player);
}

void CTest_Player::Free()
{
	__super::Free();

	delete this;
}

#include "stdafx.h"
#include "Player_Body.h"
#include "GameInstance.h"
#include "Player_RightBody.h"
#include <tchar.h>
#include "Normal_Turret.h"
#include "Cam_Free.h"
#include "Cam_TPS.h"
#include "Cam_FPS.h"
#include "Cam_Shoulder.h"
#include "Normal_Bullet.h"
#include "Math_Utillity.h"
#include "HpBar.h"



CPlayer_Body::CPlayer_Body()
{

}

CPlayer_Body::CPlayer_Body(const CPlayer_Body & Prototype)
{
	*this = Prototype;
	//m_szName = L"Body";
	m_pTransformCom = Add_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);
	m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(0.f, 1.f, 0.f));
	GAMEINSTANCE->Set_Current_Camera(TEXT("FPS"));
}

HRESULT CPlayer_Body::Initialize_Prototype()
{
	/* 백엔드로부터 값ㅇ를 어덩오낟. */


	return S_OK;
}

HRESULT CPlayer_Body::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;
	
	

	return S_OK;
}

void CPlayer_Body::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


	if (KEY_INPUT(KEY::C, KEY_STATE::TAP))
	{
		Set_Controller(CONTROLLER::AI);
	}
	if (KEY_INPUT(KEY::B, KEY_STATE::TAP))
	{
		Set_Controller(CONTROLLER::PLAYER);
	}

	m_fTime -= fTimeDelta;
	if (m_fTime < 0.f)
	{
		Update_PosinTarget();
		m_fTime = 1.f;
	}
}

void CPlayer_Body::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRigidBodyCom->Update_Transform(fTimeDelta);

	

	ISVALID(m_pRendererCom, );

	
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_DEFERRED, this);
}

HRESULT CPlayer_Body::Render_Begin(ID3DXEffect** Shader)
{
	//m_pTransformCom->Scaling(_float3(0.03f, 0.03f, 0.03f), true);
	m_pTransformCom->Bind_WorldMatrix();

	D3DXHANDLE ColorHandle = (*Shader)->GetParameterByName(0, "Color");

	float floatArray[3];
	floatArray[0] = 0.7f;
	floatArray[1] = 0.f;
	floatArray[2] = 0.7f;

	(*Shader)->SetFloatArray(ColorHandle, floatArray, 3);


	return S_OK;
}

HRESULT CPlayer_Body::Render()
{
	//m_pColliderCom->Debug_Render();
	//m_pPreColliderCom->Debug_Render();

	/*m_pTransformCom->Bind_WorldMatrix();*/
	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//m_pRendererCom->Bind_Texture(0);

	__super::Render();



	m_pMeshCubeCom->Render_Mesh(5);

	//m_pRendererCom->UnBind_Texture();

	
	 //DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}

HRESULT CPlayer_Body::SetUp_Components()
{

	//약포인터: 원본 객체가 삭제되면 약포인터로 등록된 포인터들도 nullptr로 바뀐다.
	//댕글링 포인터를 방지하기 위해 사용한다.


	CStatus::STATUS		Status;
	Status.fHp = 10.f;
	Status.fAttack = 7.f;
	Status.fArmor = 5.f;

	m_pStatusCom = Add_Component<CStatus>(&Status);
	m_pStatusCom->Set_WeakPtr(&m_pStatusCom);
	

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);
	m_pRendererCom->Set_Textures_From_Key(TEXT("Test"), MEMORY_TYPE::MEMORY_DYNAMIC);



	m_pMeshCubeCom = Add_Component<CMesh_Test>();
	m_pMeshCubeCom->Set_WeakPtr(&m_pMeshCubeCom);
	m_pMeshCubeCom->Set_Texture(TEXT("Mesh_Cube"), MEMORY_TYPE::MEMORY_STATIC);
	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.m_fOwnerSpeed = 40.f;
	RigidBodyDesc.m_fOwnerAccel = 0.5f;
	RigidBodyDesc.m_fOwnerRadSpeed= D3DXToRadian(90.0f);
	RigidBodyDesc.m_fOwnerRadAccel = 0.3f;
	RigidBodyDesc.m_fOwnerJump = 5.f;
	RigidBodyDesc.m_fOwnerJumpScale = 1.f;

	RigidBodyDesc.m_fFrictional = 0.05f;
	RigidBodyDesc.m_fRadFrictional =0.02f;
	RigidBodyDesc.m_fRadZ = 0.01f;


	RigidBodyDesc.m_fOwnerLiftSpeed = 40.f;
	RigidBodyDesc.m_fOwnerLiftAccel = 0.3f;
	RigidBodyDesc.m_fRadDrag = 1.f;
	RigidBodyDesc.m_fDirDrag = 0.05f;
	m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);

	m_pRigidBodyCom->Set_Mouse();

	m_pTargetingCom = Add_Component<CTargeting>();
	m_pTargetingCom->Set_WeakPtr(&m_pTargetingCom);

	

	m_pPreColliderCom = Add_Component<CCollider_Pre>();
	WEAK_PTR(m_pPreColliderCom);
	m_pPreColliderCom->Link_Transform(m_pTransformCom);
	//구체라서 x만 받는다.
	m_pPreColliderCom->Set_Collider_Size(_float3(4.5f, 0.f, 0.f));

	COLLISION_TYPE eCollisionType = COLLISION_TYPE::PLAYER_ATTACK;
	m_pColliderCom = Add_Component<CCollider_OBB>(&eCollisionType);
	m_pColliderCom->Set_WeakPtr(&m_pColliderCom);
	m_pColliderCom->Link_Transform(m_pTransformCom);
	m_pColliderCom->Set_Collider_Size(_float3(7.f, 1.5f, 1.f));
	m_pColliderCom->Link_Pre_Collider(m_pPreColliderCom);

	m_pStateCom = Add_Component<CState_Move>();
	m_pStateCom->Set_WeakPtr(&m_pStateCom);
	m_pStateCom->Link_RigidBody(m_pRigidBodyCom);
	m_pStateCom->Link_AI_Transform(m_pTransformCom);

	
	CNormal_Turret* Posin = static_cast<CNormal_Turret*>(GAMEINSTANCE->Add_GameObject<CNormal_Turret>(CURRENT_LEVEL, TEXT("Normal_Turret"), m_pTransformCom));
	Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(2.8f, -0.15f, 0.f));
	m_pMyPosinList.push_back(Posin);
	Posin->Set_WeakPtr(&m_pMyPosinList.back());

	Posin = static_cast<CNormal_Turret*>(GAMEINSTANCE->Add_GameObject<CNormal_Turret>(CURRENT_LEVEL, TEXT("Normal_Turret"), m_pTransformCom));
	Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(1.6f, -0.15f, 0.f));
	m_pMyPosinList.push_back(Posin);
	Posin->Set_WeakPtr(&m_pMyPosinList.back());

	Posin = static_cast<CNormal_Turret*>(GAMEINSTANCE->Add_GameObject<CNormal_Turret>(CURRENT_LEVEL, TEXT("Normal_Turret"), m_pTransformCom));
	Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(-1.6f, -0.15f, 0.f));
	m_pMyPosinList.push_back(Posin);
	Posin->Set_WeakPtr(&m_pMyPosinList.back());

	Posin = static_cast<CNormal_Turret*>(GAMEINSTANCE->Add_GameObject<CNormal_Turret>(CURRENT_LEVEL, TEXT("Normal_Turret"), m_pTransformCom));
	Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(-2.8f, -0.15f, 0.f));
	m_pMyPosinList.push_back(Posin);
	Posin->Set_WeakPtr(&m_pMyPosinList.back());

	m_pAIControllerCom = Add_Component<CAI_Controller>();
	m_pAIControllerCom->Set_WeakPtr(&m_pAIControllerCom);
	m_pAIControllerCom->Link_Object(this);
	m_pAIControllerCom->Set_Enable(false);

	m_pPlayerController = Add_Component<CPlayer_Controller>();
	m_pPlayerController->Set_WeakPtr(&m_pPlayerController);
	m_pPlayerController->Link_Object(this);
	m_pPlayerController->Set_Enable(false);

	m_pLight = Add_Component<CSpotLight>();
	WEAK_PTR(m_pLight);
	m_pLight->Set_Margin_Position(_float3(0.f, 5.f, 0.f));

	Set_Controller(CONTROLLER::PLAYER);


	return S_OK;
}

void CPlayer_Body::Update_PosinTarget()
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

void CPlayer_Body::On_Change_Controller(const CONTROLLER& _IsAI)
{

	// front 받아오는것은 임시 테스트용
	list<CGameObject*>* pAiObect = GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("Test_Player"));

		if (_IsAI == CONTROLLER::PLAYER)
		{
			m_pAIControllerCom->Set_Enable(false);
			m_pPlayerController->Set_Enable(true);
			m_pRigidBodyCom->Set_Mouse();

			if(pAiObect)
				pAiObect->front()->Set_Controller(CONTROLLER::AI);
			//이 게임오브젝트가 플레이어라면, 카메라에게 이 게임 오브젝트를 보도록 하겠다.
			GAMEINSTANCE->Set_Camera_Target(m_pTransformCom, TEXT("FPS"));
			GAMEINSTANCE->Set_Camera_Target(m_pTransformCom, TEXT("Shoulder"));
			GAMEINSTANCE->Set_Camera_Target(m_pTransformCom, TEXT("TPS"));
		}
		else
		{
			m_pAIControllerCom->Set_Enable(true);
			m_pPlayerController->Set_Enable(false);
			m_pRigidBodyCom->Set_Mouse();
			if(pAiObect)
				pAiObect->front()->Set_Controller(CONTROLLER::PLAYER);
		}

}

void CPlayer_Body::On_Collision_Enter(CCollider* _Other_Collider)
{
	int i = 0;
}

void CPlayer_Body::On_Collision_Stay(CCollider* _Other_Collider)
{

}

void CPlayer_Body::On_Collision_Exit(CCollider* _Other_Collider)
{
	int i = 0;
}


CPlayer_Body * CPlayer_Body::Create()
{
	CREATE_PIPELINE(CPlayer_Body);
}

CGameObject * CPlayer_Body::Clone(void* pArg)
{
	CLONE_PIPELINE(CPlayer_Body);
}

void CPlayer_Body::Free()
{
	__super::Free();
	
	delete this;
}

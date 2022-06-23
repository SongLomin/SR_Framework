#include "stdafx.h"
#include "Player_Body.h"
#include "GameInstance.h"
#include "Player_RightBody.h"
#include <tchar.h>
#include "Player_Posin.h"
#include "CameraPosin.h"
#include "Cam_Free.h"
#include "Cam_TPS.h"
#include "Cam_FPS.h"
#include "Cam_Shoulder.h"
#include "Player_ProPeller.h"
#include "Bullet.h"
#include "Math_Utillity.h"



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

	GAMEINSTANCE->Add_GameObject<CPlayer_RightBody>(CURRENT_LEVEL, TEXT("Dummy"), m_pTransformCom);

	GAMEINSTANCE->Add_GameObject<CPlayer_Posin>(CURRENT_LEVEL, TEXT("Posin"), m_pTransformCom)
		->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(2.f, 1.5f, 0.f));

	GAMEINSTANCE->Add_GameObject<CPlayer_Posin>(CURRENT_LEVEL, TEXT("Posin"), m_pTransformCom)
		->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(0.f, 1.5f, 0.f));

	//GAMEINSTANCE->Add_GameObject<CRing>(CURRENT_LEVEL, TEXT("Ring"), m_pTransformCom);

	GAMEINSTANCE->Add_GameObject<CPlayer_ProPeller>(CURRENT_LEVEL, TEXT("Player_ProPeller"), m_pTransformCom);

	GAMEINSTANCE->Add_GameObject<CPlayer_ProPeller>(CURRENT_LEVEL, TEXT("Player_ProPeller"), m_pTransformCom)
		->Get_Component<CTransform>()->Rotation(_float3(0.f, 1.f, 0.f), 30);
	
	return S_OK;
}

void CPlayer_Body::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	if (KEY_INPUT(KEY::W, KEY_STATE::HOLD))
		m_pRigidBodyCom->Add_Dir(CRigid_Body::FRONT);

	
	if (KEY_INPUT(KEY::S, KEY_STATE::HOLD))
		m_pRigidBodyCom->Add_Dir(CRigid_Body::BACK);

	if (KEY_INPUT(KEY::D, KEY_STATE::HOLD))
		m_pRigidBodyCom->Add_Dir(CRigid_Body::RIGHT);

	if (KEY_INPUT(KEY::A, KEY_STATE::HOLD))
		m_pRigidBodyCom->Add_Dir(CRigid_Body::LEFT);

	if (KEY_INPUT(KEY::SPACE, KEY_STATE::HOLD))
	{
		m_pRigidBodyCom->Add_Dir(CRigid_Body::JUMP);
	}

	if (KEY_INPUT(KEY::UP, KEY_STATE::HOLD))
	{
		m_pRigidBodyCom->Add_Dir(CRigid_Body::LIFT);
	}


	if (KEY_INPUT(KEY::Z, KEY_STATE::TAP))
	{
		m_pStatusCom->Add_Status(CStatus::STATUSID::STATUS_HP, -1.f);
	}

	if (KEY_INPUT(KEY::V, KEY_STATE::TAP))
	{
		switch (m_iCurrentCam)
		{
		case 0:
			GAMEINSTANCE->Set_Current_Camera(TEXT("Shoulder"));
			break;

		case 1:
			GAMEINSTANCE->Set_Current_Camera(TEXT("FPS"));
			break;

		case 2:
			GAMEINSTANCE->Set_Current_Camera(TEXT("TPS"));
			break;
		}
		
		m_iCurrentCam = (m_iCurrentCam + 1) % 3;
	}

	if (KEY_INPUT(KEY::L, KEY_STATE::TAP))
	{
		CONTROLLER Next_Controller = 
			Get_Controller() == CONTROLLER::PLAYER ? 
			CONTROLLER::AI : 
			CONTROLLER::PLAYER;

		Set_Controller(Next_Controller);
	}


	GAMEINSTANCE->Add_Text(
		_point{ 100, g_iWinCY - 100 },
		D3DCOLOR_ARGB(255, 130, 255, 0), 
		0.0f, 
		L"HP : %d", 
		1, 
		(_int)m_pStatusCom->Get_Status().fHp);

	GAMEINSTANCE->Add_Text(
		_point{ g_iWinCX - 300, g_iWinCY - 100 },
		L"남은 총알 : %d / %d",
		2,
		14, 300);

}

void CPlayer_Body::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	ISVALID(m_pRendererCom, );

	
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_PRIORITY, this);
}

HRESULT CPlayer_Body::Render()
{

	m_pTransformCom->Bind_WorldMatrix();
	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pRendererCom->Bind_Texture(0);

	__super::Render();

	if(Get_Controller() == CONTROLLER::PLAYER)
		m_pMeshCubeCom->Render_Mesh();
	m_pRendererCom->UnBind_Texture();

	
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



	m_pMeshCubeCom = Add_Component<CMesh_Cube>();
	m_pMeshCubeCom->Set_WeakPtr(&m_pMeshCubeCom);

	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.m_fOwnerSpeed = 10.f;
	RigidBodyDesc.m_fOwnerAccel = 0.1f;
	RigidBodyDesc.m_fOwnerRadSpeed= D3DXToRadian(90.0f);
	RigidBodyDesc.m_fOwnerRadAccel = 0.3f;
	RigidBodyDesc.m_fOwnerJump = 5.f;
	RigidBodyDesc.m_fOwnerJumpScale = 1.f;

	RigidBodyDesc.m_fFrictional = 0.05f;
	RigidBodyDesc.m_fRadFrictional =0.02f;
	RigidBodyDesc.m_fRadZ = 0.01f;


	RigidBodyDesc.m_fOwnerLiftSpeed = 3.f;
	RigidBodyDesc.m_fOwnerLiftAccel = 0.3f;
	RigidBodyDesc.m_fRadDrag = 1.f;
	RigidBodyDesc.m_fDirDrag = 0.05f;
	m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);

	m_pTargetingCom = Add_Component<CTargeting>();
	m_pTargetingCom->Set_WeakPtr(&m_pTargetingCom);

	//m_pCColliderCom = Add_Component<CCollider_OBB>();
	//m_pCColliderCom->Set_WeakPtr(&m_pCColliderCom);
	//m_pCColliderCom->Link_Transform(m_pTransformCom);



	
	//CGameObject* CameraPosin = GAMEINSTANCE->Add_GameObject<CCameraPosin>(CURRENT_LEVEL, TEXT("CameraPosin"), m_pTransformCom);	
	//m_pCameraPosin = (CCameraPosin*)GAMEINSTANCE->Add_GameObject<CCameraPosin>(CURRENT_LEVEL, TEXT("CameraPosin"), m_pTransformCom);
	
	GAMEINSTANCE->Add_GameObject<CPlayer_RightBody>(CURRENT_LEVEL, TEXT("Player_RightBody"), m_pTransformCom);

	GAMEINSTANCE->Add_GameObject<CPlayer_Posin>(CURRENT_LEVEL, TEXT("Player_Posin"), m_pTransformCom)
		->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(2.f, 1.5f, 0.f));;

	GAMEINSTANCE->Add_GameObject<CPlayer_Posin>(CURRENT_LEVEL, TEXT("Player_Posin"), m_pTransformCom)
		->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(0.f, 1.5f, 0.f));

	//GAMEINSTANCE->Add_GameObject<CRing>(CURRENT_LEVEL, TEXT("Player_ProPeller"), m_pTransformCom);

	GAMEINSTANCE->Add_GameObject<CPlayer_ProPeller>(CURRENT_LEVEL, TEXT("Player_ProPeller"), m_pTransformCom);

	GAMEINSTANCE->Add_GameObject<CPlayer_ProPeller>(CURRENT_LEVEL, TEXT("Player_ProPeller"), m_pTransformCom)
		->Get_Component<CTransform>()->Rotation(_float3(0.f, 1.f, 0.f), 30);

	Set_Controller(CONTROLLER::PLAYER);


	return S_OK;
}

void CPlayer_Body::On_Change_Controller(const CONTROLLER& _IsAI)
{
	if (_IsAI == CONTROLLER::PLAYER)
	{
		GAMEINSTANCE->Set_Camera_Target(m_pTransformCom, TEXT("FPS"));
		GAMEINSTANCE->Set_Camera_Target(m_pTransformCom, TEXT("Shoulder"));
		GAMEINSTANCE->Set_Camera_Target(m_pTransformCom, TEXT("TPS"));
		//if(m_pCameraPosin)
		//	m_pCameraPosin->Link_CameraTransfrom(GAMEINSTANCE->Get_Camera(TEXT("TPS"))->Get_Owner()->Get_Component<CTransform>());
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

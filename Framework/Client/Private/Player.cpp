#include "stdafx.h"
#include "Player.h"
#include "GameInstance.h"
#include "Normal_Turret.h"
#include <Booster_PSystem.h>
#include <Move_PSystem.h>
#include <Bomb_Effect.h>

CPlayer::CPlayer()
{
}

HRESULT CPlayer::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CPlayer::Initialize(void* pArg)
{
	return S_OK;
}

void CPlayer::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	list<CGameObject*>* pAiObect = GAMEINSTANCE->Find_Layer(LEVEL_STATIC, TEXT("Player"));
	_uint i = 0;

	if (!pAiObect)
		return;

	for (auto& elem : *pAiObect)
	{
		if (KEY_INPUT((KEY)((_uint)KEY::NUM1 + i), KEY_STATE::TAP))
		{
			elem->Set_Controller(CONTROLLER::PLAYER);
		}

			++i;
	}


	if (m_pRigid_BodyCom->Get_Booster())
	{
		//GAMEINSTANCE->Get_ParticleSystem<CBooster_PSystem>(CURRENT_LEVEL, TEXT("Particle_Booster"));
		((CBooster_PSystem*)GAMEINSTANCE->Get_ParticleSystem<CBooster_PSystem>(CURRENT_LEVEL, TEXT("Particle_Booster"), nullptr, nullptr))->AddParticle(900 * fTimeDelta, m_pTransformCom);
	}
	else if (m_pRigid_BodyCom->Get_Booster() == false)
	{
		_float3 Speed = m_pRigid_BodyCom->Get_Vector(RIGID_BODY::SPEED);
		
		_float vNow = fabs(D3DXVec3Length(&Speed)) / 30.f;
		if (vNow > 0.9f)
		{
			D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 0, 0);
			((CMove_PSystem*)GAMEINSTANCE->Get_ParticleSystem<CMove_PSystem>(CURRENT_LEVEL, TEXT("Particle_Smoke")))->AddParticle(500 * fTimeDelta, m_pTransformCom, color);
		}
	}
}

void CPlayer::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	ISVALID(m_pRendererCom, );

	m_fTime -= fTimeDelta;
	if (m_fTime < 0.f)
	{
		if (Get_Controller() == CONTROLLER::PLAYER)
		{
			Update_PosinTarget(m_pTargetingCom->Get_TargetMode());
		}
		else
		{
			m_pTargetingCom->Set_TargetMode(TARGETMODE::TARGET_MULTIRAY);
			m_pTargetingCom->Make_TargetList_Distance(GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("EnemySpace_Body")), m_pTransformCom->Get_State(CTransform::STATE_POSITION, true), 10000.f);	
		}
		m_fTime = 1.f;
	}
	m_pRigid_BodyCom->Update_Transform(fTimeDelta);

	_float3 vPos = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);

	if (GAMEINSTANCE->IsIn(&vPos))
		m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_DEFERRED, this);
}

HRESULT CPlayer::Render_Begin(ID3DXEffect** Shader)
{
	return S_OK;
}

HRESULT CPlayer::Render()
{
	__super::Render();
	m_pColliderCom->Debug_Render();

	return S_OK;
}

void CPlayer::On_Change_Controller(const CONTROLLER& _IsAI)
{

	if (_IsAI == CONTROLLER::PLAYER)
	{
		
		m_pAI_ControllerCom->Set_Enable(false);
		m_pPlayer_ControllerCom->Set_Enable(true);
		m_pRigid_BodyCom->Set_Mouse(true);

		CCamera* pCurCamera = GAMEINSTANCE->Get_Camera();
		CTransform* pCurCameraTransform = nullptr;//이게맞냐
		if(pCurCamera)
			pCurCameraTransform = GAMEINSTANCE->Get_Camera()->Get_Transform();

		GAMEINSTANCE->Set_Camera_Target(m_pTransformCom, TEXT("FPS"));
		GAMEINSTANCE->Set_Camera_Target(m_pTransformCom, TEXT("Shoulder"));
		GAMEINSTANCE->Set_Camera_Target(m_pTransformCom, TEXT("TPS"));
		if (pCurCameraTransform)
		{
			GAMEINSTANCE->Get_Camera()->Get_Transform();

			GAMEINSTANCE->Switch_Player(pCurCameraTransform, GAMEINSTANCE->Get_Camera()->Get_Transform(), TEXT("TPS"), 1.f);
		}
		list<CGameObject*>* pAiObect = GAMEINSTANCE->Find_Layer(LEVEL_STATIC, TEXT("Player"));

		if (pAiObect == nullptr)
			return;

		for (auto& elem : *pAiObect)
		{
			if (elem == this)
			{
				continue;
			}
			elem->Set_Controller(CONTROLLER::AI);
		}

		//이 게임오브젝트가 플레이어라면, 카메라에게 이 게임 오브젝트를 보도록 하겠다.
	}
	else if (_IsAI == CONTROLLER::AI)
	{
		m_pAI_ControllerCom->Set_Enable(true);
		m_pPlayer_ControllerCom->Set_Enable(false);
		m_pRigid_BodyCom->Set_Mouse(false);	
	}

}

void CPlayer::On_Collision_Enter(CCollider* _Other_Collider)
{
	if (_Other_Collider->Get_Collision_Type() == COLLISION_TYPE::MONSTER_ATTACK && Get_Controller() == CONTROLLER::PLAYER)
	{
		GAMEINSTANCE->Add_Shaking(0.4f, 0.1f);
		m_pStatusCom->Add_Status(CStatus::STATUSID::STATUS_HP, -1.f);

		if (m_pStatusCom->Get_Status().fHp <= DBL_EPSILON)
		{
			//Set_Dead();

			//_float3 MyPos = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);
			//((CBomb_Effect*)GAMEINSTANCE->Add_GameObject<CBomb_Effect>(CURRENT_LEVEL, TEXT("Bomb"), nullptr, nullptr, false))->Set_Pos(MyPos);

		}
	}


}

void CPlayer::On_Collision_Stay(CCollider* _Other_Collider)
{
}

void CPlayer::On_Collision_Exit(CCollider* _Other_Collider)
{
}

HRESULT CPlayer::SetUp_Components()
{
	m_pTransformCom = Add_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);

	m_pTargetingCom = Add_Component<CTargeting>();
	m_pTargetingCom->Set_WeakPtr(&m_pTargetingCom);
	m_pTargetingCom->Set_TargetMode(TARGETMODE::TARGET_SINGLE);

	COLLISION_TYPE eCollisionType = COLLISION_TYPE::PLAYER;
	m_pColliderCom = Add_Component<CCollider_Sphere>(&eCollisionType);
	m_pColliderCom->Set_WeakPtr(&m_pColliderCom);
	m_pColliderCom->Link_Transform(m_pTransformCom);

	m_pStateCom = Add_Component<CState_Move>();
	m_pStateCom->Set_WeakPtr(&m_pStateCom);

	m_pAI_ControllerCom = Add_Component<CAI_Controller>();
	m_pAI_ControllerCom->Set_WeakPtr(&m_pAI_ControllerCom);
	m_pAI_ControllerCom->Set_UsableStates(m_pAI_ControllerCom->Get_States_Preset_AI_Default());

	m_pPlayer_ControllerCom = Add_Component<CPlayer_Controller>();
	m_pPlayer_ControllerCom->Set_WeakPtr(&m_pPlayer_ControllerCom);

	SetUp_Components_For_Child();
	return S_OK;
}


void CPlayer::Update_PosinTarget(TARGETMODE _TargetMode)
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

			(*iter)->Set_Player_Target(nullptr);
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

			if (TargetVec[Index % TargetVec.size()])
			{
				(*iter)->Set_Player_Target(TargetVec[Index % TargetVec.size()]);
			}

			else
			{
				(*iter)->Set_Player_Target(nullptr);
			}
			

			(*iter)->Set_Player_Target(TargetVec[Index % TargetVec.size()]);
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

			(*iter)->Set_Player_Target(TargetVec.front());

			iter++;
		}

	}

	if (_TargetMode == TARGETMODE::TARGET_MULTIWIDE)
	{
		// 전체 타겟팅 코드
		_uint Index = 0;
		for (auto iter = m_pMyPosinList.begin(); iter != m_pMyPosinList.end();)
		{
			if (!(*iter))
			{
				iter = m_pMyPosinList.erase(iter);
				continue;
			}

			(*iter)->Set_Player_Target(TargetVec[Index % TargetVec.size()]);
			Index++;
			iter++;
		}

	}
}

void CPlayer::Change_Player()
{


}

void CPlayer::Free()
{
	__super::Free();
}

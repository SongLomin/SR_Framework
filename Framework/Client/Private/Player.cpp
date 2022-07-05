#include "stdafx.h"
#include "Player.h"
#include "GameInstance.h"
#include "Normal_Turret.h"

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
	list<CGameObject*>* pAiObect = GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("Player"));
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
			m_pTargetingCom->Make_AI_TargetList(GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("EnemySpace_Body")), m_pTransformCom);
			Update_PosinTarget(m_pTargetingCom->Get_TargetMode());
		}
		m_fTime = 1.f;
	}
	m_pRigid_BodyCom->Update_Transform(fTimeDelta);
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
		GAMEINSTANCE->Set_Camera_Target(m_pTransformCom, TEXT("FPS"));
		GAMEINSTANCE->Set_Camera_Target(m_pTransformCom, TEXT("Shoulder"));
		GAMEINSTANCE->Set_Camera_Target(m_pTransformCom, TEXT("TPS"));

		list<CGameObject*>* pAiObect = GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("Player"));

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
		GAMEINSTANCE->Add_Shaking(1.f, 0.1f);
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
}

void CPlayer::Free()
{
	__super::Free();
}

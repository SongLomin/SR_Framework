#include "stdafx.h"
#include "..\Public\Monster.h"
#include "GameInstance.h"
#include <Math_Utillity.h>
#include "Bomb_Effect.h"
#include "Fire_PSystem.h"
#include "Smoke_PSystem.h"
#include "Normal_Turret.h"
#include <TargetingBox.h>
#include "Bayonet_Turret.h"
#include <Enemy_GPS.h>
#include <AI_HPBar.h>
#include <MagmaSpace_Body.h>
#include "Rocket_Turret.h"
#include <Bullet.h>
#include "Rock_PSystem.h"
#include <Lazer_Turret.h>
#include "Turret.h"

HRESULT CMonster::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CMonster::Initialize(void* pArg)
{

	GAMEINSTANCE->Add_GameObject<CTargetingBox>(CURRENT_LEVEL,
		TEXT("Targeting"), m_pTransformCom)->Set_Enable(false);

	GAMEINSTANCE->Add_GameObject<CEnemy_GPS>(CURRENT_LEVEL, TEXT("GPS_Enemy"), m_pTransformCom);

	//m_pGPS = (CEnemy_GPS*)GAMEINSTANCE->Add_GameObject<CEnemy_GPS>(CURRENT_LEVEL, TEXT("GPS"),m_pTransformCom);
	
	m_pHPBar = GAMEINSTANCE->Add_GameObject<CAI_HPBar>(CURRENT_LEVEL, TEXT("AI_HPBar_UI"), m_pTransformCom, nullptr);

	m_pHPBar->Set_Enable(false);

	return S_OK;
}

void CMonster::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	

}

void CMonster::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_fTime -= fTimeDelta;
	if (m_fTime < 0.f)
	{
		m_pTargetingCom->Add_TargetList_Distance(GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("AI_Friendly")), m_pTransformCom->Get_State(CTransform::STATE_POSITION, true), 10000.f, true);
		m_pTargetingCom->Add_TargetList_Distance(GAMEINSTANCE->Find_Layer(LEVEL_STATIC, TEXT("Player")), m_pTransformCom->Get_State(CTransform::STATE_POSITION, true), 10000.f, false);
		m_pTargetingCom->Add_TargetList_Distance(GAMEINSTANCE->Find_Layer(LEVEL_STATIC, TEXT("TransportShip")), m_pTransformCom->Get_State(CTransform::STATE_POSITION, true), 10000.f, false);

		auto TargetList = m_pTargetingCom->Get_Targetting();

		if (!TargetList->empty())
		{
			Update_Target(TargetList->begin()->second);
		}

		m_fTime = 3.f;
	}

	if (m_pStatusCom->Get_Status().fHp < m_pStatusCom->Get_Status().fMaxHp / 2.f)
	{
		//((CSmoke_PSystem*)GAMEINSTANCE->Get_ParticleSystem<CSmoke_PSystem>(CURRENT_LEVEL, TEXT("Particle_Smoke")))->AddParticle(500 * fTimeDelta, m_pTransformCom->Get_World_State(CTransform::STATE_POSITION));
	}

	m_pRigidBodyCom->Update_Transform(fTimeDelta);
	_float3 vPos = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);


}

HRESULT CMonster::Render_Begin(ID3DXEffect** Shader)
{
	return S_OK;
}

HRESULT CMonster::Render()
{
	__super::Render();
	m_pColliderCom->Debug_Render();

	return S_OK;
}



void CMonster::On_Change_Controller(const CONTROLLER& _IsAI)
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

void CMonster::Update_Target(CGameObject* _Target)
{
	if (!_Target)
		return;

	if (!m_pPosinList.empty())
	{
		for (auto& elem : m_pPosinList)
		{
			if(elem)
				elem->Set_AI_Target(_Target);
		}
	}

	if (!m_pBayonetList.empty())
	{
		for (auto& elem : m_pBayonetList)
		{
			if(elem)
				elem->Set_AI_Target(_Target);
		}
	}

}

void CMonster::LookAt_Camera()
{
	_float4x4		ViewMatrix;

	DEVICE->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, *(_float3*)&ViewMatrix.m[0][0], true);
	m_pTransformCom->Set_State(CTransform::STATE_UP, *(_float3*)&ViewMatrix.m[1][0], true);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, *(_float3*)&ViewMatrix.m[2][0], true);
}

HRESULT CMonster::SetUp_Components()
{
    m_pTransformCom = Add_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr((void**)&m_pRendererCom);

	m_pTargetingCom = Add_Component<CTargeting>();
	m_pTargetingCom->Set_WeakPtr(&m_pTargetingCom);

	m_pStateCom = Add_Component<CState_Move>();
	m_pStateCom->Set_WeakPtr((void**)m_pStateCom);

	m_pAIControllerCom = Add_Component<CAI_Controller>();
	m_pAIControllerCom->Set_WeakPtr(&m_pAIControllerCom);

	


	SetUp_Components_For_Child();

	return S_OK;
}

void CMonster::Drop_Item()
{
	int random = rand() % 100;

	GAMEINSTANCE->PlaySoundW(TEXT("Drop_Turret.wav"), 1.f);

	CGameObject* Turret = nullptr;

	if (random < 15)
	{
		Turret = GAMEINSTANCE->Add_GameObject<CNormal_Turret>(LEVEL_STATIC, TEXT("Normal_Turret"), nullptr, nullptr, true);
	}

	else if (random < 25)
	{
		Turret = GAMEINSTANCE->Add_GameObject<CRocket_Turret>(LEVEL_STATIC, TEXT("Rocket_Turret"), nullptr, nullptr, true);
	}

	else if (random < 31)
	{
		//레이저 터렛

		Turret = GAMEINSTANCE->Add_GameObject<CLazer_Turret>(LEVEL_STATIC, TEXT("Lazer_Turret"), nullptr, nullptr, true);
	}

	else
	{
		return;
	}


	if (Turret)
	{
	
		Turret->Get_Component<CTransform>()->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION, true));
	}
}




void CMonster::On_Collision_Enter(CCollider* _Other_Collider)
{

	 if (_Other_Collider->Get_Collision_Type() == COLLISION_TYPE::PLAYER_ATTACK)
	{
		m_pHPBar->Set_Enable(true);

		_float fDamage = static_cast<CBullet*>(_Other_Collider->Get_Owner())->Get_Damage();

		m_pStatusCom->Add_Status(CStatus::STATUSID::STATUS_HP, -fDamage);
		
		GAMEINSTANCE->PlaySoundW(TEXT("Enemy_Hit.wav"), 0.1f);
		//((CFire_PSystem*)GAMEINSTANCE->Add_GameObject<CFire_PSystem>(CURRENT_LEVEL, TEXT("Particle_Fire"), nullptr, nullptr, true))->AddParticle(50, m_pTransformCom->Get_World_State(CTransform::STATE_POSITION));
		((CFire_PSystem*)GAMEINSTANCE->Get_ParticleSystem<CFire_PSystem>(CURRENT_LEVEL, TEXT("Particle_Fire")))->AddParticle(50, m_pTransformCom);
		if (m_pStatusCom->Get_Status().fHp <= DBL_EPSILON)
		{
	
			
		
			//Set_Dead();
			_float3 vPos = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);

			if (GAMEINSTANCE->IsIn(&vPos))
			{
				GAMEINSTANCE->Add_TimerEvent(1, this, 0.1f);
				GAMEINSTANCE->Set_TimeScale(0.05f);
				GAMEINSTANCE->Add_Shaking(2.7f, 0.01f);
			}
			

			_float3 MyPos = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);
			((CBomb_Effect*)GAMEINSTANCE->Add_GameObject<CBomb_Effect>(CURRENT_LEVEL, TEXT("Explosion"), nullptr, nullptr, false))->Set_Pos(MyPos);

			if(CURRENT_LEVEL == LEVEL::LEVEL_MAGMAPLANET)
				Drop_Item();
			Set_Enable(false);

		}
	}

}

void CMonster::On_Collision_Stay(CCollider* _Other_Collider)
{
}

void CMonster::On_Collision_Exit(CCollider* _Other_Collider)
{
}

void CMonster::OnTimerEvent(const _uint _iEventIndex)
{
	if (1 == _iEventIndex)
	{
		GAMEINSTANCE->Set_TimeScale(1.f);
	}
}

void CMonster::OnEnable(void* _Arg)
{
	//자식들을 순회하면서 Set_Enable 함수를 호출한다.
	function<void(CBase&, _bool, void*)> Set_EnableFunc = &CBase::Set_Enable;
	Command_For_Children<function<void(CBase&, _bool, void*)>, _bool, void*>(Set_EnableFunc, true, _Arg);

	Get_Children_From_Key(TEXT("Targeting")).front()->Set_Enable(false);
	m_pHPBar->Set_Enable(false);

	m_pStatusCom->Set_FULL_HP();
	m_fTime = 3.f;
	m_pTargetingCom->Clear_Targeting();

	//AI 행동 초기화
	m_pAIControllerCom->Push_Front_Command(STATE::STATE_NONE, -1.f, true);
}

void CMonster::OnDisable()
{
	//자식들을 순회하면서 Set_Enable 함수를 호출한다.
	function<void(CBase&, _bool, void*)> Set_EnableFunc = &CBase::Set_Enable;
	Command_For_Children<function<void(CBase&, _bool, void*)>, _bool, void*>(Set_EnableFunc, false, nullptr);

	

}

void CMonster::Free()
{
	__super::Free();
}

#include "stdafx.h"
#include "..\Public\Monster.h"
#include "GameInstance.h"
#include <Math_Utillity.h>
#include "Bomb_Effect.h"
#include "Fire_PSystem.h"
#include "Smoke_PSystem.h"
#include "Normal_Turret.h"
#include <TargetingBox.h>


HRESULT CMonster::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CMonster::Initialize(void* pArg)
{

	GAMEINSTANCE->Add_GameObject<CTargetingBox>(CURRENT_LEVEL,
		TEXT("Targeting"), m_pTransformCom)->Set_Enable(false);

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
	{/*
		int RandomTarget = rand() % 2;

		if (0 == RandomTarget)
		{
			m_pTargetingCom->Make_TargetList_Distance(GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("Player")), m_pTransformCom->Get_State(CTransform::STATE_POSITION, true), 10000.f);
		}

		else
		{
			m_pTargetingCom->Make_TargetList_Distance(GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("AI_Friendly")), m_pTransformCom->Get_State(CTransform::STATE_POSITION, true), 10000.f);
		}*/

		m_pTargetingCom->Add_TargetList_Distance(GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("AI_Friendly")), m_pTransformCom->Get_State(CTransform::STATE_POSITION, true), 10000.f, true);
		m_pTargetingCom->Add_TargetList_Distance(GAMEINSTANCE->Find_Layer(LEVEL_STATIC, TEXT("Player")), m_pTransformCom->Get_State(CTransform::STATE_POSITION, true), 10000.f, false);

		auto TargetList = m_pTargetingCom->Get_Targetting();

		if (!TargetList->empty())
		{
			Update_Target(TargetList->begin()->second);
		}

		m_fTime = 3.f;
	}

	if (m_pStatusCom->Get_Status().fHp < m_pStatusCom->Get_Status().fMaxHp / 2.f)
	{
		((CSmoke_PSystem*)GAMEINSTANCE->Get_ParticleSystem<CSmoke_PSystem>(CURRENT_LEVEL, TEXT("Particle_Smoke")))->AddParticle(1, m_pTransformCom->Get_World_State(CTransform::STATE_POSITION));
	}

	m_pRigidBodyCom->Update_Transform(fTimeDelta);
	_float3 vPos = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);

	if (GAMEINSTANCE->IsIn(&vPos))
		m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_DEFERRED, this);


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

	for (auto& elem : m_pPosinList)
	{
		elem->Set_AI_Target(_Target);
	}

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

	COLLISION_TYPE eCollisionType = COLLISION_TYPE::MONSTER;
	m_pColliderCom = Add_Component<CCollider_Sphere>(&eCollisionType);


	SetUp_Components_For_Child();

	return S_OK;
}




void CMonster::On_Collision_Enter(CCollider* _Other_Collider)
{
	if (_Other_Collider->Get_Collision_Type() == COLLISION_TYPE::PLAYER_ATTACK)
	{
		m_pStatusCom->Add_Status(CStatus::STATUSID::STATUS_HP, -1.f);
		((CFire_PSystem*)GAMEINSTANCE->Add_GameObject<CFire_PSystem>(CURRENT_LEVEL, TEXT("Particle_Fire"), nullptr, nullptr, true))->AddParticle(50, m_pTransformCom->Get_World_State(CTransform::STATE_POSITION));

		if (m_pStatusCom->Get_Status().fHp <= DBL_EPSILON)
		{
			Set_Dead();
			CLevel_RedPlanet::m_iEnemyCount - 1;
			_float3 MyPos = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);
			((CBomb_Effect*)GAMEINSTANCE->Add_GameObject<CBomb_Effect>(CURRENT_LEVEL, TEXT("Bomb"), nullptr, nullptr, false))->Set_Pos(MyPos);

		}
	}
}

void CMonster::On_Collision_Stay(CCollider* _Other_Collider)
{
}

void CMonster::On_Collision_Exit(CCollider* _Other_Collider)
{
}

void CMonster::Free()
{
	__super::Free();
}

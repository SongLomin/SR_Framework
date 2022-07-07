#include "stdafx.h"
#include "..\Public\Monster.h"
#include "GameInstance.h"
#include <Math_Utillity.h>
#include "Bomb_Effect.h"
#include "Fire_PSystem.h"
#include "Smoke_PSystem.h"


HRESULT CMonster::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CMonster::Initialize(void* pArg)
{
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
		m_pTargetingCom->Make_AI_TargetList(GAMEINSTANCE->Find_Layer(LEVEL_STATIC, TEXT("Player")), m_pTransformCom);
		m_fTime = 1.f;
	}

	if (m_pStatusCom->Get_Status().fHp < m_pStatusCom->Get_Status().fMaxHp / 2.f)
	{
		((CSmoke_PSystem*)GAMEINSTANCE->Add_GameObject<CSmoke_PSystem>(CURRENT_LEVEL, TEXT("Particle_Smoke"), nullptr, nullptr, true))->AddParticle(1, m_pTransformCom->Get_World_State(CTransform::STATE_POSITION));
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

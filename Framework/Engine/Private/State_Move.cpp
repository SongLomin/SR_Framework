#include "State_Move.h"
#include "GameInstance.h"
#include "GameObject.h"

CState_Move::CState_Move(const CState_Move& Prototype)
{
	*this = Prototype;
}

HRESULT CState_Move::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CState_Move::Initialize(void* pArg)
{
	return S_OK;

	m_fCurTime = m_fMaxTime;

	m_fTargetCurTime = m_fTargetMaxTime;


}

void CState_Move::Tick(_float fTimeDelta)
{
	switch (m_eCurState)
	{
	case Engine::STATE::MOVE_UPPER_LEFT:
		Move_Upper_Left();
		break;
	case Engine::STATE::MOVE_DOWN_FRONT:
		Move_Down_Front();
		break;
	case Engine::STATE::MOVE_LIFT_FRONT:
		Move_Lift_Front();
		break;
	case Engine::STATE::MOVE_LIFT_BACK:
		Move_Lift_Back();
		break;
	case Engine::STATE::MOVE_JUMP_FRONT:
		Move_Jump_Front();
		break;
	case Engine::STATE::MOVE_UPPER_RIGHT:
		Move_Upper_Right();
		break;
	case Engine::STATE::MOVE_FORWARD:
		Move_Forward();
		break;


	case Engine::STATE::MOVETARGET_CHASE:
		MoveTarget_Chase(fTimeDelta, 10.f);
		break;
	case Engine::STATE::MOVETAGET_CHASE_PLAYER:
		MoveTaget_Chase_Player(fTimeDelta);
		break;
	case Engine::STATE::MOVETARGET_RSPIN:
		MoveTarget_RSpin(fTimeDelta, 10.f);
		break;
	case Engine::STATE::MOVETARGET_LSPIN:
		MoveTarget_LSpin(fTimeDelta, 10.f);
		break;

	case Engine::STATE::MOVEROLLER_RSPIN:
		MoveRoller_RSpin(fTimeDelta, 10.f);
		break;

	case Engine::STATE::MOVEROLLER_LSPIN:
		MoveRoller_LSpin(fTimeDelta, 10.f);
		break;

	case Engine::STATE::MOVETARGET_BACK:
		MoveTarget_Back(fTimeDelta);
		break;
	case Engine::STATE::ATTACK_TAP:
		
		break;

	case Engine::STATE::ATTACK_HOLD:

		break;
	case Engine::STATE::STATE_END:

		break;
	default:
		break;
	}

	

	//스테이트 사용 후에 다시 돌려준다.
	m_eCurState = STATE::STATE_END;

}

void CState_Move::Set_TargetTransform(CTransform* _pTargetTransform)
{
	if (m_pTargetTransform)
	{
		RETURN_WEAKPTR(m_pTargetTransform);
		m_pTargetTransform = nullptr;
	}

	m_pTargetTransform = _pTargetTransform;
	WEAK_PTR(m_pTargetTransform);
}

void CState_Move::Move_Upper_Right()
{
	m_pRigidBody->Add_Dir(CRigid_Body::FRONT);
	m_pRigidBody->Add_Dir(CRigid_Body::RIGHT);
	m_pRigidBody->Add_Dir(CRigid_Body::LIFT);

}


void CState_Move::Move_Upper_Left()
{
	m_pRigidBody->Add_Dir(CRigid_Body::FRONT);
	m_pRigidBody->Add_Dir(CRigid_Body::LEFT);
	m_pRigidBody->Add_Dir(CRigid_Body::LIFT);
}


void CState_Move::Move_Down_Front()
{

	m_pRigidBody->Add_Dir(CRigid_Body::FRONT);
	m_pRigidBody->Add_Dir(CRigid_Body::DOWN);
}


void CState_Move::Move_Lift_Front()
{
	m_pRigidBody->Add_Dir(CRigid_Body::FRONT);
	m_pRigidBody->Add_Dir(CRigid_Body::LIFT);
	m_pRigidBody->Add_Dir(CRigid_Body::DOWN);

}

void CState_Move::Move_Lift_Back()
{
	m_pRigidBody->Add_Dir(CRigid_Body::BACK);
	m_pRigidBody->Add_Dir(CRigid_Body::LIFT);
}

void CState_Move::Move_Jump_Front()
{
	m_pRigidBody->Add_Dir(CRigid_Body::DOWN);
	m_pRigidBody->Add_Dir(CRigid_Body::FRONT);
}


void CState_Move::MoveTaget_Chase_Player(_float fTimeDelta)
{
	if (!m_pTargetTransform)
	{
		return;
	}

	m_pTransform->Go_Target(m_pTargetTransform, fTimeDelta);
	m_pTransform->Go_BackAndForth(50.f, fTimeDelta);
	m_pTransform->Turn_AxisZ(90.f, fTimeDelta);
}



void CState_Move::Move_Forward()
{
	m_pRigidBody->Add_Dir(CRigid_Body::FRONT);
}


// Taget
void CState_Move::MoveTarget_Chase( _float fTimeDelta, _float fLimit)
{
	if (!m_pTargetTransform)
	{
		return;
	}

	m_pTransform->Go_Target(m_pTargetTransform, fTimeDelta);
	m_pTransform->Chase(m_pTargetTransform, fTimeDelta, fLimit);

}


void CState_Move::MoveTarget_LSpin(_float fTimeDelta, _float fLimit)
{
	if (!m_pTargetTransform)
	{
		return;
	}

	
	if (m_pTransform->Chase(m_pTargetTransform, fTimeDelta, 10))
	{
		m_pRigidBody->Add_Dir(CRigid_Body::FRONT);
		m_pRigidBody->Add_Dir(CRigid_Body::LEFT);

		m_pTransform->Go_Target(m_pTargetTransform, fTimeDelta);
	}

	else
	{
		wstring Message = TEXT("Fire");
		Get_Owner()->Broadcast_EventMessage(&Message);
	}

	wstring Message = TEXT("Fire");
	Get_Owner()->Broadcast_EventMessage(&Message);

	/*_float3 vDir = m_pTargetTransform->Get_World_State(CTransform::STATE_POSITION) - m_pTransform->Get_World_State(CTransform::STATE_POSITION);
	_float fDistance = D3DXVec3Length(&vDir);


	if (fDistance < SHOT_RANGE)
	{
		wstring Message = TEXT("Fire");
		Get_Owner()->Broadcast_EventMessage(&Message);
	}*/


	
}

void CState_Move::MoveTarget_RSpin(_float fTimeDelta, _float fLimit)
{
	if (!m_pTargetTransform)
	{
		return;
	}

	if (m_pTransform->Chase(m_pTargetTransform, fTimeDelta, 10))
	{
		m_pRigidBody->Add_Dir(CRigid_Body::FRONT);
		m_pRigidBody->Add_Dir(CRigid_Body::RIGHT);

		m_pTransform->Go_Target(m_pTargetTransform, fTimeDelta);
	}

	else
	{
		wstring Message = TEXT("Fire");
		Get_Owner()->Broadcast_EventMessage(&Message);
	}

	wstring Message = TEXT("Fire");
	Get_Owner()->Broadcast_EventMessage(&Message);

	/*_float3 vDir = m_pTargetTransform->Get_World_State(CTransform::STATE_POSITION) - m_pTransform->Get_World_State(CTransform::STATE_POSITION);
	_float fDistance = D3DXVec3Length(&vDir);


	if (fDistance < SHOT_RANGE)
	{
		wstring Message = TEXT("Fire");
		Get_Owner()->Broadcast_EventMessage(&Message);
	}*/

}

void CState_Move::MoveTarget_Back(_float fTimeDelta)
{
	m_pRigidBody->Add_Dir(CRigid_Body::BACK);
}
void CState_Move::MoveRoller_LSpin(_float fTimeDelta, _float fLimit)
{
	if (!m_pTargetTransform)
	{
		return;
	}

	m_pRigidBody->Add_Dir(CRigid_Body::FRONT);
	m_pRigidBody->Add_Dir(CRigid_Body::LEFT);

	m_pTransform->Go_Target(m_pTargetTransform, fTimeDelta);
	m_pTransform->Chase(m_pTargetTransform, fTimeDelta, 10);


	_float3 vDir = m_pTargetTransform->Get_World_State(CTransform::STATE_POSITION) - m_pTransform->Get_World_State(CTransform::STATE_POSITION);
	_float fDistance = D3DXVec3Length(&vDir);


	if (fDistance < SHOT_RANGE)
	{
		wstring Message = TEXT("Fire");
		Get_Owner()->Broadcast_EventMessage(&Message);
	}

}
void CState_Move::MoveRoller_RSpin(_float fTimeDelta, _float fLimit)
{
	if (!m_pTargetTransform)
	{
		return;
	}

	m_pRigidBody->Add_Dir(CRigid_Body::FRONT);
	m_pRigidBody->Add_Dir(CRigid_Body::RIGHT);

	m_pTransform->Go_Target(m_pTargetTransform, fTimeDelta);
	m_pTransform->Chase(m_pTargetTransform, fTimeDelta, 10);

	_float3 vDir = m_pTargetTransform->Get_World_State(CTransform::STATE_POSITION) - m_pTransform->Get_World_State(CTransform::STATE_POSITION);
	_float fDistance = D3DXVec3Length(&vDir);


	if (fDistance < SHOT_RANGE)
	{
		wstring Message = TEXT("Fire");
		Get_Owner()->Broadcast_EventMessage(&Message);
	}

}

void CState_Move::Set_State(STATE _eState)
{
	if (m_eCurState != _eState)
	{
		m_ePreState = m_eCurState;
		m_eCurState = _eState;
	}
}

CState_Move* CState_Move::Create()
{
	CREATE_PIPELINE(CState_Move);
}

CComponent* CState_Move::Clone(void* pArg)
{
	CLONE_PIPELINE(CState_Move);
}

void CState_Move::Free()
{
	__super::Free();

	RETURN_WEAKPTR(m_pTargetTransform);

	delete this;
}

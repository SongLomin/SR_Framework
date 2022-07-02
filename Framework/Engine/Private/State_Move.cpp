#include "State_Move.h"
#include "GameInstance.h"

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


void CState_Move::Move_Chase_Player(CTransform* pPlayerTransform, _float fTimeDelta)
{
	m_pTransform->Go_Target(pPlayerTransform, fTimeDelta);
	m_pTransform->Go_BackAndForth(8.f, fTimeDelta);
}


// Taget
void CState_Move::MoveTarget_Chase(CTransform* pTargetTransform, _float fTimeDelta, _float fLimit)
{
	m_pTransform->Go_Target(pTargetTransform, fTimeDelta);
	m_pTransform->Chase(pTargetTransform, fTimeDelta, fLimit);
}

void CState_Move::MoveTarget_LSpin(CTransform* pTargetTransform, _float fTimeDelta, _float fLimit)
{
	m_pRigidBody->Add_Dir(CRigid_Body::FRONT);
	m_pRigidBody->Add_Dir(CRigid_Body::LEFT);

	m_pTransform->Go_Target(pTargetTransform, fTimeDelta);
	m_pTransform->Chase(pTargetTransform, fTimeDelta, 10);


}

void CState_Move::MoveTarget_RSpin(CTransform* pTargetTransform, _float fTimeDelta, _float fLimit)
{
	m_pRigidBody->Add_Dir(CRigid_Body::FRONT);
	m_pRigidBody->Add_Dir(CRigid_Body::RIGHT);

	m_pTransform->Go_Target(pTargetTransform, fTimeDelta);
	m_pTransform->Chase(pTargetTransform, fTimeDelta, fLimit);
}

void CState_Move::MoveTarget_Back(_float fTimeDelta)
{
	m_pRigidBody->Add_Dir(CRigid_Body::BACK);
}
//

void CState_Move::State_Tick(CTransform* _Transform, _float fTimeDelta)
{

	m_fCurTime -= fTimeDelta;

	CTransform* pTransform = GAMEINSTANCE->Get_Camera(CURRENT_CAMERA)->Get_Transform();
	
	_float3 MyPos = _Transform->Get_World_State(CTransform::STATE_POSITION);
	_float3 MyDir = _Transform->Get_World_State(CTransform::STATE_LOOK);

	_float3 TargetPos = pTransform->Get_World_State(CTransform::STATE_POSITION);

	_float3 Boundary = TargetPos - MyPos;
	_float3 TargetDir = Boundary;

	D3DXVec3Normalize(&TargetDir, &TargetDir);

	_float BoundaryLength = D3DXVec3Length(&Boundary);

	if (BoundaryLength > m_fDefaultBoundary)
	{
		_float3 vRight;
		_float3 vUp;
		D3DXVec3Cross(&vRight, &_float3(0.f, 1.f, 0.f), &TargetDir);
		D3DXVec3Cross(&vUp, &TargetDir, &vRight);

		m_pRigidBody->Set_Direction(CRigid_Body::STATE_RIGHT, vRight);
		m_pRigidBody->Set_Direction(CRigid_Body::STATE_UP, vUp);
		m_pRigidBody->Set_Direction(CRigid_Body::STATE_LOOK, TargetDir);

		m_pRigidBody->Add_Dir(CRigid_Body::FRONT);

		//m_pRigidBody->Set_Booster(true);
		// 
		//m_pRigidBody->Set_Direction(CRigid_Body::STATE_LOOK, TargetDir);
		//m_pRigidBody->Add_Dir(CRigid_Body::FRONT);
		//m_pRigidBody->Set_Direction(CRigid_Body::STATE_LOOK, MyDir);

	}
	//else
	//{
	//	m_pRigidBody->Set_Booster(false);
	//}


	if (m_fCurTime <= 0.f)
	{
		m_eCurState = (STATE_MOVE)(rand() % (_uint)STATE_MOVE::STATE_END);
		m_bStateCheck = true;

		m_fCurTime = m_fMaxTime;
	}

	if (!m_bStateCheck)
	{
		return;
	}

	switch (m_eCurState)
	{
	case  STATE_MOVE::MOVE_UPPER_LEFT:
		Move_Upper_Left();
		break;

	case  STATE_MOVE::MOVE_DOWN_FRONT:
		Move_Down_Front();
		break;

	case  STATE_MOVE::MOVE_LIFT_FRONT:
		Move_Lift_Front();
		break;

	case  STATE_MOVE::MOVE_LIFT_BACK:
		Move_Lift_Back();
		break;

	case  STATE_MOVE::MOVE_JUMP_FRONT:
		Move_Jump_Front();
		break;

	case  STATE_MOVE::MOVE_UPPER_RIGHT:
		Move_Upper_Right();
		break;
	}

}

void CState_Move::State_Tagetting(CTransform* _TargetTransform, _float fTimeDelta, _float fLimit)
{

	m_fTargetCurTime -= fTimeDelta;

	if (m_fTargetCurTime <= 0.f)
	{
		m_eTargetCurState = (STATE_MOVETARGET)(rand() % (_uint)STATE_MOVETARGET::MOVETARGET_END);
		m_bStateCheck = true;

		m_fTargetCurTime = m_fTargetMaxTime;
	}

	if (!m_bStateCheck)
	{
		return;
	}

	switch (m_eTargetCurState)
	{
	case  STATE_MOVETARGET::MOVETARGET_CHASE:
		MoveTarget_Chase(_TargetTransform, fTimeDelta, fLimit);
		break;

	case  STATE_MOVETARGET::MOVETARGET_LSPIN:
		MoveTarget_LSpin(_TargetTransform, fTimeDelta, fLimit);
		break;

	case  STATE_MOVETARGET::MOVETARGET_RSPIN:
		MoveTarget_RSpin(_TargetTransform, fTimeDelta, fLimit);
		break;

	case STATE_MOVETARGET::MOVETARGET_BACK:
		MoveTarget_Back(fTimeDelta);
		break;
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

	delete this;
}

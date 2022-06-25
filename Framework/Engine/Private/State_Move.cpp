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
}


void CState_Move::Move_Upper_Right(_float fTimeDelta)
{
	m_pRigidBody->Add_Dir(CRigid_Body::FRONT);
	m_pRigidBody->Add_Dir(CRigid_Body::RIGHT);
	m_pRigidBody->Add_Dir(CRigid_Body::JUMP);
	m_pRigidBody->Add_Dir(CRigid_Body::LIFT);
	
}


void CState_Move::Move_Upper_Left(_float fTimeDelta)
{
	m_pRigidBody->Add_Dir(CRigid_Body::FRONT);
	m_pRigidBody->Add_Dir(CRigid_Body::LEFT);
	m_pRigidBody->Add_Dir(CRigid_Body::JUMP);
	m_pRigidBody->Add_Dir(CRigid_Body::LIFT);
}


void CState_Move::Move_Upper_Front(_float fTimeDelta)
{

	m_pRigidBody->Add_Dir(CRigid_Body::FRONT);
	m_pRigidBody->Add_Dir(CRigid_Body::JUMP);
}


void CState_Move::Move_Lift_Front(_float fTimeDelta)
{
	m_pRigidBody->Add_Dir(CRigid_Body::FRONT);
	m_pRigidBody->Add_Dir(CRigid_Body::LIFT);

}

void CState_Move::Move_Lift_Back(_float fTimeDelta)
{
	m_pRigidBody->Add_Dir(CRigid_Body::BACK);
	m_pRigidBody->Add_Dir(CRigid_Body::LIFT);
}

void CState_Move::Move_Jump_Front(_float fTimeDelta)
{
	m_pRigidBody->Add_Dir(CRigid_Body::FRONT);
	m_pRigidBody->Add_Dir(CRigid_Body::JUMP);
}

void CState_Move::Move_Chase_Player(CTransform* pPlayerTransform, _float fTimeDelta)
{
	m_pTransform->Go_Target(pPlayerTransform, fTimeDelta);
	m_pTransform->Go_BackAndForth(8.f, fTimeDelta);
	
}

void CState_Move::State_Change(CTransform* pPlayerTransform, _float fTimeDelta)
{

	m_fCurTime -= fTimeDelta;

	GAMEINSTANCE->Add_Text(_point{ 100, 600 }, TEXT("m_fCurTime : %d"), 1, (int)m_fCurTime);

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
		Move_Upper_Left(fTimeDelta);
		break;

	case  STATE_MOVE::MOVE_UPPER_FRONT:
		Move_Upper_Front(fTimeDelta);
		break;

	case  STATE_MOVE::MOVE_LIFT_FRONT:
		Move_Lift_Front(fTimeDelta);
		break;

	case  STATE_MOVE::MOVE_LIFT_BACK:
		Move_Lift_Back(fTimeDelta);
		break;

	case  STATE_MOVE::MOVE_JUMP_FRONT:
		Move_Jump_Front(fTimeDelta);
		break;

	case STATE_MOVE::MOVE_CHAES_PLAYER:
		Move_Chase_Player(pPlayerTransform, fTimeDelta);

	case  STATE_MOVE::MOVE_UPPER_RIGHT:
		Move_Upper_Right(fTimeDelta);
		break;
	}

}

void CState_Move::Link_RigidBody(CRigid_Body* pRigidBody)
{
	m_pRigidBody = pRigidBody;

	m_pRigidBody->Set_WeakPtr(&m_pRigidBody);
}

void CState_Move::Link_Transform(CTransform* pTransform)
{
	m_pTransform = pTransform;

	m_pTransform->Set_WeakPtr(&m_pTransform);
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

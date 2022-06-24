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
}

void CState_Move::State_Start(_float fTimeDelta)
{
	m_pRigidBody->Add_Dir(CRigid_Body::FRONT);
	m_pRigidBody->Add_Dir(CRigid_Body::JUMP);
	m_pRigidBody->Add_Dir(CRigid_Body::LIFT);
}

void CState_Move::State_1(_float fTimeDelta)
{
	if (m_bStateCheck)
	{
		m_pRigidBody->Add_Dir(CRigid_Body::RIGHT);
		m_pRigidBody->Add_Dir(CRigid_Body::LIFT);
	}

	if (m_fTimeAcc > 3)
	{
		m_bStateCheck = false;
	}
}

void CState_Move::State_2(_float fTimeDelta)
{
	m_fTimeAcc += fTimeDelta;

	if (m_bStateCheck)
	{
		m_pRigidBody->Add_Dir(CRigid_Body::LEFT);
		m_pRigidBody->Add_Dir(CRigid_Body::LIFT);
	}

	if (m_fTimeAcc > 3)
	{
		m_bStateCheck = false;
	}
}

void CState_Move::State_3(_float fTimeDelta)
{
	m_fTimeAcc += fTimeDelta;

	if (m_bStateCheck)
	{
		m_pRigidBody->Add_Dir(CRigid_Body::BACK);
		m_pRigidBody->Add_Dir(CRigid_Body::JUMP);
		m_pRigidBody->Add_Dir(CRigid_Body::LIFT);
	}

	if (m_fTimeAcc > 3)
	{
		m_bStateCheck = false;
	}
}

void CState_Move::State_4(_float fTimeDelta)
{
	m_fTimeAcc += fTimeDelta;

	if (m_bStateCheck)
	{
		m_pRigidBody->Add_Dir(CRigid_Body::LEFT);
		m_pRigidBody->Add_Dir(CRigid_Body::LIFT);
	}

	if (m_fTimeAcc > 3)
	{
		m_bStateCheck = false;
	}
}

void CState_Move::State_5(_float fTimeDelta)
{
	m_fTimeAcc += fTimeDelta;

	if (m_bStateCheck)
	{
		m_pRigidBody->Add_Dir(CRigid_Body::LEFT);
		m_pRigidBody->Add_Dir(CRigid_Body::LIFT);
	}

	if (m_fTimeAcc > 3)
	{
		m_bStateCheck = false;
	}
}

void CState_Move::State_Change(_float fTimeDelta)
{

	m_fTimeAcc += fTimeDelta;

	if (m_fTimeAcc > 8.f);
	{
		_uint iState = rand() % (_uint)STATE_MOVE::STATE_START;
		m_eCurState = (STATE_MOVE)iState;
		m_bStateCheck = true;

		m_fTimeAcc = 0;
	}

	switch (m_eCurState)
	{
	case  STATE_MOVE::STATE_1:
		State_1(fTimeDelta);
		break;
	case  STATE_MOVE::STATE_2:
		State_2(fTimeDelta);
		break;
	case  STATE_MOVE::STATE_3:
		State_3(fTimeDelta);
		break;
	case  STATE_MOVE::STATE_4:
		State_4(fTimeDelta);
		break;
	case  STATE_MOVE::STATE_5:
		State_5(fTimeDelta);
		break;
	}

}

void CState_Move::Link_RigidBody(CRigid_Body* pRigidBody)
{
	m_pRigidBody = pRigidBody;

	m_pRigidBody->Set_WeakPtr(&m_pRigidBody);
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

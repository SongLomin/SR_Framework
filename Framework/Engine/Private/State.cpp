#include "State.h"
#include "GameInstance.h"

CState::CState(const CState& Prototype)
{
	*this = Prototype;
}

HRESULT CState::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CState::Initialize(void* pArg)
{
	return S_OK;
}



void CState::State_1( _float* fCountTime)
{
	m_fCountTime = *fCountTime;


	if (m_bStateCheck)
	{
		m_pRigidBody->Add_Dir(CRigid_Body::Func::FRONT);
		m_pRigidBody->Add_Dir(CRigid_Body::Func::LIFT);
		m_pRigidBody->Add_Dir(CRigid_Body::Func::JUMP);
		m_pRigidBody->Add_Dir(CRigid_Body::Func::LEFT);
	}

	m_fCountTime -= GAMEINSTANCE->Compute_Timer(3);

	if (m_fCountTime < 0.f)
	{
		m_bStateCheck = false;
	}
}

void CState::State_2(_float* fCountTime)
{
	m_fCountTime = *fCountTime;


	if (m_bStateCheck)
	{
		m_pRigidBody->Add_Dir(CRigid_Body::Func::RIGHT);
		m_pRigidBody->Add_Dir(CRigid_Body::Func::FRONT);
		m_pRigidBody->Add_Dir(CRigid_Body::Func::JUMP);
		m_pRigidBody->Add_Dir(CRigid_Body::Func::LIFT);
	}

	m_fCountTime -= GAMEINSTANCE->Compute_Timer(3);

	if (m_fCountTime < 0.f)
	{
		m_bStateCheck = false;
	}
}

void CState::State_3(_float *fCountTime)
{
	m_fCountTime = *fCountTime;

	if (m_bStateCheck)
	{
		m_pRigidBody->Add_Dir(CRigid_Body::Func::LEFT);
		m_pRigidBody->Add_Dir(CRigid_Body::Func::LIFT);

	}

	m_fCountTime -= GAMEINSTANCE->Compute_Timer(3);

	if (m_fCountTime < 0.f)
	{
		m_bStateCheck = false;
	}
}

void CState::State_4(_float* fCountTime)
{
	m_fCountTime = *fCountTime;

	if (m_bStateCheck)
	{
		m_pRigidBody->Add_Dir(CRigid_Body::Func::FRONT);
		m_pRigidBody->Add_Dir(CRigid_Body::Func::LIFT);
	}

	m_fCountTime -= GAMEINSTANCE->Compute_Timer(3);

	if (m_fCountTime < 0.f)
	{
		m_bStateCheck = false;
	}
}

void CState::State_5(_float *fCountTime)
{
	m_fCountTime = *fCountTime;

	if (m_bStateCheck)
	{
		m_pRigidBody->Add_Dir(CRigid_Body::Func::BACK);
		m_pRigidBody->Add_Dir(CRigid_Body::Func::LIFT);
	}

	m_fCountTime -= GAMEINSTANCE->Compute_Timer(3);

	if (m_fCountTime < 0.f)
	{
		m_bStateCheck = false;
	}
}

void CState::State_Change(_float* fCountTime, _bool bStateCheck)
{

 
	m_bStateCheck = bStateCheck;
	m_fCountTime = *fCountTime;

	if (m_fCountTime < 0.f)
	{

		_uint iState = rand() %  (_uint)STATE::STATE_START;
		m_eCurMovement = (STATE)iState;
		m_bStateCheck = true;

		m_fCountTime = 0.5f;

	}

	switch (m_eCurMovement)
	{ 
	case STATE::STATE_1:
		State_1(fCountTime);
		break;
	case STATE::STATE_2:
		State_2(fCountTime);
		break;
	case STATE::STATE_3:
		State_3(fCountTime);
		break;
	case STATE::STATE_4:
		State_4(fCountTime);
		break;
	case STATE::STATE_5:
		State_5(fCountTime);
		break;
	}
}

void CState::Link_RigidBodyCom(CRigid_Body* pRigidBody)
{
	m_pRigidBody = pRigidBody;
	m_pRigidBody->Set_WeakPtr(&m_pRigidBody);
}

void CState::State_Start(_float fSpeedValue)
{
	m_pRigidBody->Add_Dir(CRigid_Body::Func::FRONT);
}

CState* CState::Create()
{
	CREATE_PIPELINE(CState);
}

CComponent* CState::Clone(void* pArg)
{
	CLONE_PIPELINE(CState);
}

void CState::Free()
{
	__super::Free();

	delete this;
}

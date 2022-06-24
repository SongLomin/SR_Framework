#include "stdafx.h"
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

void CState_Move::Tick(_float fTimeDelta)
{
	
}

void CState_Move::LateTick(_float fTimeDelta)
{

}

HRESULT CState_Move::Render()
{
	return S_OK;
}



void CState_Move::State_1(_float* fCountTime)
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

void CState_Move::State_2(_float* fCountTime)
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

void CState_Move::State_3(_float* fCountTime)
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

void CState_Move::State_4(_float* fCountTime)
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

void CState_Move::State_5(_float* fCountTime)
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

void CState_Move::State_Change(_float* fCountTime, _bool bStateCheck)
{


	m_bStateCheck = bStateCheck;
	m_fCountTime = *fCountTime;

	if (m_fCountTime < 0.f)
	{

		_uint iState = rand() % (_uint)STATE_MOVE::STATE_START;
		m_eCurMovement = (STATE_MOVE)iState;
		m_bStateCheck = true;

		m_fCountTime = 0.5f;

	}

	switch (m_eCurMovement)
	{
	case STATE_MOVE::STATE_1:
		State_1(fCountTime);
		break;
	case STATE_MOVE::STATE_2:
		State_2(fCountTime);
		break;
	case STATE_MOVE::STATE_3:
		State_3(fCountTime);
		break;
	case STATE_MOVE::STATE_4:
		State_4(fCountTime);
		break;
	case STATE_MOVE::STATE_5:
		State_5(fCountTime);
		break;
	}
}





void CState_Move::State_Start(_float fSpeedValue)
{
	m_pRigidBody->Add_Dir(CRigid_Body::Func::FRONT);
}


CState* CState_Move::Clone(void* pArg)
{
	CLONE_PIPELINE(CState_Move);
}

void CState_Move::Free()
{
	__super::Free();

	delete this;
}



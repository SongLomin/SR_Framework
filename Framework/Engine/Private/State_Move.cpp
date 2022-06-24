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

void CState_Move::State_Start(_float fTimeDelta)
{
	m_pRigidBody->Add_Dir(CRigid_Body::FRONT);
	m_pRigidBody->Add_Dir(CRigid_Body::JUMP);
	m_pRigidBody->Add_Dir(CRigid_Body::LIFT);
}

//오른쪽 위로 꺾으면서 이동
void CState_Move::State_1(_float fTimeDelta)
{
	m_pRigidBody->Add_Dir(CRigid_Body::RIGHT);
	m_pRigidBody->Add_Dir(CRigid_Body::LIFT);

}

//왼쪽 위로 꺾으면서 이동
void CState_Move::State_2(_float fTimeDelta)
{

	m_pRigidBody->Add_Dir(CRigid_Body::LEFT);
	m_pRigidBody->Add_Dir(CRigid_Body::LIFT);

}


void CState_Move::State_3(_float fTimeDelta)
{

	m_pRigidBody->Add_Dir(CRigid_Body::BACK);
	//m_pRigidBody->Add_Dir(CRigid_Body::JUMP);
	m_pRigidBody->Add_Dir(CRigid_Body::DESCEND);

}

void CState_Move::State_4(_float fTimeDelta)
{
	m_pRigidBody->Add_Dir(CRigid_Body::BACK);
	//m_pRigidBody->Add_Dir(CRigid_Body::LEFT);
	m_pRigidBody->Add_Dir(CRigid_Body::DESCEND);

}

void CState_Move::State_5(_float fTimeDelta)
{
	m_pRigidBody->Add_Dir(CRigid_Body::FRONT);
	//m_pRigidBody->Add_Dir(CRigid_Body::LEFT);
	m_pRigidBody->Add_Dir(CRigid_Body::DESCEND);

}

void CState_Move::State_Change(_float fTimeDelta)
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

	case  STATE_MOVE::STATE_6:
		State_Start(fTimeDelta);
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

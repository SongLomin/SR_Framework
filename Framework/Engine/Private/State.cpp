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



void CState::Link_RigidBody(CRigid_Body* pRigidBody)
{
	m_pRigidBody = pRigidBody;
	m_pRigidBody->Set_WeakPtr((void**)m_pRigidBody);
}

void CState::Link_Transform(CTransform* pTransform)
{
	m_pTransform = pTransform;
	m_pTransform->Set_WeakPtr((void**)m_pTransform);
}



void CState::Free()
{
	__super::Free();
}

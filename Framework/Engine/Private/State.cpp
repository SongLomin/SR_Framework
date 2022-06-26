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

void CState::State_Change(CTransform* pPlayerTransform, _float fTimeDelta)
{
}

void CState::Link_RigidBody(CRigid_Body* pRigidBody)
{
}

void CState::Link_Transform(CTransform* pTransform)
{
}



void CState::Free()
{
	__super::Free();
}

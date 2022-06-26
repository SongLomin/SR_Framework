#include "State_Attack.h"
#include "GameInstance.h"


CState_Attack::CState_Attack(const CState_Attack& Prototype)
{
	*this = Prototype;
}

HRESULT CState_Attack::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CState_Attack::Initialize(void* pArg)
{
	return S_OK;
}

void CState_Attack::Attack_Bullet(_float fTimeDelta)
{
}

void CState_Attack::Attack_Rager(_float fTimeDelta)
{
}

void CState_Attack::Attack_Rest(_float fTimeDelta)
{
}

void CState_Attack::State_Change(CTransform* pPlayerTransform, _float fTimeDelta)
{
}

void CState_Attack::Link_RigidBody(CRigid_Body* pRigidBody)
{
	m_pRigidBody = pRigidBody;

	m_pRigidBody->Set_WeakPtr(&m_pRigidBody);
}

void CState_Attack::Link_Transform(CTransform* pTransform)
{
	m_pTransform = pTransform;

	m_pTransform->Set_WeakPtr(&m_pTransform);
}

CState_Attack* CState_Attack::Create()
{
	CREATE_PIPELINE(CState_Attack);
}

CComponent* CState_Attack::Clone(void* pArg)
{
	CLONE_PIPELINE(CState_Attack);
}

void CState_Attack::Free()
{
	__super::Free();
	
	delete this;
}

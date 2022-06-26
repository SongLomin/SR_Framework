#include "State_Attack.h"
#include "GameInstance.h"
#include "../../Client/Public/EnemySpace_Bullet.h"


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

void CState_Attack::Attack_Bullet(CGameObject* pBullet, _float fTimeDelta)
{
	/*CGameObject* Bullet = GAMEINSTANCE->Add_GameObject<CEnemySpace_Bullet>(CURRENT_LEVEL, TEXT("EnemySpace_Bullet"));
	((CEnemySpace_Bullet*)Bullet)->Link_PosinTransform(m_pTransform);*/
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

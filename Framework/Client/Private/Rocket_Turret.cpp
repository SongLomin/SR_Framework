#include "stdafx.h"
#include "Rocket_Turret.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "Roket_Bullet.h"
#include "Fire_PSystem.h"


CRocket_Turret::CRocket_Turret(const CRocket_Turret& Prototype)
{
	*this = Prototype;
}


HRESULT CRocket_Turret::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	if (pArg)
		m_eBulletCollisionType = *(COLLISION_TYPE*)pArg;

	float floatArray[3];
	floatArray[0] = 0.5f;
	floatArray[1] = 0.2f;
	floatArray[2] = 0.2f;

	SetUp_Variables_For_Child(2.f, _float3(0.6f, 0.6f, 2.f), floatArray);

	return S_OK;
}



void CRocket_Turret::Command_Fire()
{
	CGameObject* Bullet = GAMEINSTANCE->Add_GameObject<CRocket_Bullet>(CURRENT_LEVEL, TEXT("Rocket_Bullet"), nullptr, &m_eBulletCollisionType);
	static_cast<CBullet*>(Bullet)->Init_BulletPosition(&Get_Component<CTransform>()->Get_WorldMatrix());
	static_cast<CRocket_Bullet*>(Bullet)->Set_Target(m_pTarget);
	if (Get_Controller() == CONTROLLER::PLAYER)
	{
		GAMEINSTANCE->Add_Shaking(0.1f, 0.05f);
	}
}

void CRocket_Turret::SetUp_Components_For_Child()
{
}


CRocket_Turret* CRocket_Turret::Create()
{
	CREATE_PIPELINE(CRocket_Turret);
}

CGameObject* CRocket_Turret::Clone(void* pArg)
{
	CLONE_PIPELINE(CRocket_Turret);
}

void CRocket_Turret::Free()
{
	__super::Free();

	delete this;
}
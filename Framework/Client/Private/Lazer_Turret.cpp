#include "stdafx.h"
#include "Lazer_Turret.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "Lazer_Bullet.h"




CLazer_Turret::CLazer_Turret(const CLazer_Turret& Prototype)
{
	*this = Prototype;
	
}

HRESULT CLazer_Turret::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pEventMessage = TEXT("Fire_Lazer");

	if (pArg)
		m_eBulletCollisionType = *(COLLISION_TYPE*)pArg;

	if (Get_Controller() == CONTROLLER::AI)
	{
		
		m_fMaxTime = 0.f;
		m_pEventMessage = TEXT("Fire");
	}
		

	float floatArray[3];
	floatArray[0] = 0.1f;
	floatArray[1] = 0.9f;
	floatArray[2] = 0.9f;

	SetUp_Variables_For_Child(0.0f, _float3(0.4f, 0.4f, 2.f), floatArray);

	
	return S_OK;
}

void CLazer_Turret::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	m_vColor.y += fTimeDelta * 0.9f;
	if (m_vColor.y > 1.f)
		m_vColor.y = 1.f;

	if (Get_Controller() == CONTROLLER::AI)
	{

		m_fMaxTime = 0.f;
		m_pEventMessage = TEXT("Fire");
	}

	else
	{
		m_pEventMessage = TEXT("Fire_Lazer");
	}

}

void CLazer_Turret::Command_Fire()
{
	CGameObject* Bullet = GAMEINSTANCE->Add_GameObject<CLazer_Bullet>(CURRENT_LEVEL, TEXT("Lazer_Bullet"), nullptr, &m_eBulletCollisionType, true);
	static_cast<CBullet*>(Bullet)->Init_BulletPosition(&Get_Component<CTransform>()->Get_WorldMatrix());
	//GAMEINSTANCE->PlaySoundW(TEXT("Laser.wav"), 1.f);
	m_vColor.y -= TIMEDELTA;
	static_cast<CLazer_Bullet*>(Bullet)->Get_Color(m_vColor);
}

void CLazer_Turret::SetUp_Components_For_Child()
{
}

CLazer_Turret* CLazer_Turret::Create()
{
	CREATE_PIPELINE(CLazer_Turret);
}

CGameObject* CLazer_Turret::Clone(void* pArg)
{
	CLONE_PIPELINE(CLazer_Turret);
}

void CLazer_Turret::Free()
{
	__super::Free();

	delete this;
}
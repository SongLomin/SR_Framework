#include "stdafx.h"
#include "Level_ExoPlanet.h"
#include "GameInstance.h"
#include "LEvel_Loading.h"
#include "Song_Ship_Body.h"
#include "Monster.h"
#include "Terrain.h"
#include "Cam_Free.h"
#include "Cam_FPS.h"
#include "Cam_Shoulder.h"
#include "Cam_TPS.h"
#include <UITest.h>
#include <SkyBox.h>
#include "Default_Aim.h"
#include <TargetingBox.h>
#include <UITest.h>
#include <SkyBox.h>
#include "../Default/EnemySpace_Body.h"
#include "StatusBar.h"
#include "HpBar.h"
#include "BoosterBar.h"
#include "ShieldBar.h"
#include "BulletUI.h"
#include "BulletCountUI.h"
#include "AI_Friendly.h"
#include "MovingCamera.h"
#include "../Default/EnemySpace_Body.h"
#include "Kang_Ship_Body.h"
#include "Planet_Venus.h"
#include "Math_Utillity.h"
#include "Light_Moon.h"
#include "Quest.h"
#include <SelectPlanet_SkyBox.h>
#include "ExoPlanet_SkyBox.h"
#include "Rock_1.h"
#include "Rock_2.h"
#include "Rock_3.h"
#include "Rock_4.h"
#include "Enemy_Scourge.h"

CLevel_ExoPlanet::CLevel_ExoPlanet()
{

}

HRESULT CLevel_ExoPlanet::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;



	
	if (!GAMEINSTANCE->Add_GameObject<CExoPlanet_SkyBox>(LEVLE_EXOPLANET, TEXT("SkyBox")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CDefault_Aim>(LEVLE_EXOPLANET, TEXT("Aim_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CLight_Moon>(LEVLE_EXOPLANET , TEXT("Light_Moon")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CStatusBar>(LEVLE_EXOPLANET, TEXT("Status_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CHpBar>(LEVLE_EXOPLANET, TEXT("HP_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBoosterBar>(LEVLE_EXOPLANET, TEXT("Booster_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CShieldBar>(LEVLE_EXOPLANET, TEXT("Shield_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletUI>(LEVLE_EXOPLANET, TEXT("NormalBullet_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletCountUI>(LEVLE_EXOPLANET, TEXT("BulletCount_UI")))
		return E_FAIL;

	for (int i = 0; i < 1000; ++i)
	{
		if (!GAMEINSTANCE->Add_GameObject<CRock_1>(LEVLE_EXOPLANET, TEXT("Rock_1")))
			return E_FAIL;

		if (!GAMEINSTANCE->Add_GameObject<CRock_2>(LEVLE_EXOPLANET, TEXT("Rock_2")))
			return E_FAIL;

		if (!GAMEINSTANCE->Add_GameObject<CRock_3>(LEVLE_EXOPLANET, TEXT("Rock_3")))
			return E_FAIL;

		if (!GAMEINSTANCE->Add_GameObject<CRock_4>(LEVLE_EXOPLANET, TEXT("Rock_4")))
			return E_FAIL;
	}

	return S_OK;
}

void CLevel_ExoPlanet::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);		


	m_fSpawnTime -= fTimeDelta;

	if (m_fSpawnTime < 0.f)
	{

		CTransform* pEnemyTransform = GAMEINSTANCE->Add_GameObject<CEnemy_Scourge>(CURRENT_LEVEL, TEXT("Enemy_Scourge"), nullptr, nullptr, true)
			->Get_Component<CTransform>();
		_float3 SpawnPos{ 0, 0.f, 300.f };

		_float RotateX = (_float)(rand() % 361);
		_float RotateY = (_float)(rand() % 361);
		_float RotateZ = (_float)(rand() % 361);
		RotateX = D3DXToRadian(RotateX);
		RotateY = D3DXToRadian(RotateY);
		RotateZ = D3DXToRadian(RotateZ);

		SpawnPos = CMath_Utillity::Rotate_Vec3(_float3(RotateX, RotateY, RotateZ), SpawnPos);
		pEnemyTransform->Set_State(CTransform::STATE_POSITION, SpawnPos);

		m_fSpawnTime = 3.f;
	}
	
}

HRESULT CLevel_ExoPlanet::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;


	SetWindowText(g_hWnd, TEXT("Exo Planet 레벨입니다. "));



	return S_OK;
}

CLevel_ExoPlanet* CLevel_ExoPlanet::Create()
{
	CLevel_ExoPlanet* pInstance = new CLevel_ExoPlanet();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_ExoPlanet");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_ExoPlanet::Free()
{
	__super::Free();

	delete this;
}




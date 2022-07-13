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
#include "TextBox.h"
#include "Quest.h"
#include "Planet_Select.h"
#include "Satellite_1.h"
#include "Satellite_2.h"
#include "Satellite_3.h"

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

	m_pTextBoxObject = GAMEINSTANCE->Add_GameObject<CTextBox>(LEVLE_EXOPLANET, TEXT("TextBox_Yang"));
	m_pTextBoxObject->Set_Enable(false);

	m_pQuestBoxObject = GAMEINSTANCE->Add_GameObject<CQuest>(LEVLE_EXOPLANET, TEXT("Quest_UI"));
	m_pQuestBoxObject->Set_Enable(false);


	m_pPlanetObject = GAMEINSTANCE->Add_GameObject<CPlanet_Select>(LEVLE_EXOPLANET, TEXT("Earth"));
	m_pPlanetObject->Set_Enable(false);

	for (int i = 0; i < 500; ++i)
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


	for (int i = 0; i < 2; ++i)
	{

		if (!GAMEINSTANCE->Add_GameObject<CSatellite_1>(LEVLE_EXOPLANET, TEXT("Satellite_1")))
			return E_FAIL;

		if (!GAMEINSTANCE->Add_GameObject<CSatellite_2>(LEVLE_EXOPLANET, TEXT("Satellite_2")))
			return E_FAIL;
	}


	if (!GAMEINSTANCE->Add_GameObject<CSatellite_3>(LEVLE_EXOPLANET, TEXT("Satellite_3")))
		return E_FAIL;

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

		m_fSpawnTime = 2.f;
	}
	
	ExoPlanet_Event(fTimeDelta);
}

HRESULT CLevel_ExoPlanet::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;


	SetWindowText(g_hWnd, TEXT("Exo Planet 레벨입니다. "));



	return S_OK;
}

void CLevel_ExoPlanet::ExoPlanet_Event(float fTimeDelta)
{
	m_fTextBoxTime -= fTimeDelta;


	if (m_fTextBoxTime <= 298.f && !m_bEventCheck[0])
	{
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("이번 임무는 적군 행성 우주 정거장을 해킹해야하네."), 0);
	}

	if (m_fTextBoxTime <= 296.f && !m_bEventCheck[0])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[0] = true;
	}

	if (m_fTextBoxTime <= 294.f && !m_bEventCheck[1])
	{
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("이 행성은 우주 쓰레기와 운석 파편이 아주 많다고 들었네\n조심히 들키지 않게 빠르게 우주 정거장을 해킹해주게."), 0);
	}

	if (m_fTextBoxTime <= 292.f && !m_bEventCheck[1])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[1] = true;
	}

	if (m_fTextBoxTime <= 290.f && !m_bEventCheck[2])
	{
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("이런! 벌써 들킨것같군\n내가 최대한 적들을 유인할태니 서둘러주게! "), 0);
	}

	if (m_fTextBoxTime <= 288.f && !m_bEventCheck[2])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[2] = true;
	}

	if (m_fTextBoxTime <= 290.f && !m_bEventCheck[3])
	{
		m_pQuestBoxObject->Set_Enable(true);

		GAMEINSTANCE->Add_Text(_point{ (LONG)m_iFontiX, (LONG)50 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("            현재 임무\n      우주 정거장 해킹  \n     남은시간 (초) :"), 0);
		GAMEINSTANCE->Add_Text(_point{ (LONG)m_iFontiXCount, (LONG)68 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("\n  %d"), 1, (_uint)m_fMaxTime);

		if (m_iFontiX <= 1040)
		{
			m_iFontiX = 1040;
		}

		if (m_iFontiXCount <= 1150)
		{
			m_iFontiXCount = 1150;
		}

		m_iFontiX -= 0.8;
		m_iFontiXCount -= 0.8;
		m_fMaxTime -= fTimeDelta;
	}

	if (m_fTextBoxTime <= 280.f && !m_bEventCheck[4])
	{
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("이런 미친자식들! 자살특공대인가 카미카제를 하다니.."), 0);
	}

	if (m_fTextBoxTime <= 277.f && !m_bEventCheck[4])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[4] = true;
	}

	if (m_fTextBoxTime <= 274.f && !m_bEventCheck[5])
	{
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("좋지않아! 안그래도 운석 파편떄문에\n움직이는대 제약이있는데\n저 자살특공대 까지 신경을 써야하다니!"), 0);
	}

	if (m_fTextBoxTime <= 271.f && !m_bEventCheck[5])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[5] = true;
	}

	if (m_fTextBoxTime <= 268 && !m_bEventCheck[6])
	{
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("하지만 나 대위 양갑렬 절대 굴하지않는다!"), 0);
	}

	if (m_fTextBoxTime <= 265 && !m_bEventCheck[6])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[6] = true;
	}


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




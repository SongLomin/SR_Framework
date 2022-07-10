#include "stdafx.h"
#include "Level_VenusPlanet.h"
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
#include "Rock.h"
#include "../Default/EnemySpace_Body.h"
#include "StatusBar.h"
#include "HpBar.h"
#include "BoosterBar.h"
#include "ShieldBar.h"
#include "BulletUI.h"
#include "BulletCountUI.h"
#include "AI_Friendly.h"
#include "Rock.h"
#include "MovingCamera.h"
#include "../Default/EnemySpace_Body.h"
#include "Kang_Ship_Body.h"
#include "Planet_Venus.h"
#include "Math_Utillity.h"
#include "Light_Moon.h"
#include <SelectPlanet_SkyBox.h>
#include "TextBox.h"
#include "Quest.h"

CLevel_VenusPlanet::CLevel_VenusPlanet()
{

}

HRESULT CLevel_VenusPlanet::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;




	if (!GAMEINSTANCE->Add_GameObject<CSelectPlanet_SkyBox>(LEVEL_SELECTPLANET, TEXT("SkyBox")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CDefault_Aim>(LEVEL_VENUSPLANET, TEXT("Aim")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CLight_Moon>(LEVEL_VENUSPLANET, TEXT("Light_Moon")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CStatusBar>(LEVEL_VENUSPLANET, TEXT("Status")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CHpBar>(LEVEL_VENUSPLANET, TEXT("HP")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBoosterBar>(LEVEL_VENUSPLANET, TEXT("Booster")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CShieldBar>(LEVEL_VENUSPLANET, TEXT("Shield")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletUI>(LEVEL_VENUSPLANET, TEXT("NormalBullet")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletCountUI>(LEVEL_VENUSPLANET, TEXT("CBulletCountUI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CDefault_Aim>(LEVEL_REDPLANET, TEXT("Aim")))
		return E_FAIL;

	m_pTextBoxObject = GAMEINSTANCE->Add_GameObject<CTextBox>(LEVEL_REDPLANET, TEXT("TextBox_Yang"));
	m_pTextBoxObject->Set_Enable(false);

	m_pQuestBoxObject = GAMEINSTANCE->Add_GameObject<CQuest>(LEVEL_REDPLANET, TEXT("Quest"));
	m_pQuestBoxObject->Set_Enable(false);


	//if (!GAMEINSTANCE->Add_GameObject<CTargetingBox>(LEVEL_GAMEPLAY, TEXT("Targeting")))
	//	return E_FAIL;


	return S_OK;
}

void CLevel_VenusPlanet::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);		

	VenusPlanet_Event(fTimeDelta);
}

HRESULT CLevel_VenusPlanet::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;


	SetWindowText(g_hWnd, TEXT("Venus Planet 레벨입니다. "));

	return S_OK;
}

void CLevel_VenusPlanet::VenusPlanet_Event(_float fTimeDelta)
{
	m_fTextBoxTime -= fTimeDelta;


	if (m_fTextBoxTime <= 298.f && !m_bEventCheck[0])
	{
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("자네가 요번에 들어온 신입 파일럿인가? \n 어리버리 하게 생긴게 마음에 안들군. "), 0);
	}

	if (m_fTextBoxTime <= 295.f && !m_bEventCheck[0])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[0] = true;
	}

	if (m_fTextBoxTime <= 292.f && !m_bEventCheck[1])
	{
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("이동키와 마우스를 이용해 \n 앞에보이는 체크포인트까지 이동해봐."), 0);
	}

	if (!m_bEventCheck[1])
	{

	}
	 

}

CLevel_VenusPlanet* CLevel_VenusPlanet::Create()
{
	CLevel_VenusPlanet*		pInstance = new CLevel_VenusPlanet();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_RedPlanet");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_VenusPlanet::Free()
{
	__super::Free();

	delete this;
}




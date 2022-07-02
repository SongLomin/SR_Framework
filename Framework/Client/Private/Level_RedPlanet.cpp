#include "stdafx.h"
#include "Level_RedPlanet.h"
#include "GameInstance.h"
#include "LEvel_Loading.h"
#include "Player_Body.h"
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
#include <Test_Player.h>
#include "Planet_Venus.h"
#include "Math_Utillity.h"
#include "Light_Moon.h"

CLevel_RedPlanet::CLevel_RedPlanet()
{

}

HRESULT CLevel_RedPlanet::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;



	CGameObject* FPS_Cam = GAMEINSTANCE->Add_GameObject<CCam_FPS>(CURRENT_LEVEL, TEXT("Camera"));
	FPS_Cam->Get_Component<CCamera>()->Set_Param(D3DXToRadian(65.0f), (_float)g_iWinCX / g_iWinCY, 0.2f, 300.f);
	GAMEINSTANCE->Register_Camera(TEXT("FPS"), FPS_Cam->Get_Component<CCamera>());

	CGameObject* Shoulder_Cam = GAMEINSTANCE->Add_GameObject<CCam_Shoulder>(CURRENT_LEVEL, TEXT("Camera"));
	Shoulder_Cam->Get_Component<CCamera>()->Set_Param(D3DXToRadian(65.0f), (_float)g_iWinCX / g_iWinCY, 0.2f, 300.f);
	GAMEINSTANCE->Register_Camera(TEXT("Shoulder"), Shoulder_Cam->Get_Component<CCamera>());

	CGameObject* TPS_Cam = GAMEINSTANCE->Add_GameObject<CCam_TPS>(CURRENT_LEVEL, TEXT("Camera"));
	TPS_Cam->Get_Component<CCamera>()->Set_Param(D3DXToRadian(65.0f), (_float)g_iWinCX / g_iWinCY, 0.2f, 300.f);
	GAMEINSTANCE->Register_Camera(TEXT("TPS"), TPS_Cam->Get_Component<CCamera>());

	CGameObject* Moving_Cam = GAMEINSTANCE->Add_GameObject<CMovingCamera>(CURRENT_LEVEL, TEXT("Camera"));
	Moving_Cam->Get_Component<CCamera>()->Set_Param(D3DXToRadian(65.0f), (_float)g_iWinCX / g_iWinCY, 0.2f, 300.f);
	GAMEINSTANCE->Register_Camera(TEXT("Moving"), Moving_Cam->Get_Component<CCamera>());

	if (!GAMEINSTANCE->Add_GameObject<CPlayer_Body>(LEVEL_REDPLANET, TEXT("Player_Body")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CTest_Player>(LEVEL_REDPLANET, TEXT("Test_Player")))
		return E_FAIL;

	for (int i = 0; i < 50; ++i)
	{
		if (!GAMEINSTANCE->Add_GameObject<CEnemySpace_Body>(LEVEL_REDPLANET, TEXT("EnemySpace_Body")))
			return E_FAIL;
	}

	for (int i = 0; i < 50; ++i)
	{
		if (!GAMEINSTANCE->Add_GameObject<CAI_Friendly>(LEVEL_REDPLANET, TEXT("AI_Friendly")))
			return E_FAIL;
	}


	/*for (int i = 0; i < 5; i++)
	{
		GAMEINSTANCE->Add_GameObject<CMonster>(LEVEL_GAMEPLAY, TEXT("Monster"))
			->Get_Component<CTransform>()->Set_State(CTransform::STATE_POSITION, _float3(i * 5.f, 0.f, 0.f));
	}*/

	if (!GAMEINSTANCE->Add_GameObject<CTerrain>(LEVEL_REDPLANET, TEXT("Terrain")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CSkyBox>(LEVEL_REDPLANET, TEXT("SkyBox")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CDefault_Aim>(LEVEL_REDPLANET, TEXT("Aim")))
		return E_FAIL;

	for (int i = 0; i < 30; ++i)
	{
		if (!GAMEINSTANCE->Add_GameObject<CRock>(LEVEL_REDPLANET, TEXT("Rock")))
			return E_FAIL;
	}

	if (!GAMEINSTANCE->Add_GameObject<CLight_Moon>(LEVEL_REDPLANET, TEXT("Light_Moon")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CStatusBar>(LEVEL_REDPLANET, TEXT("Status")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CHpBar>(LEVEL_REDPLANET, TEXT("HP")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBoosterBar>(LEVEL_REDPLANET, TEXT("Booster")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CShieldBar>(LEVEL_REDPLANET, TEXT("Shield")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletUI>(LEVEL_REDPLANET, TEXT("NormalBullet")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletCountUI>(LEVEL_REDPLANET, TEXT("CBulletCountUI")))
		return E_FAIL;



	//if (!GAMEINSTANCE->Add_GameObject<CTargetingBox>(LEVEL_GAMEPLAY, TEXT("Targeting")))
	//	return E_FAIL;

	


	/*TEXTINFO Info;
	Info.color = D3DCOLOR_ARGB(255, 0, 255, 0);
	Info.rcTemp = { 600, 300, 600 + 200, 300 + 300 };
	wsprintf(Info.szBuff, L"10초동안 출력");
	if (FAILED(GAMEINSTANCE->Add_Text(&Info, 10.f)))
		return E_FAIL;*/

	return S_OK;
}

void CLevel_RedPlanet::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);		


	// 1

	/*if (KEY_INPUT(KEY::F1, KEY_STATE::TAP))
	{
		if (FAILED(GAMEINSTANCE->Register_OpenLevelEvent(LEVEL_LOADING, CLevel_Loading::Create(LEVEL_SELECTPLANET))))
			return;
	}*/



	if (KEY_INPUT(KEY::F1, KEY_STATE::TAP))
	{
		if (FAILED(GAMEINSTANCE->Get_Instance()->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(LEVEL_SELECTPLANET))))
			return;
	}

	// 2
	


	// 3
	 
	
}

HRESULT CLevel_RedPlanet::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;


	SetWindowText(g_hWnd, TEXT("Red Planet 레벨입니다. "));

	return S_OK;
}

CLevel_RedPlanet * CLevel_RedPlanet::Create()
{
	CLevel_RedPlanet*		pInstance = new CLevel_RedPlanet();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_RedPlanet");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_RedPlanet::Free()
{
	__super::Free();

	delete this;
}

void CLevel_RedPlanet::Ai_Create(_float TimeDelta)
{
	
}


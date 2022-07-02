#include "stdafx.h"
#include "Level_SelectPlanet.h"
#include "GameInstance.h"
#include "Level_Loading.h"
#include "Cam_FPS.h"
#include "Cam_Shoulder.h"
#include "Cam_TPS.h"
#include "MovingCamera.h"
#include "Player_Body.h"
#include "SelectPlanet_SkyBox.h"
#include "Default_Aim.h"
#include "BoosterBar.h"
#include "StatusBar.h"
#include "HpBar.h"
#include "ShieldBar.h"
#include "BulletUI.h"
#include "BulletCountUI.h"
#include "Planet_Venus.h"
#include "Planet_Sun.h"
#include "Planet_Red.h"

CLevel_SelectPlanet::CLevel_SelectPlanet()
{
}

HRESULT CLevel_SelectPlanet::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;

	

	CGameObject* FPS_Cam = GAMEINSTANCE->Add_GameObject<CCam_FPS>(CURRENT_LEVEL, TEXT("Camera"));
	FPS_Cam->Get_Component<CCamera>()->Set_Param(D3DXToRadian(65.0f), (_float)g_iWinCX / g_iWinCY, 0.2f, 900.f);
	GAMEINSTANCE->Register_Camera(TEXT("FPS"), FPS_Cam->Get_Component<CCamera>());

	CGameObject* Shoulder_Cam = GAMEINSTANCE->Add_GameObject<CCam_Shoulder>(CURRENT_LEVEL, TEXT("Camera"));
	Shoulder_Cam->Get_Component<CCamera>()->Set_Param(D3DXToRadian(65.0f), (_float)g_iWinCX / g_iWinCY, 0.2f, 900.f);
	GAMEINSTANCE->Register_Camera(TEXT("Shoulder"), Shoulder_Cam->Get_Component<CCamera>());

	CGameObject* TPS_Cam = GAMEINSTANCE->Add_GameObject<CCam_TPS>(CURRENT_LEVEL, TEXT("Camera"));
	TPS_Cam->Get_Component<CCamera>()->Set_Param(D3DXToRadian(65.0f), (_float)g_iWinCX / g_iWinCY, 0.2f, 900.f);
	GAMEINSTANCE->Register_Camera(TEXT("TPS"), TPS_Cam->Get_Component<CCamera>());

	CGameObject* Moving_Cam = GAMEINSTANCE->Add_GameObject<CMovingCamera>(CURRENT_LEVEL, TEXT("Camera"));
	Moving_Cam->Get_Component<CCamera>()->Set_Param(D3DXToRadian(65.0f), (_float)g_iWinCX / g_iWinCY, 0.2f, 900.f);
	GAMEINSTANCE->Register_Camera(TEXT("Moving"), Moving_Cam->Get_Component<CCamera>());

	if (!GAMEINSTANCE->Add_GameObject<CPlayer_Body>(LEVEL_SELECTPLANET, TEXT("Player_Body")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CSelectPlanet_SkyBox>(LEVEL_SELECTPLANET, TEXT("SkyBox")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CPlanet_Venus>(LEVEL_SELECTPLANET, TEXT("Venus")))
		return E_FAIL;

	/*if (!GAMEINSTANCE->Add_GameObject<CDefault_Aim>(LEVEL_SELECTPLANET, TEXT("Aim")))
		return E_FAIL;*/

	if (!GAMEINSTANCE->Add_GameObject<CStatusBar>(LEVEL_SELECTPLANET, TEXT("Status")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CHpBar>(LEVEL_SELECTPLANET, TEXT("HP")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBoosterBar>(LEVEL_SELECTPLANET, TEXT("Booster")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CShieldBar>(LEVEL_SELECTPLANET, TEXT("Shield")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletUI>(LEVEL_SELECTPLANET, TEXT("NormalBullet")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletCountUI>(LEVEL_SELECTPLANET, TEXT("CBulletCountUI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CPlanet_Sun>(LEVEL_SELECTPLANET, TEXT("Sun")))
		return E_FAIL;
	
	if (!GAMEINSTANCE->Add_GameObject<CPlanet_Red>(LEVEL_SELECTPLANET, TEXT("Red")))
		return E_FAIL;

	return S_OK;
}

void CLevel_SelectPlanet::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	

	// Planet_Venus



	// Planet_ ~



	// Planet_ ~


	// 


	//
	

}

HRESULT CLevel_SelectPlanet::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;


	SetWindowText(g_hWnd, TEXT("행성 선택 레벨입니다. "));

	return S_OK;
}

CLevel_SelectPlanet* CLevel_SelectPlanet::Create()
{
	CLevel_SelectPlanet* pInstance = new CLevel_SelectPlanet();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_SelectPlanet");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_SelectPlanet::Free()
{
	__super::Free();

	delete this;
}

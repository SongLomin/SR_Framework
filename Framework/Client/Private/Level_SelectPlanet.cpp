#include "stdafx.h"
#include "Level_SelectPlanet.h"
#include "GameInstance.h"
#include "Level_Loading.h"
#include "Cam_FPS.h"
#include "Cam_Shoulder.h"
#include "Cam_TPS.h"
#include "MovingCamera.h"
#include "Player_Body.h"
#include "SkyBox.h"

CLevel_SelectPlanet::CLevel_SelectPlanet()
{
}

HRESULT CLevel_SelectPlanet::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;

	/*if (!GAMEINSTANCE->Add_GameObject<CLevel_SelectPlanet>(LEVEL_SELECTPLANET, TEXT("SelectPlanet")))
		return E_FAIL;*/

	CGameObject* FPS_Cam = GAMEINSTANCE->Add_GameObject<CCam_FPS>(CURRENT_LEVEL, TEXT("Camera"));
	FPS_Cam->Get_Component<CCamera>()->Set_Param(D3DXToRadian(65.0f), (_float)g_iWinCX / g_iWinCY, 0.2f, 300.f);
	GAMEINSTANCE->Register_Camera(TEXT("FPS"), FPS_Cam->Get_Component<CCamera>());

	CGameObject* Shoulder_Cam = GAMEINSTANCE->Add_GameObject<CCam_Shoulder>(CURRENT_LEVEL, TEXT("Camera"));
	Shoulder_Cam->Get_Component<CCamera>()->Set_Param(D3DXToRadian(65.0f), (_float)g_iWinCX / g_iWinCY, 0.2f, 300.f);
	GAMEINSTANCE->Register_Camera(TEXT("Shoulder"), Shoulder_Cam->Get_Component<CCamera>());

	CGameObject* TPS_Cam = GAMEINSTANCE->Add_GameObject<CCam_TPS>(CURRENT_LEVEL, TEXT("Camera"));
	TPS_Cam->Get_Component<CCamera>()->Set_Param(D3DXToRadian(65.0f), (_float)g_iWinCX / g_iWinCY, 0.2f, 300.f);
	GAMEINSTANCE->Register_Camera(TEXT("TPS"), TPS_Cam->Get_Component<CCamera>());

	CGameObject* Moving_Cam = GAMEINSTANCE->Add_GameObject<CMovingCamera>(LEVEL_STATIC, TEXT("Camera"));
	Moving_Cam->Get_Component<CCamera>()->Set_Param(D3DXToRadian(65.0f), (_float)g_iWinCX / g_iWinCY, 0.2f, 300.f);
	GAMEINSTANCE->Register_Camera(TEXT("Moving"), Moving_Cam->Get_Component<CCamera>());

	if (!GAMEINSTANCE->Add_GameObject<CPlayer_Body>(LEVEL_GAMEPLAY, TEXT("Player_Body")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CSkyBox>(LEVEL_GAMEPLAY, TEXT("SkyBox")))
		return E_FAIL;

	return S_OK;
}

void CLevel_SelectPlanet::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
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

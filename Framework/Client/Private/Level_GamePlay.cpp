#include "stdafx.h"
#include "..\Public\Level_GamePlay.h"
#include "GameInstance.h"
#include "LEvel_Loading.h"
#include "BackGround.h"
#include "Monster.h"
#include "Terrain.h"
#include "Cam_Free.h"
#include "Cam_FPS.h"
#include "Cam_Shoulder.h"
#include "Cam_TPS.h"

CLevel_GamePlay::CLevel_GamePlay()
{

}

HRESULT CLevel_GamePlay::Initialize()
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


	if (!GAMEINSTANCE->Add_GameObject<CBackGround>(LEVEL_GAMEPLAY, TEXT("Background")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CMonster>(LEVEL_GAMEPLAY, TEXT("Monster")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CTerrain>(LEVEL_GAMEPLAY, TEXT("Terrain")))
		return E_FAIL;


	/*TEXTINFO Info;
	Info.color = D3DCOLOR_ARGB(255, 0, 255, 0);
	Info.rcTemp = { 600, 300, 600 + 200, 300 + 300 };
	wsprintf(Info.szBuff, L"10초동안 출력");
	if (FAILED(GAMEINSTANCE->Add_Text(&Info, 10.f)))
		return E_FAIL;*/

	return S_OK;
}

void CLevel_GamePlay::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);		
}

HRESULT CLevel_GamePlay::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;


	SetWindowText(g_hWnd, TEXT("게임프렐이레벨임. "));

	return S_OK;
}

CLevel_GamePlay * CLevel_GamePlay::Create()
{
	CLevel_GamePlay*		pInstance = new CLevel_GamePlay();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_GamePlay");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_GamePlay::Free()
{
	__super::Free();

	delete this;
}


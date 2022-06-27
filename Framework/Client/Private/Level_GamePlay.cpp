#include "stdafx.h"
#include "..\Public\Level_GamePlay.h"
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


	if (!GAMEINSTANCE->Add_GameObject<CPlayer_Body>(LEVEL_GAMEPLAY, TEXT("Player_Body")))
		return E_FAIL;

	//for (int i = 0; i < 30; ++i)
	//{
		if (!GAMEINSTANCE->Add_GameObject<CEnemySpace_Body>(LEVEL_GAMEPLAY, TEXT("EnemySpace_Body")))
			return E_FAIL;
	//}


	for (int i = 0; i < 5; i++)
	{
		GAMEINSTANCE->Add_GameObject<CMonster>(LEVEL_GAMEPLAY, TEXT("Monster"))
			->Get_Component<CTransform>()->Set_State(CTransform::STATE_POSITION, _float3(i * 5.f, 0.f, 0.f));
	}

	if (!GAMEINSTANCE->Add_GameObject<CTerrain>(LEVEL_GAMEPLAY, TEXT("Terrain")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CSkyBox>(LEVEL_GAMEPLAY, TEXT("SkyBox")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CDefault_Aim>(LEVEL_GAMEPLAY, TEXT("Aim")))
		return E_FAIL;

	for (int i = 0; i < 30; ++i)
	{
		if (!GAMEINSTANCE->Add_GameObject<CRock>(LEVEL_GAMEPLAY, TEXT("Rock")))
			return E_FAIL;
	}


	if (!GAMEINSTANCE->Add_GameObject<CStatusBar>(LEVEL_GAMEPLAY, TEXT("Status")))
		return E_FAIL;

	//if (!GAMEINSTANCE->Add_GameObject<CTargetingBox>(LEVEL_GAMEPLAY, TEXT("Targeting")))
	//	return E_FAIL;

	


	/*TEXTINFO Info;
	Info.color = D3DCOLOR_ARGB(255, 0, 255, 0);
	Info.rcTemp = { 600, 300, 600 + 200, 300 + 300 };
	wsprintf(Info.szBuff, L"10�ʵ��� ���");
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


	SetWindowText(g_hWnd, TEXT("���� �÷��� �����Դϴ�. "));

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


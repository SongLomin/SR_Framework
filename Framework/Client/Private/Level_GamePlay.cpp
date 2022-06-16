#include "stdafx.h"
#include "..\Public\Level_GamePlay.h"
#include "GameInstance.h"
#include "LEvel_Loading.h"
#include "BackGround.h"
#include "Monster.h"
#include "Terrain.h"
#include "Cam_Free.h"

CLevel_GamePlay::CLevel_GamePlay()
{

}

HRESULT CLevel_GamePlay::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBackGround>(LEVEL_LOGO, TEXT("Background")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CMonster>(LEVEL_LOGO, TEXT("Monster")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CTerrain>(LEVEL_LOGO, TEXT("Terrain")))
		return E_FAIL;

	TEXTINFO Info;
	Info.color = D3DCOLOR_ARGB(255, 0, 255, 0);
	Info.rcTemp = { 600, 300, 600 + 200, 300 + 300 };
	wsprintf(Info.szBuff, L"¹» ÃÄ´ÙºÁ ¾¾¹ß");
	if (FAILED(GAMEINSTANCE->Add_Text(&Info, 10.f)))
		return E_FAIL;

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


	SetWindowText(g_hWnd, TEXT("°ÔÀÓÇÁ·¼ÀÌ·¹º§ÀÓ. "));

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


#include "stdafx.h"
#include "..\Public\Level_Logo.h"
#include "GameInstance.h"
#include "LEvel_Loading.h"
#include "Song_Ship_Body.h"
#include "Monster.h"
#include "Terrain.h"
#include "Cam_Free.h"
#include "Cam_FPS.h"
#include "UITest.h"
#include "../Default/Logo.h"


CLevel_Logo::CLevel_Logo()
{
	
		
}

HRESULT CLevel_Logo::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CLogo>(LEVEL_LOGO, TEXT("Logo")))
		return E_FAIL;

	GAMEINSTANCE->PlayBGM(TEXT("Logo.wav"), 3.f);

	return S_OK;
}

void CLevel_Logo::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);		
	GAMEINSTANCE->Add_FadeOffSet();

	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		GAMEINSTANCE->PlaySoundW(TEXT("Start.wav"), 1.f);

		if (FAILED(GAMEINSTANCE->Get_Instance()->Register_OpenLevelEvent(LEVEL_LOADING, CLevel_Loading::Create(LEVEL_CHARACTERSELECT))))
			return;
	}
	
}

HRESULT CLevel_Logo::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	SetWindowText(g_hWnd, TEXT("로고 레벨입니다. "));

	return S_OK;
}

HRESULT CLevel_Logo::Ready_Layer_BackGround(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();

	return S_OK;
}

CLevel_Logo * CLevel_Logo::Create()
{
	CLevel_Logo*		pInstance = new CLevel_Logo();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_Logo");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_Logo::Free()
{
	__super::Free();

	delete this;

}


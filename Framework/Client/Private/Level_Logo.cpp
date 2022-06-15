#include "stdafx.h"
#include "..\Public\Level_Logo.h"
#include "GameInstance.h"
#include "LEvel_Loading.h"
#include "BackGround.h"
#include "Monster.h"
#include "Terrain.h"
#include "Cam_Free.h"

CLevel_Logo::CLevel_Logo()
{

}

HRESULT CLevel_Logo::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;

	return S_OK;
}

void CLevel_Logo::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);		

	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
		//Safe_AddRef(pGameInstance);

		if (FAILED(pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(LEVEL_GAMEPLAY))))
			return;

		//Safe_Release(pGameInstance);
	}

	if (GetKeyState('1') & 0x8000)
	{
		CGameInstance* pGameInstance = CGameInstance::Get_Instance();

		if (pGameInstance->Add_GameObject<CMonster>(LEVEL_LOGO, TEXT("Monster")))
			return;
	}
}

HRESULT CLevel_Logo::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	SetWindowText(g_hWnd, TEXT("롷고레벨임. "));

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


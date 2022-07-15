#include "stdafx.h"
#include "..\Public\Level_Loading.h"
#include "Loader.h"
#include "Level_Logo.h"
#include "Level_CharacterSelect.h"
#include "Level_RedPlanet.h"
#include "Level_SelectPlanet.h"
#include "Level_MagmaPlanet.h"
#include "Level_VenusPlanet.h"
#include "Level_ExoPlanet.h"
#include "Level_SunPlanet.h"
#include "GameInstance.h"

CLevel_Loading::CLevel_Loading()
{

}

HRESULT CLevel_Loading::Initialize(LEVEL eNextLevel)
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;

	m_eNextLevel = eNextLevel;

	m_pLoader = CLoader::Create(DEVICE, eNextLevel);
	if (nullptr == m_pLoader)
		return E_FAIL;

	return S_OK;
}

void CLevel_Loading::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);	

	if (true == m_pLoader->is_Finished())
	{
		
			CLevel*			pLevel = nullptr;

			switch (m_eNextLevel)
			{
			case LEVEL_LOGO:
				pLevel = CLevel_Logo::Create();
				break;
			case LEVEL_CHARACTERSELECT:
				pLevel = CLevel_CharacterSelect::Create();
				break;
			case LEVEL_SELECTPLANET:
				pLevel = CLevel_SelectPlanet::Create();
				break;
			case LEVEL_REDPLANET:
				pLevel = CLevel_RedPlanet::Create();
				break;
			case LEVEL_EXOPLANET:
				pLevel = CLevel_ExoPlanet::Create();
				break;
			case LEVEL_VENUSPLANET:
				pLevel = CLevel_VenusPlanet::Create();
				break;
			case LEVEL_MAGMAPLANET:
				pLevel = CLevel_MagmaPlanet::Create();
				break;
			case LEVEL_SUNPLANET:
				pLevel = CLevel_SunPlanet::Create();
				break;
			}

			if (nullptr == pLevel)
				return;

			CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
			
			pGameInstance->Open_Level(m_eNextLevel, pLevel);

		
	}
}

HRESULT CLevel_Loading::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	SetWindowText(g_hWnd, m_pLoader->Get_LoadingText());	

	return S_OK;
}

CLevel_Loading * CLevel_Loading::Create(LEVEL eNextLevel)
{
	CLevel_Loading*		pInstance = new CLevel_Loading();

	if (FAILED(pInstance->Initialize(eNextLevel)))
	{
		MSG_BOX("Failed to Created : CLevel_Loading");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_Loading::Free()
{
	__super::Free();

	Safe_Release(m_pLoader);

	delete this;
}


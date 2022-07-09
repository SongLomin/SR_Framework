#include "stdafx.h"
#include "..\Public\Loader.h"
#include "GameInstance.h"
#include "Song_Ship_Body.h"
#include "Monster.h"
#include "Loading.h"

CLoader::CLoader(LPDIRECT3DDEVICE9 pGraphic_Device)
	: m_pGraphic_Device(pGraphic_Device)
{
	//Safe_AddRef(m_pGraphic_Device);
}

unsigned int APIENTRY LoadingMain(void* pArg)
{
	CLoader* pLoader = (CLoader*)pArg;

	EnterCriticalSection(&pLoader->Get_CS());

	HRESULT hr = 0;

	switch (pLoader->Get_NextLevelID())
	{
	case LEVEL_LOGO:
		GAMEINSTANCE->Set_CurrentLevelIndex(pLoader->Get_NextLevelID());
		hr = pLoader->Loading_ForLogoLevel();
		break;
	case LEVEL_SELECTPLANET:
		GAMEINSTANCE->Set_CurrentLevelIndex(pLoader->Get_NextLevelID());
		hr = pLoader->Loading_ForSelectPlanet();
		break;
	case LEVEL_REDPLANET:
		GAMEINSTANCE->Set_CurrentLevelIndex(pLoader->Get_NextLevelID());
		hr = pLoader->Loading_ForRedPlanet();
		break;
	case LEVLE_EXOPLANET:
		GAMEINSTANCE->Set_CurrentLevelIndex(pLoader->Get_NextLevelID());
		hr = pLoader->Loaidng_ForExoPlanet();
		break;
	case LEVEL_VENUSPLANET:
		GAMEINSTANCE->Set_CurrentLevelIndex(pLoader->Get_NextLevelID());
		hr = pLoader->Loading_ForVenusPlanet();
		break;
	case LEVEL_MAGMAPLANET:
		GAMEINSTANCE->Set_CurrentLevelIndex(pLoader->Get_NextLevelID());
		hr = pLoader->Loading_ForMagmaPlanet();
		break;
	}

	if (FAILED(hr))
		MSG_BOX("Failed to Loading");

	LeaveCriticalSection(&pLoader->Get_CS());

	return 0;
}

HRESULT CLoader::Initialize(LEVEL eNextLevel)
{
	m_eNextLevel = eNextLevel;

	InitializeCriticalSection(&m_CriticalSection);


	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, LoadingMain, this, 0, nullptr);
	if (0 == m_hThread)
		return E_FAIL;

	return S_OK;
}

HRESULT CLoader::Loading_ForLogoLevel()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	//Safe_AddRef(pGameInstance);

#pragma region PROTOTYPE_GAMEOBJECT

	lstrcpy(m_szLoadingText, TEXT("객체를 생성중입니다."));
	/* For.Prototype_GameObject_BackGround */
	//if (FAILED(pGameInstance->Add_Prototype_GameObject<CPlayer_Body>()))
	//	return E_FAIL;

	//if (FAILED(pGameInstance->Add_Prototype_GameObject<CMonster>()))
	//	return E_FAIL;


#pragma endregion


	lstrcpy(m_szLoadingText, TEXT("텍스쳐를 로딩중 입니다. "));
	

	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("Booster"), TEXT("../Bin/Resources/Textures/UI/Booster.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("Shield"), TEXT("../Bin/Resources/Textures/UI/Shield.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("MainWeapon"), TEXT("../Bin/Resources/Textures/UI/MainWeapon.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("Sky_Test"), TEXT("../Bin/Resources/Textures/SkyBox/Sky_%d.dds"),
		TEXTURE_TYPE::TYPE_CUBE, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("Status"), TEXT("../Bin/Resources/Textures/UI/Status.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("HP"), TEXT("../Bin/Resources/Textures/UI/HP.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("SubWeapon"), TEXT("../Bin/Resources/Textures/UI/SubWeapon.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("EmptyItem"), TEXT("../Bin/Resources/Textures/UI/EmptyItem.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("Aim_Default"), TEXT("../Bin/Resources/Textures/UI/Aim_Default%d.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("Targeting"), TEXT("../Bin/Resources/Textures/UI/Targeting.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("Logo"), TEXT("../Bin/Resources/Textures/Logo/Logo.jpg"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("Loading"), TEXT("../Bin/Resources/Textures/Logo/Loading.jpg"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("Light_Moon"), TEXT("../Bin/Resources/Textures/Object/Light_Moon.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("Quest"), TEXT("../Bin/Resources/Textures/UI/Quest.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;


	if (!GAMEINSTANCE->Add_GameObject<CLoading>(LEVEL_LOADING, TEXT("Loading")))
		return E_FAIL;


	lstrcpy(m_szLoadingText, TEXT("쉐이더를 로딩중 입니다. "));

	GAMEINSTANCE->Load_Shader(TEXT("GBuffer"), TEXT("GBuffer.hlsl"));
	GAMEINSTANCE->Load_Shader(TEXT("DirectionalLight"), TEXT("DirectionalLight.hlsl"));
	GAMEINSTANCE->Load_Shader(TEXT("SpotLight"), TEXT("SpotLight.hlsl"));
	GAMEINSTANCE->Load_Shader(TEXT("PointLight"), TEXT("PointLight.hlsl"));


	if (!GAMEINSTANCE->Add_GameObject<CLoading>(LEVEL_LOADING, TEXT("Loading")))
		return E_FAIL;

	lstrcpy(m_szLoadingText, TEXT("로딩 끝 "));

	if (!GAMEINSTANCE->Add_GameObject<CLoading>(LEVEL_LOADING, TEXT("Loading")))
		return E_FAIL;

	m_isFinished = true;

	return S_OK;
}

HRESULT CLoader::Loading_ForRedPlanet()
{
	lstrcpy(m_szLoadingText, TEXT("텍스쳐를 로딩중 입니다. "));

	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("Test"), TEXT("../Bin/Resources/Textures/Default%d.jpg"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_DYNAMIC)))
		return E_FAIL;


	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("Tex_Terrain"), TEXT("../Bin/Resources/Textures/Terrain/SpaceStation.jpg"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_DYNAMIC)))
		return E_FAIL;


	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("Rock"), TEXT("../Bin/Resources/Textures/Object/Rock.png"), TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;


	lstrcpy(m_szLoadingText, TEXT("모델을 로딩중 입니다. "));


	lstrcpy(m_szLoadingText, TEXT("로딩 끝 "));


	m_isFinished = true;

	//Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLoader::Loading_ForMagmaPlanet()
{
	lstrcpy(m_szLoadingText, TEXT("텍스쳐를 로딩중 입니다. "));



	lstrcpy(m_szLoadingText, TEXT("모델을 로딩중 입니다. "));



	lstrcpy(m_szLoadingText, TEXT("로딩 끝 "));



	m_isFinished = true;


	return S_OK;
}

HRESULT CLoader::Loading_ForVenusPlanet()
{

	lstrcpy(m_szLoadingText, TEXT("텍스쳐를 로딩중 입니다. "));



	lstrcpy(m_szLoadingText, TEXT("모델을 로딩중 입니다. "));



	lstrcpy(m_szLoadingText, TEXT("로딩 끝 "));



	m_isFinished = true;


	return S_OK;
}

HRESULT CLoader::Loaidng_ForExoPlanet()
{

	lstrcpy(m_szLoadingText, TEXT("텍스쳐를 로딩중 입니다. "));



	lstrcpy(m_szLoadingText, TEXT("모델을 로딩중 입니다. "));


	lstrcpy(m_szLoadingText, TEXT("로딩 끝 "));



	m_isFinished = true;


	return S_OK;
}




HRESULT CLoader::Loading_ForSelectPlanet()
{

	lstrcpy(m_szLoadingText, TEXT("텍스쳐를 로딩중 입니다. "));

	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("Bomb_Effect"), TEXT("../Bin/Resources/Textures/Effect/Bomb/Explosion%d.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;


	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("TextBox_Yang"), TEXT("../Bin/Resources/Textures/UI/TextBox_Yang.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("Booster_Particle"), TEXT("../Bin/Resources/Textures/Particle/Booster%d.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("Smoke_Particle"), TEXT("../Bin/Resources/Textures/Particle/Smoke.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("Teleport_Effect"), TEXT("../Bin/Resources/Textures/Effect/Teleport/Teleport_%d.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;


	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("Warring"), TEXT("../Bin/Resources/Textures/UI/Warring.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("Dive"), TEXT("../Bin/Resources/Textures/UI/Dive.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;
	
	if (FAILED(GAMEINSTANCE->Load_Textures(TEXT("Planet"), TEXT("../Bin/Resources/Textures/Object/Planet_%d.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	lstrcpy(m_szLoadingText, TEXT("텍스쳐를 로딩중 입니다. "));



	lstrcpy(m_szLoadingText, TEXT("로딩 끝 "));



	m_isFinished = true;

	return S_OK;
}



CLoader* CLoader::Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel)
{
	CLoader* pInstance = new CLoader(pGraphic_Device);

	if (FAILED(pInstance->Initialize(eNextLevel)))
	{
		MSG_BOX("Failed to Created : CLoader");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLoader::Free()
{
	WaitForSingleObject(m_hThread, INFINITE);

	//Safe_Release(m_pGraphic_Device);

	DeleteCriticalSection(&m_CriticalSection);
	CloseHandle(m_hThread);

	delete this;
}

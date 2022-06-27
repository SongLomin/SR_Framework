#include "stdafx.h"
#include "..\Public\Loader.h"
#include "GameInstance.h"
#include "Player_Body.h"
#include "Monster.h"

CLoader::CLoader(LPDIRECT3DDEVICE9 pGraphic_Device)
	: m_pGraphic_Device(pGraphic_Device)
{
	//Safe_AddRef(m_pGraphic_Device);
}

unsigned int APIENTRY LoadingMain(void* pArg)
{
	CLoader*		pLoader = (CLoader*)pArg;

	EnterCriticalSection(&pLoader->Get_CS());

	HRESULT hr = 0;

	switch (pLoader->Get_NextLevelID())
	{
	case LEVEL_LOGO:
		GAMEINSTANCE->Set_CurrentLevelIndex(pLoader->Get_NextLevelID());
		hr = pLoader->Loading_ForLogoLevel();
		break;
	case LEVEL_GAMEPLAY:
		GAMEINSTANCE->Set_CurrentLevelIndex(pLoader->Get_NextLevelID());
		hr = pLoader->Loading_ForGamePlayLevel();
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
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
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
	if (FAILED(pGameInstance->Add_Textures(TEXT("Test"), TEXT("../Bin/Resources/Textures/Default%d.jpg"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_DYNAMIC)))
		return E_FAIL;
	/*메쉬 텍스처 추가*/
	if (FAILED(pGameInstance->Add_Textures(TEXT("Mesh_Cube"), TEXT("../Bin/Resources/Textures/Terrain/Filter.bmp"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Textures(TEXT("Mesh_Cube"), TEXT("../Bin/Resources/Textures/Terrain/Brush.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Textures(TEXT("Mesh_Cube"), TEXT("../Bin/Resources/Textures/Terrain/Height.bmp"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Textures(TEXT("Mesh_Cube"), TEXT("../Bin/Resources/Textures/Terrain/MyFilter.bmp"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Textures(TEXT("Mesh_Cube"), TEXT("../Bin/Resources/Textures/Terrain/MyHeight.bmp"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Textures(TEXT("Mesh_Cube"), TEXT("../Bin/Resources/Textures/Terrain/Tile0.jpg"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(pGameInstance->Add_Textures(TEXT("Mesh_Cube"), TEXT("../Bin/Resources/Textures/Terrain/Spaceship.jpg"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	lstrcpy(m_szLoadingText, TEXT("모델을 로딩중 입니다. "));


	lstrcpy(m_szLoadingText, TEXT("로딩 끝 "));	

	m_isFinished = true;

	//Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CLoader::Loading_ForGamePlayLevel()
{
	lstrcpy(m_szLoadingText, TEXT("텍스쳐를 로딩중 입니다. "));

	if (FAILED(GAMEINSTANCE->Add_Textures(TEXT("Test"), TEXT("../Bin/Resources/Textures/Default%d.jpg"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_DYNAMIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Add_Textures(TEXT("Tex_Terrain"), TEXT("../Bin/Resources/Textures/Terrain/SpaceStation.jpg"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_DYNAMIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Add_Textures(TEXT("Sky_Test"), TEXT("../Bin/Resources/Textures/SkyBox/Sky_%d.dds"),
		TEXTURE_TYPE::TYPE_CUBE, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Add_Textures(TEXT("Aim_Default"), TEXT("../Bin/Resources/Textures/UI/Aim_Default.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Add_Textures(TEXT("Targeting"), TEXT("../Bin/Resources/Textures/UI/Targeting.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Add_Textures(TEXT("Rock"), TEXT("../Bin/Resources/Textures/Object/Rock.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Add_Textures(TEXT("Logo"), TEXT("../Bin/Resources/Textures/Logo/Logo.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Add_Textures(TEXT("Status"), TEXT("../Bin/Resources/Textures/UI/Status.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	if (FAILED(GAMEINSTANCE->Add_Textures(TEXT("HP"), TEXT("../Bin/Resources/Textures/UI/HP.png"),
		TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE::MEMORY_STATIC)))
		return E_FAIL;

	lstrcpy(m_szLoadingText, TEXT("로딩 끝 "));

	m_isFinished = true;


	return S_OK;
}

CLoader* CLoader::Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel)
{
	CLoader*		pInstance = new CLoader(pGraphic_Device);

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

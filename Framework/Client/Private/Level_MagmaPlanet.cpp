#include "stdafx.h"
#include "Level_MagmaPlanet.h"
#include "GameInstance.h"
#include "LEvel_Loading.h"
#include "Song_Ship_Body.h"
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
#include "HpBar.h"
#include "BoosterBar.h"
#include "ShieldBar.h"
#include "BulletUI.h"
#include "BulletCountUI.h"
#include "AI_Friendly.h"
#include "Rock.h"
#include "MovingCamera.h"
#include "../Default/EnemySpace_Body.h"
#include "Kang_Ship_Body.h"
#include "Planet_Venus.h"
#include "Math_Utillity.h"
#include "Light_Moon.h"
#include "Quest.h"
#include <SelectPlanet_SkyBox.h>
#include <MagmaPlanet_SkyBox.h>
#include <TextBox.h>
#include <MagmaSpace_Body.h>

CLevel_MagmaPlanet::CLevel_MagmaPlanet()
{

}

HRESULT CLevel_MagmaPlanet::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;

	for (int i = 0; i < 15; ++i)
	{
		CTransform* pEnemyTransform = GAMEINSTANCE->Add_GameObject<CMagmaSpace_Body>(CURRENT_LEVEL, TEXT("Monster"))->Get_Component<CTransform>();

		_float3 SpawnPos{ 0, 0.f, 300.f };

		_float RotateX = (_float)(rand() % 361);
		_float RotateY = (_float)(rand() % 361);
		_float RotateZ = (_float)(rand() % 361);
		RotateX = D3DXToRadian(RotateX);
		RotateY = D3DXToRadian(RotateY);
		RotateZ = D3DXToRadian(RotateZ);


		SpawnPos = CMath_Utillity::Rotate_Vec3(_float3(RotateX, RotateY, RotateZ), SpawnPos);

		pEnemyTransform->Set_State(CTransform::STATE_POSITION, SpawnPos);
		++m_iSpawnCount;
	}

	for (int i = 0; i < 30; ++i)
	{
		CTransform* pRockTransform = GAMEINSTANCE->Add_GameObject<CRock>(CURRENT_LEVEL, TEXT("Rock"))->Get_Component<CTransform>();

		_float3 SpawnPos{ 0, 0.f, 400.f };

		_float RotateX = (_float)(rand() % 361);
		_float RotateY = (_float)(rand() % 361);
		_float RotateZ = (_float)(rand() % 361);
		RotateX = D3DXToRadian(RotateX);
		RotateY = D3DXToRadian(RotateY);
		RotateZ = D3DXToRadian(RotateZ);


		SpawnPos = CMath_Utillity::Rotate_Vec3(_float3(RotateX, RotateY, RotateZ), SpawnPos);

		pRockTransform->Set_State(CTransform::STATE_POSITION, SpawnPos);
	}


	if (!GAMEINSTANCE->Add_GameObject<CMagmaPlanet_SkyBox>(LEVEL_SELECTPLANET, TEXT("SkyBox")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CDefault_Aim>(LEVEL_MAGMAPLANET, TEXT("Aim")))
		return E_FAIL;


	if (!GAMEINSTANCE->Add_GameObject<CLight_Moon>(LEVEL_MAGMAPLANET, TEXT("Light_Moon")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CStatusBar>(LEVEL_MAGMAPLANET, TEXT("Status")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CHpBar>(LEVEL_MAGMAPLANET, TEXT("HP")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBoosterBar>(LEVEL_MAGMAPLANET, TEXT("Booster")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CShieldBar>(LEVEL_MAGMAPLANET, TEXT("Shield")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletUI>(LEVEL_MAGMAPLANET, TEXT("NormalBullet")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletCountUI>(LEVEL_MAGMAPLANET, TEXT("CBulletCountUI")))
		return E_FAIL;


	//if (!GAMEINSTANCE->Add_GameObject<CTargetingBox>(LEVEL_GAMEPLAY, TEXT("Targeting")))
	//	return E_FAIL;

	m_pTextBoxObject = GAMEINSTANCE->Add_GameObject<CTextBox>(LEVEL_MAGMAPLANET, TEXT("TextBox_Yang"));
	m_pTextBoxObject->Set_Enable(false);

	m_pQuestBoxObject = GAMEINSTANCE->Add_GameObject<CQuest>(LEVEL_MAGMAPLANET, TEXT("Quest"));
	m_pQuestBoxObject->Set_Enable(false);




	return S_OK;
}

void CLevel_MagmaPlanet::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);		

	m_fSpawnTime -= fTimeDelta;

	if (m_fSpawnTime < 0.f && m_bSpawnCheck == true)
	{
		CTransform* pEnemyTransform = GAMEINSTANCE->Add_GameObject<CMagmaSpace_Body>(CURRENT_LEVEL, TEXT("Monster"), nullptr, nullptr, true)
										->Get_Component<CTransform>();
		_float3 SpawnPos{ 0, 0.f, 300.f };

		_float RotateX = (_float)(rand() % 361);
		_float RotateY = (_float)(rand() % 361);
		_float RotateZ = (_float)(rand() % 361);
		RotateX = D3DXToRadian(RotateX);
		RotateY = D3DXToRadian(RotateY);
		RotateZ = D3DXToRadian(RotateZ);

		SpawnPos = CMath_Utillity::Rotate_Vec3(_float3(RotateX, RotateY, RotateZ), SpawnPos);
		pEnemyTransform->Set_State(CTransform::STATE_POSITION, SpawnPos);

		m_fSpawnTime = 2.f;

		++m_iSpawnCount;
		if (m_iSpawnCount == 30)
		{
			m_bSpawnCheck = false;
		}
	}

	MagmaPlanet_Event(fTimeDelta);


}

HRESULT CLevel_MagmaPlanet::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;


	SetWindowText(g_hWnd, TEXT("Magma Planet 레벨입니다. "));

	return S_OK;
}

void CLevel_MagmaPlanet::MagmaPlanet_Event(float fTimeDelta)
{
	m_fTextBoxTime -= fTimeDelta;

	auto Monster = GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("Monster"));

	_uint MonsterSize = Monster->size();

	m_iMonsterCount = m_iSpawnCount - MonsterSize;

	// 양갑렬 대위
	if (m_fTextBoxTime <= 295.f && !m_bEventCheck[0])
	{
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("Magma Planet은 적군의 엘리트들이 모여있는 곳일세. \n 엘리트들을 소탕해, 작전을 완수 해주게. "), 0);
	}

	if (m_fTextBoxTime <= 292.f && !m_bEventCheck[0])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[0] = true;
	}

	if (m_fTextBoxTime <= 290.f && !m_bEventCheck[1])
	{
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("조심하게! 내 생각보다 수가 많네!"), 0);
	}

	if (m_fTextBoxTime <= 287.f && !m_bEventCheck[1])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[1] = true;
	}


	if (m_fTextBoxTime <= 284.f && !m_bEventCheck[2])
	{
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("우리의 존재를 눈치챈듯 하네! \n 힘을 합쳐 엘리트들을 말살하세!"), 0);
	}


	if (m_fTextBoxTime <= 281.f && !m_bEventCheck[2])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[2] = true;
	}




	if (m_fTextBoxTime <= 279.f && !m_bEventCheck[8])
	{
		m_pQuestBoxObject->Set_Enable(true);

		GAMEINSTANCE->Add_Text(_point{ (LONG)m_iFontiX, (LONG)50 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("            현재 임무\n   엘리트 비행선 섬멸  \n %d / 30 \n   남은시간 (초) : "), 0 , m_iMonsterCount);
		GAMEINSTANCE->Add_Text(_point{ (LONG)m_iFontiXCount, (LONG)88 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT(" %d"), 1, (_uint)m_fMaxTime);

		if (m_iFontiX <= 1040)
		{
			m_iFontiX = 1040;
		}

		if (m_iFontiXCount <= 1150)
		{
			m_iFontiXCount = 1150;
		}

		m_iFontiX -= 0.8;
		m_iFontiXCount -= 0.8;
		m_fMaxTime -= fTimeDelta;
	}


	if (m_fTextBoxTime <= 179 && !m_bEventCheck[8])
	{
		m_pQuestBoxObject->Set_Enable(false);
		m_bEventCheck[8] = true;
	}


	// 적생성 false 모든적 처치임무
	//if (m_fTextBoxTime <= 175 && !m_bEventCheck[9])
	//{
	//	m_bSpawnCheck = false;
	//	m_pQuestBoxObject->Set_Enable(true);
	//	GAMEINSTANCE->Add_Text(_point{ (LONG)1040, (LONG)50 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("            현재 임무  \n    모든 적 함체 섬멸 / 화물선 호위 "), 0);
	//
	//	if (m_iFontiX <= 1040)
	//	{
	//		m_iFontiX = 1040;
	//	}
	//
	//	m_iFontiX -= 0.8;
	//}


	// (화물호위? 조건) 퀘스트박스 소멸, 폰트 소멸
	if (m_fTextBoxTime <= 100 && !m_bEventCheck[9])
	{
		m_pQuestBoxObject->Set_Enable(false);
		m_bEventCheck[9] = true;

		m_fTextBoxTime = 300;
	}


	if (m_iMonsterCount >= 30)
	{
		if (m_iEnemyCount <= 295 && !m_bEventCheck[6] && !m_bSpawnCheck && m_bEventCheck[9])
		{
			m_pTextBoxObject->Set_Enable(true);
			GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("고생했네! \n 오늘밤은 맘 편히 발 쭉뻗고 자겠구만! \n 맘 편히 복귀하도록 하게나! "), 0);
		}

		if (m_iEnemyCount <= 290 && !m_bEventCheck[6] && !m_bSpawnCheck && m_bEventCheck[9])
		{
			m_pTextBoxObject->Set_Enable(false);
			m_bEventCheck[6] = true;
		}

		if (FAILED(GAMEINSTANCE->Register_OpenLevelEvent(LEVEL_LOADING, CLevel_Loading::Create(LEVEL::LEVEL_SELECTPLANET))))
			return;
	}
	



	if (m_fTextBoxTime <= 285 && m_iEnemyCount <= 3 && !m_bEventCheck[7] && !m_bSpawnCheck)
	{
		// 보상 UI / 선택
	}


	if (!m_bEventCheck[7] && !m_bSpawnCheck && m_iEnemyCount <= 3)  // 보상 받았단 정보 조건 넣어줌
	{
		//m_bEventCheck[7] = true;
		//GAMEINSTANCE->Get_CurrentLevel()->Change_Level(this, LEVEL::LEVEL_SELECTPLANET);
	}
	

}

CLevel_MagmaPlanet* CLevel_MagmaPlanet::Create()
{
	CLevel_MagmaPlanet*		pInstance = new CLevel_MagmaPlanet();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_MagmaPlanet");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_MagmaPlanet::Free()
{
	__super::Free();

	delete this;
}




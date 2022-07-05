#include "stdafx.h"
#include "Level_RedPlanet.h"
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
#include "TextBox.h"
#include "Hong_Ship_Body.h"
#include "Shin_Ship_Body.h"
#include <SpaceDust_PSystem.h>

CLevel_RedPlanet::CLevel_RedPlanet()
{

}


HRESULT CLevel_RedPlanet::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;



	CGameObject* FPS_Cam = GAMEINSTANCE->Add_GameObject<CCam_FPS>(CURRENT_LEVEL, TEXT("Camera"));
	FPS_Cam->Get_Component<CCamera>()->Set_Param(D3DXToRadian(65.0f), (_float)g_iWinCX / g_iWinCY, 0.2f, 900.f);
	GAMEINSTANCE->Register_Camera(TEXT("FPS"), FPS_Cam->Get_Component<CCamera>());

	CGameObject* Shoulder_Cam = GAMEINSTANCE->Add_GameObject<CCam_Shoulder>(CURRENT_LEVEL, TEXT("Camera"));
	Shoulder_Cam->Get_Component<CCamera>()->Set_Param(D3DXToRadian(65.0f), (_float)g_iWinCX / g_iWinCY, 0.2f, 900.f);
	GAMEINSTANCE->Register_Camera(TEXT("Shoulder"), Shoulder_Cam->Get_Component<CCamera>());

	CGameObject* TPS_Cam = GAMEINSTANCE->Add_GameObject<CCam_TPS>(CURRENT_LEVEL, TEXT("Camera"));
	TPS_Cam->Get_Component<CCamera>()->Set_Param(D3DXToRadian(65.0f), (_float)g_iWinCX / g_iWinCY, 0.2f, 900.f);
	GAMEINSTANCE->Register_Camera(TEXT("TPS"), TPS_Cam->Get_Component<CCamera>());

	//CURRENT_LEVEL이게 LEVEL_STATIC이 아님. 그래서 터짐.
	if (!GAMEINSTANCE->Add_GameObject<CSong_Ship_Body>(LEVEL_REDPLANET, TEXT("Player")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CKang_Ship_Body>(LEVEL_REDPLANET, TEXT("Player")))
		return E_FAIL;

	/*if (!GAMEINSTANCE->Add_GameObject<CHong_Ship_Body>(LEVEL_REDPLANET, TEXT("Player")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CShin_Ship_Body>(LEVEL_REDPLANET, TEXT("Player")))
		return E_FAIL;*/

	for (int i = 0; i < 15; ++i)
	{
		if (!GAMEINSTANCE->Add_GameObject<CEnemySpace_Body>(LEVEL_REDPLANET, TEXT("EnemySpace_Body")))
			return E_FAIL;
	}

	/*for (int i = 0; i < 50; ++i)
	{
		if (!GAMEINSTANCE->Add_GameObject<CAI_Friendly>(LEVEL_REDPLANET, TEXT("AI_Friendly")))
			return E_FAIL;
	}*/


	/*for (int i = 0; i < 5; i++)
	{
		GAMEINSTANCE->Add_GameObject<CMonster>(LEVEL_GAMEPLAY, TEXT("Monster"))
			->Get_Component<CTransform>()->Set_State(CTransform::STATE_POSITION, _float3(i * 5.f, 0.f, 0.f));
	}*/

	if (!GAMEINSTANCE->Add_GameObject<CTerrain>(LEVEL_REDPLANET, TEXT("Terrain")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CSkyBox>(LEVEL_REDPLANET, TEXT("SkyBox")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CDefault_Aim>(LEVEL_REDPLANET, TEXT("Aim")))
		return E_FAIL;

	for (int i = 0; i < 30; ++i)
	{
		if (!GAMEINSTANCE->Add_GameObject<CRock>(LEVEL_REDPLANET, TEXT("Rock")))
			return E_FAIL;
	}

	if (!GAMEINSTANCE->Add_GameObject<CLight_Moon>(LEVEL_REDPLANET, TEXT("Light_Moon")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CStatusBar>(LEVEL_REDPLANET, TEXT("Status")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CHpBar>(LEVEL_REDPLANET, TEXT("HP")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBoosterBar>(LEVEL_REDPLANET, TEXT("Booster")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CShieldBar>(LEVEL_REDPLANET, TEXT("Shield")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletUI>(LEVEL_REDPLANET, TEXT("NormalBullet")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletCountUI>(LEVEL_REDPLANET, TEXT("CBulletCountUI")))
		return E_FAIL;

	((CSpaceDust_PSystem*)GAMEINSTANCE->Add_GameObject<CSpaceDust_PSystem>(LEVEL_SELECTPLANET, TEXT("Particle")))->AddParticle(500);

	m_pTextBoxObject = GAMEINSTANCE->Add_GameObject<CTextBox>(LEVEL_SELECTPLANET, TEXT("TextBox_Yang"));
	m_pTextBoxObject->Set_Enable(false);

	m_pQuestBoxObject = GAMEINSTANCE->Add_GameObject<CQuest>(LEVEL_SELECTPLANET, TEXT("Quest"));
	m_pQuestBoxObject->Set_Enable(false);



	//if (!GAMEINSTANCE->Add_GameObject<CTargetingBox>(LEVEL_GAMEPLAY, TEXT("Targeting")))
	//	return E_FAIL;




	/*TEXTINFO Info;
	Info.color = D3DCOLOR_ARGB(255, 0, 255, 0);
	Info.rcTemp = { 600, 300, 600 + 200, 300 + 300 };
	wsprintf(Info.szBuff, L"10초동안 출력");
	if (FAILED(GAMEINSTANCE->Add_Text(&Info, 10.f)))
		return E_FAIL;*/

	return S_OK;
}

void CLevel_RedPlanet::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


	
	m_fSpawnTime -= fTimeDelta;
	if (m_fSpawnTime < 0.f)
	{
		if (!GAMEINSTANCE->Add_GameObject<CEnemySpace_Body>(CURRENT_LEVEL, TEXT("EnemySpace_Body")))
			return;

		m_fSpawnTime = 5.f;
	}





	if (KEY_INPUT(KEY::F1, KEY_STATE::TAP))
	{
		if (FAILED(GAMEINSTANCE->Get_Instance()->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(LEVEL_SELECTPLANET))))
			return;
	}



	/*if (m_fMaxTime <= 0)
	{
		if (FAILED(GAMEINSTANCE->Get_Instance()->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(LEVEL_SELECTPLANET))))
			return;
	}*/


	

	RedPlanet_Event(fTimeDelta);


	

}

HRESULT CLevel_RedPlanet::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;


	SetWindowText(g_hWnd, TEXT("Red Planet 레벨입니다. "));

	return S_OK;
}

CLevel_RedPlanet * CLevel_RedPlanet::Create()
{
	CLevel_RedPlanet*		pInstance = new CLevel_RedPlanet();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_RedPlanet");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_RedPlanet::Free()
{
	__super::Free();

	delete this;
}

void CLevel_RedPlanet::RedPlanet_Event(float fTimeDelta)
{
	m_fTextBoxTime -= fTimeDelta;


	if (m_fTextBoxTime <= 295.f && !m_bEventCheck[0])
	{
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("이쪽 행성은 왠지 빨갛고 불길한 기분이 드는군... "), 0);
	}

	if (m_fTextBoxTime <= 292.f && !m_bEventCheck[0])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[0] = true;
	}

	if (m_fTextBoxTime <= 290.f && !m_bEventCheck[1])
	{
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("이봐 저기 달쪽에 무언가 빨간색이 보이지않나?"), 0);
	}

	if (m_fTextBoxTime <= 287.f && !m_bEventCheck[1])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[1] = true;
	}


	if (m_fTextBoxTime <= 284.f && !m_bEventCheck[2])
	{
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("젠장! 전방에 적 함체들이 몰려오고있어! \n 지금바로 지원병력을 보낼테니 조금만 버텨주게!"), 0);
	}


	if (m_fTextBoxTime <= 281.f && !m_bEventCheck[2])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[2] = true;
	}

	if (m_fTextBoxTime <= 229.f && !m_bEventCheck[3])
	{
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("지원병력이 거의 다 와가네! 조금만 더 버텨주게나!"), 0);
	}

	if (m_fTextBoxTime <= 225.f && !m_bEventCheck[3])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[3] = true;
	}

	if (m_fTextBoxTime <= 179.f && !m_bEventCheck[4])
	{
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("고생 많았네 모조리 쓸어보자고!"), 0);

		m_fSpawnTime -= fTimeDelta;

		if (m_fSpawnTime < 1.5f)
		{
			if (!GAMEINSTANCE->Add_GameObject<CAI_Friendly>(CURRENT_LEVEL, TEXT("AI_Friendly")))
				return;

			m_fSpawnTime = 1.5f;
		}

	}


	if (m_fTextBoxTime <= 172.f && !m_bEventCheck[4])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[4] = true;
	}


	if (m_fTextBoxTime <= 279.f && !m_bEventCheck[8])
	{
		m_pQuestBoxObject->Set_Enable(true);

		GAMEINSTANCE->Add_Text(_point{ (LONG)1040, (LONG)50 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("            현재 임무  \n  지원병력 도착까지 생존하기 \n  남은시간 (초) : "), 0);
		GAMEINSTANCE->Add_Text(_point{ (LONG)1145, (LONG)88 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("%d"), 1, (_uint)m_fMaxTime);
		m_fMaxTime -= fTimeDelta;
	}


	if (m_fTextBoxTime <= 179 && !m_bEventCheck[8])
	{
		m_pQuestBoxObject->Set_Enable(false);
		m_bEventCheck[8] = true;
	}


	if (m_fTextBoxTime <= 175 && !m_bEventCheck[9])
	{
		m_pQuestBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)1040, (LONG)50 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("            현재 임무  \n    모든 적 함체 섬멸 "), 0);
	}
}


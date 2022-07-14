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
#include <SkyBox.h>
#include "../Default/EnemySpace_Body.h"
#include "StatusBar.h"
#include "HpBar.h"
#include "BoosterBar.h"
#include "ShieldBar.h"
#include "BulletUI.h"
#include "BulletCountUI.h"
#include "AI_Friendly.h"
#include "Rock_1.h"
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
#include <SelectPlanet_SkyBox.h>
#include "AI_TransportShip.h"
#include "RedPlanet_SkyBox.h"
#include <Planet_Select.h>
#include "Enemy_Roller.h"
#include "Boss_HpTable.h"
#include "Boss_Name.h"
#include "TransportShip_HpBar.h"




CLevel_RedPlanet::CLevel_RedPlanet()
{

}


HRESULT CLevel_RedPlanet::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;



	//CGameObject* pPlayer = GAMEINSTANCE->Add_GameObject<CKang_Ship_Body>(LEVEL_STATIC, TEXT("Player"));
	//pPlayer->Set_Controller(CONTROLLER::AI);



	/*if (!GAMEINSTANCE->Add_GameObject<CHong_Ship_Body>(LEVEL_REDPLANET, TEXT("Player")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CShin_Ship_Body>(LEVEL_REDPLANET, TEXT("Player")))
		return E_FAIL;*/

	for (int i = 0; i < 20; ++i)
	{
		CTransform* pEnemyTransform = GAMEINSTANCE->Add_GameObject<CEnemySpace_Body>(CURRENT_LEVEL, TEXT("EnemySpace_Body"))->Get_Component<CTransform>();

		_float3 SpawnPos{ 0, 0.f, 300.f };

		_float RotateX = (_float)(rand() % 361);
		_float RotateY = (_float)(rand() % 361);
		_float RotateZ = (_float)(rand() % 361);
		RotateX = D3DXToRadian(RotateX);
		RotateY = D3DXToRadian(RotateY);
		RotateZ = D3DXToRadian(RotateZ);


		SpawnPos = CMath_Utillity::Rotate_Vec3(_float3(RotateX, RotateY, RotateZ), SpawnPos);

		pEnemyTransform->Set_State(CTransform::STATE_POSITION, SpawnPos);

	}

	 if (!GAMEINSTANCE->Add_GameObject<CAI_TransportShip>(LEVEL_REDPLANET, TEXT("TransportShip")))
		return E_FAIL;

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

	if (!GAMEINSTANCE->Add_GameObject<CRedPlanet_SkyBox>(LEVEL_SELECTPLANET, TEXT("SkyBox")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CDefault_Aim>(LEVEL_REDPLANET, TEXT("Aim_UI")))
		return E_FAIL;

	for (int i = 0; i < 30; ++i)
	{
		if (!GAMEINSTANCE->Add_GameObject<CRock_1>(LEVEL_REDPLANET, TEXT("Rock_1")))
			return E_FAIL;
	}

	if (!GAMEINSTANCE->Add_GameObject<CLight_Moon>(LEVEL_REDPLANET, TEXT("Light_Moon")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CStatusBar>(LEVEL_REDPLANET, TEXT("Status_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CHpBar>(LEVEL_REDPLANET, TEXT("HP_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBoosterBar>(LEVEL_REDPLANET, TEXT("Booster_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CShieldBar>(LEVEL_REDPLANET, TEXT("Shield_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletUI>(LEVEL_REDPLANET, TEXT("NormalBullet_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletCountUI>(LEVEL_REDPLANET, TEXT("BulletCount_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CEnemy_Roller>(LEVEL_REDPLANET, TEXT("Enemy_Roller")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBossHpTable>(LEVEL_REDPLANET, TEXT("Boss_HP_Table")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBossName>(LEVEL_REDPLANET, TEXT("Boss_Name")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CTransportShip_HpBar>(LEVEL_REDPLANET, TEXT("TransportShip_HpBar")))
		return E_FAIL;

	//((CSpaceDust_PSystem*)GAMEINSTANCE->Add_GameObject<CSpaceDust_PSystem>(LEVEL_REDPLANET, TEXT("Particle")))->AddParticle(500);

	m_pTextBoxObject = GAMEINSTANCE->Add_GameObject<CTextBox>(LEVEL_REDPLANET, TEXT("TextBox_Yang"));
	m_pTextBoxObject->Set_Enable(false);

	m_pQuestBoxObject = GAMEINSTANCE->Add_GameObject<CQuest>(LEVEL_REDPLANET, TEXT("Quest_UI"));
	m_pQuestBoxObject->Set_Enable(false);



	//if (!GAMEINSTANCE->Add_GameObject<CTargetingBox>(LEVEL_GAMEPLAY, TEXT("Targeting")))
	//	return E_FAIL;

	GAMEINSTANCE->Add_GameObject<CPlanet_Select>(LEVEL_REDPLANET, TEXT("Earth"));



	return S_OK;
}

void CLevel_RedPlanet::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


	
	m_fSpawnTime -= fTimeDelta;

	if (m_fSpawnTime < 0.f && m_bSpawnCheck)
	{
		
			CTransform* pEnemyTransform = GAMEINSTANCE->Add_GameObject<CEnemySpace_Body>(CURRENT_LEVEL, TEXT("EnemySpace_Body"), nullptr, nullptr, true)
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

		     m_fSpawnTime = 3.f;
	}


	if (KEY_INPUT(KEY::F1, KEY_STATE::TAP))
	{
		GAMEINSTANCE->Register_OpenLevelEvent(LEVEL_LOADING, CLevel_Loading::Create(LEVEL_SELECTPLANET));
	}


	RedPlanet_Event(fTimeDelta);


	

}

HRESULT CLevel_RedPlanet::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;


	SetWindowText(g_hWnd, TEXT("Red Planet 레벨입니다. "));

	return S_OK;
}

void CLevel_RedPlanet::Change_Level(void* pArg, _uint _iNextLevel)
{
	if (m_bCinematic)
		return;


	m_fTime = 5.f;
	m_bCinematic = true;
	m_iNextLevel = _iNextLevel;

	list<CGameObject*>* pLayer = GAMEINSTANCE->Find_Layer(LEVEL_STATIC, TEXT("Player"));
	for (auto& iter = pLayer->begin(); iter != pLayer->end(); ++iter)
	{
		if (CONTROLLER::PLAYER == (*iter)->Get_Controller())
		{


			(*iter)->Set_Controller(CONTROLLER::AI);
			CComponent* Temp = (*iter)->Get_Component<CAI_Controller>();
			WEAK_PTR(Temp);
			Temp->Set_Enable(false);
			Temp = (*iter)->Get_Component<CRigid_Body>();
			static_cast<CRigid_Body*>(Temp)->Add_Dir(CRigid_Body::SPIN, 0.f);
			static_cast<CRigid_Body*>(Temp)->Add_Dir(CRigid_Body::DOWN, 0.f);
			if (pArg)
			{
				Temp = (*iter)->Get_Component<CTransform>();
				static_cast<CTransform*>(Temp)->LookAt((CTransform*)pArg, true);
			}
			RETURN_WEAKPTR(Temp);
		}
	}

	CGameObject* Camera_Origin = GAMEINSTANCE->Get_Camera()->Get_Owner();
	CTransform* pCameraTransform = Camera_Origin->Get_Component<CTransform>();
	GAMEINSTANCE->Update_MovingCam();
	CGameObject* Camera_Moving = GAMEINSTANCE->Get_Camera()->Get_Owner();
	CTransform* pCameraMovingTransform = Camera_Moving->Get_Component<CTransform>();

	_float3	vUp, vLook, vRight, vSpeed;

	pCameraMovingTransform->Set_State(CTransform::STATE_RIGHT, vRight = pCameraTransform->Get_State(CTransform::STATE_RIGHT));
	pCameraMovingTransform->Set_State(CTransform::STATE_UP, vUp = pCameraTransform->Get_State(CTransform::STATE_UP));
	pCameraMovingTransform->Set_State(CTransform::STATE_LOOK, vLook = pCameraTransform->Get_State(CTransform::STATE_LOOK));
	pCameraMovingTransform->Set_State(CTransform::STATE_POSITION, pCameraTransform->Get_State(CTransform::STATE_POSITION));



	static_cast<CMovingCamera*>(Camera_Moving)->Add_Movement(2.f, 0.f,
		*D3DXVec3Normalize(&vSpeed, &(-vLook)) * 1.5f, _float3(0.f, 0.f, 0.f),
		nullptr, nullptr, 0.1f, 0.f
	);

	static_cast<CMovingCamera*>(Camera_Moving)->Add_Movement(3.f, 0.f,
		_float3(0.f, 0.f, 0.f), *D3DXVec3Normalize(&vSpeed, &(-vLook)) * 4.f,
		nullptr, nullptr, 1.f, 0.05f
	);

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
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("Red Planet 에서 화물선을 안전하게 옮기기 위해\n 용병들을 고용한다고 하는구만.\n 옆에 보이는 화물선을 목적지까지 호위해주게. "), 0);
	}

	if (m_fTextBoxTime <= 292.f && !m_bEventCheck[0])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[0] = true;
	}

	if (m_fTextBoxTime <= 290.f && !m_bEventCheck[1])
	{
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("주변에 무언가 다가오는것 같은데?."), 0);
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


	//////////////지원병력 생존 퀘스트 카운트 0 될시 아군AI생성/////////////////// 

	if (m_fTextBoxTime <= 179.f && !m_bEventCheck[4])
	{
		
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("지원군들이 도착했네! \n 고생 많았네 모조리 쓸어보자고!"), 0);

		m_fSpawnTime -= fTimeDelta;

		if (m_fSpawnTime < 1.7f && m_bSpawnCheck)
		{
			if (!GAMEINSTANCE->Add_GameObject<CAI_Friendly>(CURRENT_LEVEL, TEXT("AI_Friendly"), nullptr, nullptr, true))
				return;

			m_fSpawnTime = 2.0f;
		}

	}

	


	// 7초뒤 아군생성 false

	if (m_fTextBoxTime <= 172.f && !m_bEventCheck[4])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[4] = true;
	}




	if (m_fTextBoxTime <= 279.f && !m_bEventCheck[8])
	{
		m_pQuestBoxObject->Set_Enable(true);

		GAMEINSTANCE->Add_Text(_point{ (LONG)m_iFontiX, (LONG)270 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("            현재 임무\n지원병력 도착까지 생존 / 화물선 호위 \n      남은시간 (초) : "), 0);
		GAMEINSTANCE->Add_Text(_point{ (LONG)m_iFontiXCount, (LONG)308 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("    %d"), 1, (_uint)m_fMaxTime);

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
	if (m_fTextBoxTime <= 175 && !m_bEventCheck[9])
	{
		m_bSpawnCheck = false;
		m_pQuestBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)1040, (LONG)270 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("            현재 임무  \n    모든 적 함체 섬멸 / 화물선 호위 "), 0);

		if (m_iFontiX <= 1040)
		{
			m_iFontiX = 1040;
		}

		m_iFontiX -= 0.8;
	}


	// (화물호위? 조건) 퀘스트박스 소멸, 폰트 소멸
	if (m_fTextBoxTime <= 100 && !m_bEventCheck[9])
	{
		m_pQuestBoxObject->Set_Enable(false);
		m_bEventCheck[9] = true;
	
		m_fTextBoxTime = 300;
	}

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


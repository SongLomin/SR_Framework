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
#include "../Default/EnemySpace_Body.h"
#include "StatusBar.h"
#include "HpBar.h"
#include "BoosterBar.h"
#include "ShieldBar.h"
#include "BulletUI.h"
#include "BulletCountUI.h"
#include "AI_Friendly.h"
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
#include <Rock_1.h>
#include <Planet_Select.h>
#include <Level_SelectPlanet.h>

CLevel_MagmaPlanet::CLevel_MagmaPlanet()
{

}

HRESULT CLevel_MagmaPlanet::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;

	for (int i = 0; i < 15; ++i)
	{
		CTransform* pEnemyTransform = GAMEINSTANCE->Add_GameObject<CMagmaSpace_Body>(CURRENT_LEVEL, TEXT("Enemy_MagmaSpace"))->Get_Component<CTransform>();

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
		CTransform* pRockTransform = GAMEINSTANCE->Add_GameObject<CRock_1>(CURRENT_LEVEL, TEXT("Rock_1"))->Get_Component<CTransform>();

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

	if (!GAMEINSTANCE->Add_GameObject<CDefault_Aim>(LEVEL_MAGMAPLANET, TEXT("Aim_UI")))
		return E_FAIL;


	if (!GAMEINSTANCE->Add_GameObject<CLight_Moon>(LEVEL_MAGMAPLANET, TEXT("Light_Moon_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CStatusBar>(LEVEL_MAGMAPLANET, TEXT("Status_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CHpBar>(LEVEL_MAGMAPLANET, TEXT("HP_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBoosterBar>(LEVEL_MAGMAPLANET, TEXT("Booster_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CShieldBar>(LEVEL_MAGMAPLANET, TEXT("Shield_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletUI>(LEVEL_MAGMAPLANET, TEXT("NormalBullet_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletCountUI>(LEVEL_MAGMAPLANET, TEXT("BulletCount_UI")))
		return E_FAIL;


	m_pTextBoxObject = GAMEINSTANCE->Add_GameObject<CTextBox>(LEVEL_MAGMAPLANET, TEXT("TextBox_Yang"));
	m_pTextBoxObject->Set_Enable(false);

	m_pQuestBoxObject = GAMEINSTANCE->Add_GameObject<CQuest>(LEVEL_MAGMAPLANET, TEXT("Quest_UI"));
	m_pQuestBoxObject->Set_Enable(false);

	GAMEINSTANCE->Add_GameObject<CPlanet_Select>(LEVEL_VENUSPLANET, TEXT("Earth"));


	return S_OK;
}

void CLevel_MagmaPlanet::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);		

	m_fSpawnTime -= fTimeDelta;

	if (m_fSpawnTime < 0.f && m_bSpawnCheck == true)
	{
		CTransform* pEnemyTransform = GAMEINSTANCE->Add_GameObject<CMagmaSpace_Body>(CURRENT_LEVEL, TEXT("Enemy_MagmaSpace"), nullptr, nullptr, true)
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

	if (KEY_INPUT(KEY::F1, KEY_STATE::TAP))
	{
		GAMEINSTANCE->Register_OpenLevelEvent(LEVEL_LOADING, CLevel_Loading::Create(LEVEL_SELECTPLANET));
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

void CLevel_MagmaPlanet::Change_Level(void* pArg, _uint _iNextLevel)
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

void CLevel_MagmaPlanet::MagmaPlanet_Event(float fTimeDelta)
{
	m_fTextBoxTime -= fTimeDelta;

	auto Monster = GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("Enemy_MagmaSpace"));

	_uint MonsterSize = Monster->size();

	m_iMonsterCount = m_iSpawnCount - MonsterSize;

	// 양갑렬 대위
	if (m_fTextBoxTime <= 298.f && !m_bEventCheck[0])
	{
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("Magma Planet은 적군의 엘리트들이 모여있는 곳일세. \n 엘리트들을 소탕해, 작전을 완수 해주게. "), 0);
	}

	if (m_fTextBoxTime <= 296.f && !m_bEventCheck[0])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[0] = true;
	}

	if (m_fTextBoxTime <= 294.f && !m_bEventCheck[1])
	{
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("조심하게! 내 생각보다 수가 많네!"), 0);
	}

	if (m_fTextBoxTime <= 292.f && !m_bEventCheck[1])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[1] = true;
	}


	if (m_fTextBoxTime <= 290.f && !m_bEventCheck[2])
	{
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("우리의 존재를 눈치챈듯 하네! \n 힘을 합쳐 엘리트들을 말살하세!"), 0);
	}


	if (m_fTextBoxTime <= 288.f && !m_bEventCheck[2])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[2] = true;
	}


	if (m_fTextBoxTime <= 290.f && !m_bEventCheck[8])
	{
		m_pQuestBoxObject->Set_Enable(true);

		GAMEINSTANCE->Add_Text(_point{ (LONG)m_iFontiX, (LONG)50 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("            현재 임무\n      엘리트 비행선 섬멸  \n           %d / 100    \n     남은시간 (초) :"), 0 , m_iMonsterCount);
		GAMEINSTANCE->Add_Text(_point{ (LONG)m_iFontiXCount, (LONG)88 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("\n  %d"), 1, (_uint)m_fMaxTime);

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


	/*if (m_fMaxTime == 0)
	{
		m_pQuestBoxObject->Set_Enable(false);
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("이런, 여기에 더있다간 기체를 더이상 수리를 못하게될거세. \n 아쉽지만 일단 퇴각하도록."), 0);
	}


	if (m_fMaxTime >= 0 && m_iMonsterCount <= 0)
	{
		m_pQuestBoxObject->Set_Enable(false);
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 }, D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("하하하 역시 자네는 내가 눈여겨 보고있엇다네! \n 어서 복귀해서 축배를 드세나!"), 0);
	}*/


	

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




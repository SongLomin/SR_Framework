#include "stdafx.h"
#include "Level_SelectPlanet.h"
#include "GameInstance.h"
#include "Level_Loading.h"
#include <time.h>
#include "Cam_FPS.h"
#include "Cam_Shoulder.h"
#include "Cam_TPS.h"
#include "MovingCamera.h"
#include "Cam_Free.h"
#include "Song_Ship_Body.h"
#include "SelectPlanet_SkyBox.h"
#include "Default_Aim.h"
#include "BoosterBar.h"
#include "StatusBar.h"
#include "HpBar.h"
#include "ShieldBar.h"
#include "BulletUI.h"
#include "BulletCountUI.h"
#include "Planet_Venus.h"
#include "Planet_Sun.h"
#include "Planet_Red.h"
#include "Planet_Magma.h"
#include "Planet_Exo.h"
#include "Light_Moon.h"
#include "Quest.h"
#include "SpaceDust_PSystem.h"
#include "TextBox.h"
#include <Bomb_Effect.h>
#include "Warring.h"
#include "Dive.h"
#include "Monster.h"
#include "Enemy_TagetBoard.h"
#include "Enemy_StagBeetle.h"
#include "Planet_Select.h"

_bool CLevel_SelectPlanet::m_bFirst = false;

CLevel_SelectPlanet::CLevel_SelectPlanet()
{
}

HRESULT CLevel_SelectPlanet::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;
	
	if (!m_bFirst)
	{
		CGameObject* FPS_Cam = GAMEINSTANCE->Add_GameObject<CCam_FPS>(LEVEL_STATIC, TEXT("Camera"));
		FPS_Cam->Get_Component<CCamera>()->Set_Param(D3DXToRadian(65.0f), (_float)g_iWinCX / g_iWinCY, 0.2f, 900.f);
		GAMEINSTANCE->Register_Camera(TEXT("FPS"), FPS_Cam->Get_Component<CCamera>());

		CGameObject* Shoulder_Cam = GAMEINSTANCE->Add_GameObject<CCam_Shoulder>(LEVEL_STATIC, TEXT("Camera"));
		Shoulder_Cam->Get_Component<CCamera>()->Set_Param(D3DXToRadian(65.0f), (_float)g_iWinCX / g_iWinCY, 0.2f, 900.f);
		GAMEINSTANCE->Register_Camera(TEXT("Shoulder"), Shoulder_Cam->Get_Component<CCamera>());

		CGameObject* TPS_Cam = GAMEINSTANCE->Add_GameObject<CCam_TPS>(LEVEL_STATIC, TEXT("Camera"));
		TPS_Cam->Get_Component<CCamera>()->Set_Param(D3DXToRadian(65.0f), (_float)g_iWinCX / g_iWinCY, 0.2f, 900.f);
		GAMEINSTANCE->Register_Camera(TEXT("TPS"), TPS_Cam->Get_Component<CCamera>());

		CGameObject* Moving_Cam = GAMEINSTANCE->Add_GameObject<CMovingCamera>(LEVEL_STATIC, TEXT("Camera"));
		Moving_Cam->Get_Component<CCamera>()->Set_Param(D3DXToRadian(65.0f), (_float)g_iWinCX / g_iWinCY, 0.2f, 900.f);
		GAMEINSTANCE->Register_Camera(TEXT("Moving"), Moving_Cam->Get_Component<CCamera>());


		//카메라를 다 만들고 나서 비행기의 컨트롤러를 플레이어로 바꾸자.
		GAMEINSTANCE->Add_GameObject<CSong_Ship_Body>(LEVEL_STATIC, TEXT("Player"))->Set_Controller(CONTROLLER::PLAYER);
	}

	m_bFirst = true;
	
	
	if (!GAMEINSTANCE->Add_GameObject<CSelectPlanet_SkyBox>(LEVEL_SELECTPLANET, TEXT("SkyBox")))
		return E_FAIL;

	/*if (!GAMEINSTANCE->Add_GameObject<CDefault_Aim>(LEVEL_SELECTPLANET, TEXT("Aim")))
		return E_FAIL;*/

	if (!GAMEINSTANCE->Add_GameObject<CStatusBar>(LEVEL_SELECTPLANET, TEXT("Status_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CHpBar>(LEVEL_SELECTPLANET, TEXT("HP_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBoosterBar>(LEVEL_SELECTPLANET, TEXT("Booster_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CShieldBar>(LEVEL_SELECTPLANET, TEXT("Shield_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletUI>(LEVEL_SELECTPLANET, TEXT("NormalBullet_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletCountUI>(LEVEL_SELECTPLANET, TEXT("BulletCount_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CLight_Moon>(LEVEL_SELECTPLANET, TEXT("Light_Moon")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CDefault_Aim>(LEVEL_REDPLANET, TEXT("Aim_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CPlanet_Red>(LEVEL_SELECTPLANET, TEXT("Red")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CPlanet_Venus>(LEVEL_SELECTPLANET, TEXT("Venus")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CPlanet_Magma>(LEVEL_SELECTPLANET, TEXT("Magma")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CPlanet_Sun>(LEVEL_SELECTPLANET, TEXT("Sun")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CEnemy_StagBeetle>(LEVEL_SELECTPLANET, TEXT("Enemy_StagBeetle")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CEnemy_TagetBoard>(LEVEL_SELECTPLANET, TEXT("Enemy_TagetBoard")))
		return E_FAIL;


	m_pTextBoxObject = GAMEINSTANCE->Add_GameObject<CTextBox>(LEVEL_SELECTPLANET, TEXT("TextBox_Yang"));
	m_pTextBoxObject->Set_Enable(false);


	m_pQuestBoxObject = GAMEINSTANCE->Add_GameObject<CQuest>(LEVEL_SELECTPLANET, TEXT("Quest_UI"));
	m_pQuestBoxObject->Set_Enable(false);


	((CSpaceDust_PSystem*)GAMEINSTANCE->Add_GameObject<CSpaceDust_PSystem>(LEVEL_SELECTPLANET, TEXT("Particle")))->AddParticle(500);


	
	// 행성 2개 랜덤 생성
	srand(unsigned(time(NULL)));

	LEVEL m_eNextPlanet = LEVEL_STATIC;
	LEVEL m_ePreNextPlanet = m_eNextPlanet;

	for (_uint i = 0; i < 2; ++i)
	{
		m_eNextPlanet = (LEVEL)(rand() % (_uint)LEVEL::LEVEL_SELECTPLANET);

		if (m_eNextPlanet == m_ePreNextPlanet)
		{
			--i;
			continue;
		}
		
		switch (m_eNextPlanet)
		{
		case  LEVEL::LEVEL_REDPLANET:
			if (!GAMEINSTANCE->Add_GameObject<CPlanet_Red>(LEVEL_SELECTPLANET, TEXT("Red")))
				return E_FAIL;
			break;

		case  LEVEL::LEVLE_EXOPLANET:
			if (!GAMEINSTANCE->Add_GameObject<CPlanet_Exo>(LEVEL_SELECTPLANET, TEXT("Exo")))
				return E_FAIL;
			break;

		case  LEVEL::LEVEL_VENUSPLANET:
			if (!GAMEINSTANCE->Add_GameObject<CPlanet_Venus>(LEVEL_SELECTPLANET, TEXT("Venus")))
				return E_FAIL;
			break;

		case  LEVEL::LEVEL_MAGMAPLANET:
			if (!GAMEINSTANCE->Add_GameObject<CPlanet_Magma>(LEVEL_SELECTPLANET, TEXT("Magma")))
				return E_FAIL;
			break;
		}

		m_ePreNextPlanet = m_eNextPlanet;
	}


	


	
	return S_OK;
}

void CLevel_SelectPlanet::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
		
	if (m_bCinematic)
	{
		m_fTime -= fTimeDelta;
		if (0.f > m_fTime)
		{
			m_bCinematic = false;
			GAMEINSTANCE->Swap_Camera();
			if (FAILED(GAMEINSTANCE->Register_OpenLevelEvent(LEVEL_LOADING, CLevel_Loading::Create((LEVEL)m_iNextLevel))))
				return;

			list<CGameObject*>* pLayer = GAMEINSTANCE->Find_Layer(LEVEL_STATIC, TEXT("Player"));
			//for (auto& iter = pLayer->begin(); iter != pLayer->end(); ++iter)
			//{
			//	if (CONTROLLER::PLAYER == (*iter)->Get_Controller())
			//	{
			//		if ((*iter) == nullptr)
			//			break;
			//		//CComponent* Temp = (*iter)->Get_Component<CPlayer_Controller>();
			//		(*iter)->Get_Component<CPlayer_Controller>()->Set_Enable(false);
			//		int i = 10;
			//		//Temp->Set_Enable(false);
			//		
			//	}
			//}
			for (auto& elem : *pLayer)
			{
				if (!elem)
					break;
				
				elem->Set_Controller(CONTROLLER::PLAYER);
			}
		}
	}


	 
	SelectPlanet_Event(fTimeDelta);
	

}

HRESULT CLevel_SelectPlanet::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;


	SetWindowText(g_hWnd, TEXT("Select Planet 레벨입니다. "));
	

	return S_OK;
}

void CLevel_SelectPlanet::Change_Level(void* pArg, _uint _iNextLevel)
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

	_float3	vUp, vLook, vRight,vSpeed;

	pCameraMovingTransform->Set_State(CTransform::STATE_RIGHT, vRight= pCameraTransform->Get_State(CTransform::STATE_RIGHT));
	pCameraMovingTransform->Set_State(CTransform::STATE_UP, vUp= pCameraTransform->Get_State(CTransform::STATE_UP));
	pCameraMovingTransform->Set_State(CTransform::STATE_LOOK, vLook= pCameraTransform->Get_State(CTransform::STATE_LOOK));
	pCameraMovingTransform->Set_State(CTransform::STATE_POSITION, pCameraTransform->Get_State(CTransform::STATE_POSITION));



	static_cast<CMovingCamera*>(Camera_Moving)->Add_Movement(2.f, 0.f,
		*D3DXVec3Normalize(&vSpeed, &(-vLook))*1.5f, _float3(0.f, 0.f, 0.f),
		nullptr, nullptr, 0.1f, 0.f
	);

	static_cast<CMovingCamera*>(Camera_Moving)->Add_Movement(3.f, 0.f,
		_float3(0.f, 0.f, 0.f), *D3DXVec3Normalize(&vSpeed, &(-vLook)) * 4.f,
		nullptr, nullptr, 1.f, 0.05f
	);

}



CLevel_SelectPlanet* CLevel_SelectPlanet::Create()
{
	CLevel_SelectPlanet* pInstance = new CLevel_SelectPlanet();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_SelectPlanet");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_SelectPlanet::Free()
{
	__super::Free();

	delete this;
}

void CLevel_SelectPlanet::SelectPlanet_Event(float fTimeDelta)
{
	m_fTextBoxTime -= fTimeDelta;


	if (m_fTextBoxTime <= 297.f && !m_bEventCheck[0])
	{
		m_pTextBoxObject->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)590 },  D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("우리 행성에 온것을 환영하네. \n각 행성 임무를 통해 다양한 장비를 얻어서 \n비행선을 강화하도록 하게."), 0);
	}

	if (m_fTextBoxTime <= 293.f && !m_bEventCheck[0])
	{
		m_pTextBoxObject->Set_Enable(false);
		m_bEventCheck[0] = true;
	}

	if (m_fTextBoxTime <= 291.f && !m_bEventCheck[1])
	{
		m_pQuestBoxObject->Set_Enable(true);

		GAMEINSTANCE->Add_Text(_point{ (LONG)m_iFontiX, (LONG)60 },  D3DCOLOR_ARGB(255, 0, 204, 255), 0.f, TEXT("            현재 임무  \n행성들을 정복해 비행선 강화하기"), 0);
	  
		m_iFontiX -= 0.8;

		if (m_iFontiX <= 1040)
		{
			m_iFontiX = 1040;
		}
	}

	if (m_bCinematic)
	{
		m_pQuestBoxObject->Set_Enable(false);
		m_bEventCheck[1] = true;
	}
}

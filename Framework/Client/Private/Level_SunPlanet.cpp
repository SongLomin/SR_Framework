#include "stdafx.h"
#include "Level_SunPlanet.h"
#include "GameInstance.h"
#include "VenusPlanet_SkyBox.h"
#include "Default_Aim.h"
#include "Light_Moon.h"
#include "StatusBar.h"
#include "HpBar.h"
#include "ShieldBar.h"
#include "BoosterBar.h"
#include "BulletCountUI.h"
#include "BulletUI.h"
#include <TextBox.h>
#include <Quest.h>
#include <Planet_Select.h>
#include "Level_Loading.h"
#include "MovingCamera.h"
#include <SunSpaceBoss_Body.h>
#include "Boss_HpTable.h"
#include "Boss_HpBar.h"
#include "Boss_Name.h"

CLevel_SunPlanet::CLevel_SunPlanet()
{
}

HRESULT CLevel_SunPlanet::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CVenusPlanet_SkyBox>(LEVEL_SUNPLANET, TEXT("SkyBox")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CDefault_Aim>(LEVEL_SUNPLANET, TEXT("Aim_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CLight_Moon>(LEVEL_SUNPLANET, TEXT("Light_Moon")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CStatusBar>(LEVEL_SUNPLANET, TEXT("Status_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CHpBar>(LEVEL_SUNPLANET, TEXT("HP_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBoosterBar>(LEVEL_SUNPLANET, TEXT("Booster_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CShieldBar>(LEVEL_SUNPLANET, TEXT("Shield_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletUI>(LEVEL_SUNPLANET, TEXT("NormalBullet_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletCountUI>(LEVEL_SUNPLANET, TEXT("BulletCount_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CDefault_Aim>(LEVEL_SUNPLANET, TEXT("Aim")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBossHpTable>(LEVEL_SUNPLANET, TEXT("Boss_HP_Table")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBossName>(LEVEL_SUNPLANET, TEXT("Boss_Name")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBossHpBar>(LEVEL_SUNPLANET, TEXT("Boss_HP_Bar")))
		return E_FAIL;



	m_pTextBoxObject = GAMEINSTANCE->Add_GameObject<CTextBox>(LEVEL_SUNPLANET, TEXT("TextBox_Yang"));
	m_pTextBoxObject->Set_Enable(false);

	m_pQuestBoxObject = GAMEINSTANCE->Add_GameObject<CQuest>(LEVEL_SUNPLANET, TEXT("Quest_UI"));
	m_pQuestBoxObject->Set_Enable(false);


	m_pPlanetObject = GAMEINSTANCE->Add_GameObject<CPlanet_Select>(LEVEL_SUNPLANET, TEXT("Earth"));
	m_pPlanetObject->Set_Enable(false);


	if (!GAMEINSTANCE->Add_GameObject<CSunSpaceBoss_Body>(LEVEL_SUNPLANET, TEXT("Enemy_Boss")))
		return E_FAIL;

	return S_OK;
}

void CLevel_SunPlanet::Tick(_float fTimeDelta)
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

			for (auto& elem : *pLayer)
			{
				if (!elem)
					break;

				elem->Set_Controller(CONTROLLER::PLAYER);
			}
		}
	}


	SunPlanet_Event(fTimeDelta);
}

HRESULT CLevel_SunPlanet::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;


	SetWindowText(g_hWnd, TEXT("Satrun Planet 레벨입니다. "));

	return S_OK;
}

void CLevel_SunPlanet::Change_Level(void* pArg, _uint _iNextLevel)
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

void CLevel_SunPlanet::SunPlanet_Event(_float fTimeDelta)
{
}

CLevel_SunPlanet* CLevel_SunPlanet::Create()
{
	CLevel_SunPlanet* pInstance = new CLevel_SunPlanet();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_SatrunPlanet");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_SunPlanet::Free()
{
	__super::Free();

	delete this;
}

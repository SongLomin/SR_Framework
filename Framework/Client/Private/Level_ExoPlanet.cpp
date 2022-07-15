#include "stdafx.h"
#include "Level_ExoPlanet.h"
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
#include "ExoPlanet_SkyBox.h"

CLevel_ExoPlanet::CLevel_ExoPlanet()
{

}

HRESULT CLevel_ExoPlanet::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;



	
	if (!GAMEINSTANCE->Add_GameObject<CExoPlanet_SkyBox>(LEVLE_EXOPLANET, TEXT("SkyBox")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CDefault_Aim>(LEVLE_EXOPLANET, TEXT("Aim_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CLight_Moon>(LEVLE_EXOPLANET , TEXT("Light_Moon")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CStatusBar>(LEVLE_EXOPLANET, TEXT("Status_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CHpBar>(LEVLE_EXOPLANET, TEXT("HP_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBoosterBar>(LEVLE_EXOPLANET, TEXT("Booster_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CShieldBar>(LEVLE_EXOPLANET, TEXT("Shield_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletUI>(LEVLE_EXOPLANET, TEXT("NormalBullet_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBulletCountUI>(LEVLE_EXOPLANET, TEXT("BulletCount_UI")))
		return E_FAIL;


	return S_OK;
}

void CLevel_ExoPlanet::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);		



	if (m_bCinematic)
	{
		m_fTime -= fTimeDelta;
		//타임 이벤트 어케씀
		if (2.f > m_fTime)
		{
			m_pTagetObject->Get_Component<CRigid_Body>()->Set_Booster(true);

			m_pTagetObject->Get_Component<CRigid_Body>()->Add_Force(1.f * m_pTagetObject->Get_Component<CTransform>()->Get_State(CTransform::STATE_LOOK));
			// 이게 맞냐
			GAMEINSTANCE->Add_Shaking(1.f, 0.1f);
		}

		if (0.f > m_fTime)
		{
			m_bCinematic = false;
			GAMEINSTANCE->Swap_Camera();

			CSong_Ship_Body* pMainCharacter = nullptr;

			list<CGameObject*>* pAiObect = GAMEINSTANCE->Find_Layer(LEVEL_STATIC, TEXT("Player"));

			if (!pAiObect)
				return;

			for (auto& elem : *pAiObect)
			{
				pMainCharacter = dynamic_cast<CSong_Ship_Body*>(elem);

				if (pMainCharacter)
				{
					pMainCharacter->Set_Controller(CONTROLLER::PLAYER);
					break;
				}
			}
		}
	}

	
}

HRESULT CLevel_ExoPlanet::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;


	SetWindowText(g_hWnd, TEXT("Exo Planet 레벨입니다. "));



	return S_OK;
}

void CLevel_ExoPlanet::Change_Level(void* pArg, _uint _iNextLevel)
{

	if (m_bCinematic)
		return;


	m_fTime = 3.f;
	m_bCinematic = true;
	m_iNextLevel = _iNextLevel;

	list<CGameObject*>* pLayer = GAMEINSTANCE->Find_Layer(LEVEL_STATIC, TEXT("Player"));
	for (auto& iter = pLayer->begin(); iter != pLayer->end(); ++iter)
	{
		if (CONTROLLER::PLAYER == (*iter)->Get_Controller())
		{

			if (m_pTagetObject)
				RETURN_WEAKPTR(m_pTagetObject);
			m_pTagetObject = *iter;
			WEAK_PTR(m_pTagetObject);


			(*iter)->Set_Controller(CONTROLLER::LOCK);
			(*iter)->Get_Component<CRigid_Body>()->Reset_Force();

			CComponent* Temp = (*iter)->Get_Component<CRigid_Body>();

			WEAK_PTR(Temp);
			if (pArg)
			{
				Temp = (*iter)->Get_Component<CTransform>();
				static_cast<CTransform*>(Temp)->LookAt((CTransform*)pArg, true);

			}
			RETURN_WEAKPTR(Temp);
		}
	}
	GAMEINSTANCE->Add_Shaking(0.1f, 0.f);
}

CLevel_ExoPlanet* CLevel_ExoPlanet::Create()
{
	CLevel_ExoPlanet* pInstance = new CLevel_ExoPlanet();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_ExoPlanet");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_ExoPlanet::Free()
{
	__super::Free();

	delete this;
}




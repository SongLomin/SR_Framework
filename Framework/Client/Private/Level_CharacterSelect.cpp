#include "stdafx.h"
#include "Level_CharacterSelect.h"
#include "GameInstance.h"
#include "Level_Loading.h"
#include "Song_Ship_Body.h"
#include "Hong_Ship_Body.h"
#include "Shin_Ship_Body.h"
#include "Kang_Ship_Body.h"
#include "MovingCamera.h"
#include "Light_Moon.h"
#include "Math_Utillity.h"
#include "Cam_FPS.h"
#include "Cam_TPS.h"
#include "Cam_Shoulder.h"
#include "CharacterLogo.h"
#include "Benner.h"
#include "Damage_UI.h"
#include "Armor_UI.h"
#include "Speed_UI.h"
#include "Health_UI.h"
#include "Parts_UI.h"
#include "HpBar.h"
#include "SelectShip.h"

_bool	g_bFirst = false;

HRESULT CLevel_CharacterSelect::Initialize()
{
	

	CGameObject* m_pShip = GAMEINSTANCE->Add_GameObject<CSong_Ship_Body>(LEVEL_CHARACTERSELECT, TEXT("Player"));
	m_vecShips.push_back(m_pShip);
	WEAK_PTR(m_vecShips.back());
	m_pShip->Get_Component<CTransform>()->Set_State(CTransform::STATE_POSITION, _float3(-18.f, 0.f, 0.f));
	
	m_pShip = GAMEINSTANCE->Add_GameObject<CShin_Ship_Body>(LEVEL_CHARACTERSELECT, TEXT("Player"));
	m_vecShips.push_back(m_pShip);
	WEAK_PTR(m_vecShips.back());
	m_pShip->Get_Component<CTransform>()->Set_State(CTransform::STATE_POSITION, _float3(-6.f, 0.f, 0.f));

	m_pShip = GAMEINSTANCE->Add_GameObject<CKang_Ship_Body>(LEVEL_CHARACTERSELECT, TEXT("Player"));
	m_vecShips.push_back(m_pShip);
	WEAK_PTR(m_vecShips.back());
	m_pShip->Get_Component<CTransform>()->Set_State(CTransform::STATE_POSITION, _float3(6.f, 0.f, 0.f));
	
	m_pShip = GAMEINSTANCE->Add_GameObject<CHong_Ship_Body>(LEVEL_CHARACTERSELECT, TEXT("Player"));
	m_vecShips.push_back(m_pShip);
	WEAK_PTR(m_vecShips.back());
	m_pShip->Get_Component<CTransform>()->Set_State(CTransform::STATE_POSITION, _float3(18.f, 0.f, 0.f));

	
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


	m_iIndex = -1;

	Moving_Cam = GAMEINSTANCE->Add_GameObject<CMovingCamera>(LEVEL_CHARACTERSELECT, TEXT("Camera"));
	Moving_Cam->Get_Component<CCamera>()->Set_Param(D3DXToRadian(65.0f), (_float)g_iWinCX / g_iWinCY, 0.2f, 900.f);
	GAMEINSTANCE->Register_Camera(TEXT("Moving"), Moving_Cam->Get_Component<CCamera>());
	GAMEINSTANCE->Set_Current_Camera(TEXT("Moving"));

	if (!GAMEINSTANCE->Add_GameObject<CLight_Moon>(LEVEL_CHARACTERSELECT, TEXT("CLight_Moon")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CBenner>(LEVEL_CHARACTERSELECT, TEXT("Benner")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CDamage_UI>(LEVEL_CHARACTERSELECT, TEXT("Damage_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CArmor_UI>(LEVEL_CHARACTERSELECT, TEXT("Armor_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CHealth_UI>(LEVEL_CHARACTERSELECT, TEXT("Health_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CSpeed_UI>(LEVEL_CHARACTERSELECT, TEXT("Speed_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CParts_UI>(LEVEL_CHARACTERSELECT, TEXT("Parts_UI")))
		return E_FAIL;

	if (!GAMEINSTANCE->Add_GameObject<CSelectShip>(LEVEL_CHARACTERSELECT, TEXT("SelectShip_UI")))
		return E_FAIL;

	m_vMovePos = _float3(0.f, 5.f, -25.f);
	GAMEINSTANCE->Get_Camera()->Get_Transform()->Set_State(CTransform::STATE_POSITION, m_vMovePos);
	GAMEINSTANCE->Get_Camera()->Get_Transform()->LookAt(_float3(0.f, 0.f, 0.f));


	GAMEINSTANCE->PlayBGM(TEXT("SelectPlayer.wav"), 0.5f);

	return S_OK;
}

void CLevel_CharacterSelect::Tick(_float fTimeDelta)
{
    __super::Tick(fTimeDelta);
	CGameObject* pPlayer = nullptr;

	m_vecShips[0]->Get_Component<CTransform>()->Turn(_float3(0.f, 1.f, 0.f), D3DXToRadian(60.f), fTimeDelta);
	m_vecShips[1]->Get_Component<CTransform>()->Turn(_float3(0.f, 1.f, 0.f), D3DXToRadian(60.f), fTimeDelta);
	m_vecShips[2]->Get_Component<CTransform>()->Turn(_float3(0.f, 1.f, 0.f), D3DXToRadian(60.f), fTimeDelta);
	m_vecShips[3]->Get_Component<CTransform>()->Turn(_float3(0.f, 1.f, 0.f), D3DXToRadian(60.f), fTimeDelta);
	if(m_bCinematic)
	{ 
		m_fTime -= fTimeDelta;
		GAMEINSTANCE->Sub_FadeOffSet();
		if (0.f > m_fTime)
		{
			switch (m_iIndex)
			{
			case 0:
				pPlayer = GAMEINSTANCE->Add_GameObject<CSong_Ship_Body>(LEVEL_STATIC, TEXT("Player"));
				break;

			case 1:
				pPlayer = GAMEINSTANCE->Add_GameObject<CShin_Ship_Body>(LEVEL_STATIC, TEXT("Player"));
				break;

			case 2:
				pPlayer = GAMEINSTANCE->Add_GameObject<CKang_Ship_Body>(LEVEL_STATIC, TEXT("Player"));
				break;

			case 3:
				pPlayer = GAMEINSTANCE->Add_GameObject<CHong_Ship_Body>(LEVEL_STATIC, TEXT("Player"));
				break;
			}

			pPlayer->Set_Controller(CONTROLLER::PLAYER);
			
			if (FAILED(GAMEINSTANCE->Register_OpenLevelEvent(LEVEL_LOADING, CLevel_Loading::Create((LEVEL)m_iNextLevel))))
				return;
		}
	}
	else
	{
		GAMEINSTANCE->Add_FadeOffSet();


		if (KEY_INPUT(KEY::LEFT, KEY_STATE::TAP) /* || 버튼 눌렀을 때*/)
		{
			GAMEINSTANCE->PlaySoundW(TEXT("Select.wav"), 1.f);

			if (0 > m_iIndex)//처음
			{
				m_iIndex = 0;
				m_vMovePos = m_vecShips[m_iIndex]->Get_Component<CTransform>()->Get_State(CTransform::STATE_POSITION);
				m_vMovePos += _float3(0.f, 5.f, -15.f);
			}
			else if (0 < m_iIndex)
			{
				--m_iIndex;
				m_vMovePos = m_vecShips[m_iIndex]->Get_Component<CTransform>()->Get_State(CTransform::STATE_POSITION);
				m_vMovePos += _float3(0.f, 5.f, -15.f);
			}
		}

		if (KEY_INPUT(KEY::RIGHT, KEY_STATE::TAP)/* || 버튼 눌렀을 때*/)
		{
			GAMEINSTANCE->PlaySoundW(TEXT("Select.wav"), 1.f);

			if (0 > m_iIndex)//처음
			{
				m_iIndex = m_vecShips.size() - 1;
				m_vMovePos = m_vecShips[m_iIndex]->Get_Component<CTransform>()->Get_State(CTransform::STATE_POSITION);
				m_vMovePos += _float3(0.f, 5.f, -15.f);
			}
			else if (m_vecShips.size() - 1 > m_iIndex)
			{
				++m_iIndex;
				m_vMovePos = m_vecShips[m_iIndex]->Get_Component<CTransform>()->Get_State(CTransform::STATE_POSITION);
				m_vMovePos += _float3(0.f, 5.f, -15.f);
			}
		}

	if (KEY_INPUT(KEY::SPACE, KEY_STATE::TAP) /* || 버튼 눌렀을 때*/)
	{
		
		GAMEINSTANCE->PlaySoundW(TEXT("Start.wav"), 0.5f);

			if (-1 != m_iIndex)
			{
				if (g_bFirst)
				{
					Change_Level(nullptr, LEVEL::LEVEL_SELECTPLANET);
				}
				else
				{
					g_bFirst = true;
					Change_Level(nullptr, LEVEL::LEVEL_VENUSPLANET);
				}
				
			}
		}


		_float3 vCameraCurPos = GAMEINSTANCE->Get_Camera()->Get_Transform()->Get_State(CTransform::STATE_POSITION);
		vCameraCurPos = CMath_Utillity::vecLerp(vCameraCurPos, m_vMovePos, 0.03f);
		GAMEINSTANCE->Get_Camera()->Get_Transform()->Set_State(CTransform::STATE_POSITION, vCameraCurPos);

		GAMEINSTANCE->Get_Camera()->Get_Transform()->Update_WorldMatrix();

	}

}

HRESULT CLevel_CharacterSelect::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;
	SetWindowText(g_hWnd, TEXT("캐릭터 선택 레벨입니다. "));

    return S_OK;
}

void CLevel_CharacterSelect::Change_Level(void* pArg, _uint _iNextLevel)
{
	m_bCinematic = true;
	m_fTime = 1.f;
	m_iNextLevel = _iNextLevel;
}


CLevel_CharacterSelect* CLevel_CharacterSelect::Create()
{
	CLevel_CharacterSelect* pInstance = new CLevel_CharacterSelect();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_CharacterSelect");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel_CharacterSelect::Free()
{
	__super::Free();

	/*if (!m_vecShips.empty())
	{
		for (auto& elem : m_vecShips)
		{
			RETURN_WEAKPTR(elem);
		}

	}*/

	delete this;
}

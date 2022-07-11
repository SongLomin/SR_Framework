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

HRESULT CLevel_CharacterSelect::Initialize()
{
	CGameObject* m_pShip = GAMEINSTANCE->Add_GameObject<CSong_Ship_Body>(LEVEL_CHARACTERSELECT, TEXT("Player"));
	m_vecShips.push_back(m_pShip);
	WEAK_PTR(m_vecShips.back());
	m_pShip->Get_Component<CTransform>()->Set_State(CTransform::STATE_POSITION, _float3(-10.f, 0.f, 0.f));
	
	m_pShip = GAMEINSTANCE->Add_GameObject<CKang_Ship_Body>(LEVEL_CHARACTERSELECT, TEXT("Player"));
	m_vecShips.push_back(m_pShip);
	WEAK_PTR(m_vecShips.back());
	m_pShip->Get_Component<CTransform>()->Set_State(CTransform::STATE_POSITION, _float3(10.f, 0.f, 0.f));
	
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


	m_iIndex = 0;

	Moving_Cam = GAMEINSTANCE->Add_GameObject<CMovingCamera>(LEVEL_CHARACTERSELECT, TEXT("Camera"));
	Moving_Cam->Get_Component<CCamera>()->Set_Param(D3DXToRadian(65.0f), (_float)g_iWinCX / g_iWinCY, 0.2f, 900.f);
	GAMEINSTANCE->Register_Camera(TEXT("Moving"), Moving_Cam->Get_Component<CCamera>());
	GAMEINSTANCE->Set_Current_Camera(TEXT("Moving"));

	if (!GAMEINSTANCE->Add_GameObject<CLight_Moon>(LEVEL_CHARACTERSELECT, TEXT("CLight_Moon")))
		return E_FAIL;

	m_vMovePos = _float3(0.f, 5.f, -20.f);
	GAMEINSTANCE->Get_Camera()->Get_Transform()->Set_State(CTransform::STATE_POSITION, m_vMovePos);
	GAMEINSTANCE->Get_Camera()->Get_Transform()->LookAt(_float3(0.f, 0.f, 0.f));
	return S_OK;
}

void CLevel_CharacterSelect::Tick(_float fTimeDelta)
{
    __super::Tick(fTimeDelta);

	m_vecShips[0]->Get_Component<CTransform>()->Turn(_float3(0.f, 1.f, 0.f), D3DXToRadian(60.f), fTimeDelta);
	m_vecShips[1]->Get_Component<CTransform>()->Turn(_float3(0.f, 1.f, 0.f), D3DXToRadian(60.f), fTimeDelta);


	if (KEY_INPUT(KEY::LEFT, KEY_STATE::TAP) /* || 버튼 눌렀을 때*/)
	{
		if (0 < m_iIndex)
		{
			--m_iIndex;
			m_vMovePos = m_vecShips[m_iIndex]->Get_Component<CTransform>()->Get_State(CTransform::STATE_POSITION);
			m_vMovePos += _float3(0.f, 5.f, -15.f);
		}
	}

	if (KEY_INPUT(KEY::RIGHT, KEY_STATE::TAP)/* || 버튼 눌렀을 때*/)
	{
		if (m_vecShips.size()-1 > m_iIndex)
		{
			++m_iIndex;
			m_vMovePos = m_vecShips[m_iIndex]->Get_Component<CTransform>()->Get_State(CTransform::STATE_POSITION);
			m_vMovePos += _float3(0.f, 5.f, -15.f);
		}
	}

	if (KEY_INPUT(KEY::SPACE, KEY_STATE::TAP) /* || 버튼 눌렀을 때*/)
	{
		CGameObject* pPlayer = nullptr;
		switch (m_iIndex)
		{
		case 0:
			
			pPlayer = GAMEINSTANCE->Add_GameObject<CSong_Ship_Body>(LEVEL_STATIC, TEXT("Player"));
			break;
			
		case 1:
			pPlayer = GAMEINSTANCE->Add_GameObject<CKang_Ship_Body>(LEVEL_STATIC, TEXT("Player"));
			break;
		}

		pPlayer->Set_Controller(CONTROLLER::PLAYER);
		if (FAILED(GAMEINSTANCE->Register_OpenLevelEvent(LEVEL_LOADING, CLevel_Loading::Create(LEVEL::LEVEL_SELECTPLANET))))
			return;
	}

	
	_float3 vCameraCurPos = GAMEINSTANCE->Get_Camera()->Get_Transform()->Get_State(CTransform::STATE_POSITION);
	vCameraCurPos = CMath_Utillity::vecLerp(vCameraCurPos, m_vMovePos, 0.03f);
	GAMEINSTANCE->Get_Camera()->Get_Transform()->Set_State(CTransform::STATE_POSITION, vCameraCurPos);

	GAMEINSTANCE->Get_Camera()->Get_Transform()->Update_WorldMatrix();

	CharacterSelect_Event();//UI정리해놓음

}

HRESULT CLevel_CharacterSelect::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;
	SetWindowText(g_hWnd, TEXT("캐릭터 선택 레벨입니다. "));

    return S_OK;
}

void CLevel_CharacterSelect::CharacterSelect_Event()
{
	/*UI띄워야함*/
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

	delete this;
}

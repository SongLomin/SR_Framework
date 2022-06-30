#include "Player_Controller.h"
#include "GameInstance.h"
#include "GameObject.h"

CPlayer_Controller::CPlayer_Controller()
{
}

CPlayer_Controller::CPlayer_Controller(const CPlayer_Controller& Prototype)
{
	*this = Prototype;
}

HRESULT CPlayer_Controller::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CPlayer_Controller::Initialize(void* pArg)
{
	return S_OK;
}

void CPlayer_Controller::Tick(_float fTimeDelta)
{
	if (Get_Enable())
	{
		if (KEY_INPUT(KEY::W, KEY_STATE::HOLD))
			m_pObject->Get_Component<CRigid_Body>()->Add_Dir(CRigid_Body::FRONT);
		if (KEY_INPUT(KEY::S, KEY_STATE::HOLD))
			m_pObject->Get_Component<CRigid_Body>()->Add_Dir(CRigid_Body::BACK);
		if (KEY_INPUT(KEY::D, KEY_STATE::HOLD))
			m_pObject->Get_Component<CRigid_Body>()->Add_Dir(CRigid_Body::RIGHT);
		if (KEY_INPUT(KEY::A, KEY_STATE::HOLD))
			m_pObject->Get_Component<CRigid_Body>()->Add_Dir(CRigid_Body::LEFT);


		

		POINT pt{};
		GetCursorPos(&pt);
		ScreenToClient(GAMEINSTANCE->Get_Graphic_Desc().hWnd, &pt);

		_float fDirX = pt.x - GAMEINSTANCE->Get_Graphic_Desc().iWinCX * 0.5f;
		_float fDirY = pt.y - GAMEINSTANCE->Get_Graphic_Desc().iWinCY * 0.5f;
		m_pObject->Get_Component<CRigid_Body>()->Add_Dir(CRigid_Body::SPIN, fDirX * 0.1f);
		m_pObject->Get_Component<CRigid_Body>()->Add_Dir(CRigid_Body::DOWN, fDirY * 0.1f);

		if (KEY_INPUT(KEY::SPACE, KEY_STATE::TAP))//testing Camera Shaking
		{
			GAMEINSTANCE->Add_Shaking(2.f, 0.01f);
		}


		if (KEY_INPUT(KEY::Z, KEY_STATE::TAP))
		{
			//m_pStatusCom->Add_Status(CStatus::STATUSID::STATUS_HP, -1.f);
		}

		if (KEY_INPUT(KEY::V, KEY_STATE::TAP))
		{
			switch (m_iCurrentCam)
			{
			case 0:
				GAMEINSTANCE->Set_Current_Camera(TEXT("Shoulder"));
				break;

			case 1:
				GAMEINSTANCE->Set_Current_Camera(TEXT("FPS"));
				break;

			case 2:
				GAMEINSTANCE->Set_Current_Camera(TEXT("TPS"));
				break;
			}

			m_iCurrentCam = (m_iCurrentCam + 1) % 3;
		}


		if (KEY_INPUT(KEY::TAB, KEY_STATE::TAP))
		{
			//m_bTargetMode = !m_bTargetMode;
		}

		m_fTime -= fTimeDelta;
		if (m_fTime < 0.f)
		{
			m_pObject->Get_Component<CTargeting>()->Make_Player_TargetList(GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("EnemySpace_Body")));
			m_fTime = 1.f;
		}
	}
}

void CPlayer_Controller::LateTick(_float fTimeDelta)
{
}


CPlayer_Controller* CPlayer_Controller::Create()
{
	CREATE_PIPELINE(CPlayer_Controller);
}

CController* CPlayer_Controller::Clone(void* pArg)
{
	CLONE_PIPELINE(CPlayer_Controller);
}

void CPlayer_Controller::Free()
{
	__super::Free();

	delete this;
}

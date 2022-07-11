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
		if (m_bLock)
		{
			m_pMyObject->Get_Component<CRigid_Body>()->Reset_Force();
			return;
		}
			

		if (KEY_INPUT(KEY::W, KEY_STATE::HOLD))
			m_pMyObject->Get_Component<CRigid_Body>()->Add_Dir(CRigid_Body::FRONT);
		if (KEY_INPUT(KEY::S, KEY_STATE::HOLD))
			m_pMyObject->Get_Component<CRigid_Body>()->Add_Dir(CRigid_Body::BACK);
		if (KEY_INPUT(KEY::D, KEY_STATE::HOLD))
			m_pMyObject->Get_Component<CRigid_Body>()->Add_Dir(CRigid_Body::RIGHT);
		if (KEY_INPUT(KEY::A, KEY_STATE::HOLD))
			m_pMyObject->Get_Component<CRigid_Body>()->Add_Dir(CRigid_Body::LEFT);
		

		POINT pt{};
		GetCursorPos(&pt);
		ScreenToClient(GAMEINSTANCE->Get_Graphic_Desc().hWnd, &pt);

		_float fDirX = pt.x - GAMEINSTANCE->Get_Graphic_Desc().iWinCX * 0.5f;
		_float fDirY = pt.y - GAMEINSTANCE->Get_Graphic_Desc().iWinCY * 0.5f;
		m_pMyObject->Get_Component<CRigid_Body>()->Add_Dir(CRigid_Body::SPIN, fDirX * 0.1f);
		m_pMyObject->Get_Component<CRigid_Body>()->Add_Dir(CRigid_Body::DOWN, fDirY * 0.1f);

	
		if (KEY_INPUT(KEY::V, KEY_STATE::TAP))
		{
			switch (m_iCurrentCam)
			{
			case 0:

				GAMEINSTANCE->Switch_Camera(TEXT("Shoulder"),0.2f);
				break;

			case 1:
				GAMEINSTANCE->Switch_Camera(TEXT("FPS"),0.2f);
				break;

			case 2:
				GAMEINSTANCE->Switch_Camera(TEXT("TPS"),0.2f);
				break;

			}

			m_iCurrentCam = (m_iCurrentCam + 1) % 3;
		}

		if (KEY_INPUT(KEY::LBUTTON, KEY_STATE::HOLD))
		{
			wstring Message = TEXT("Fire");
			Get_Owner()->Broadcast_EventMessage(&Message);
		}

		m_fTime -= fTimeDelta;
		if (m_fTime < 0.f)
		{
			m_pMyObject->Get_Component<CTargeting>()->Make_TargetList_Cursor(GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("EnemySpace_Body")), m_pMyObject->Get_Component<CTransform>());
			m_pMyObject->Get_Component<CTargeting>()->Make_TargetList_Cursor(GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("Enemy_StagBeetle")), m_pMyObject->Get_Component<CTransform>());
			m_pMyObject->Get_Component<CTargeting>()->Make_TargetList_Cursor(GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("Enemy_TagetBoard")), m_pMyObject->Get_Component<CTransform>());
			m_fTime = 1.f;
		}

		if (KEY_INPUT(KEY::TAB, KEY_STATE::TAP))
		{
			switch (m_iCurrent_TargetMode)
			{
			case 0:
				m_pMyObject->Get_Component<CTargeting>()->Set_TargetMode(TARGETMODE::TARGET_SINGLE);
				break;

			case 1:
				m_pMyObject->Get_Component<CTargeting>()->Set_TargetMode(TARGETMODE::TARGET_MULTIRAY);
				break;

			case 2:
				m_pMyObject->Get_Component<CTargeting>()->Set_TargetMode(TARGETMODE::TARGET_MULTIWIDE);
				break;
			}
			m_iCurrent_TargetMode = (m_iCurrent_TargetMode + 1) % 3;
		}


		CCamera* pCurrentCam = GAMEINSTANCE->Get_Camera();
		ISVALID(pCurrentCam, );
		CTransform* TransformCom = pCurrentCam->Get_Target();

		if (TransformCom)
		{
			CStatus* pPlayerStatusCom = TransformCom->Get_Owner()->Get_Component<CStatus>();
			_float fBooster = pPlayerStatusCom->Get_Status().fBooster;
		
		if (fBooster >= 2.f && KEY_INPUT(KEY::LSHIFT, KEY_STATE::HOLD))
		{
			m_pMyObject->Get_Component<CRigid_Body>()->Set_Booster(true);
			GAMEINSTANCE->Add_Shaking(0.2f, 0.01f);	
			pPlayerStatusCom->Add_Status(CStatus::STATUSID::STATUS_BOOSTER, -0.05);
		}

		else
		{
			
			m_pMyObject->Get_Component<CRigid_Body>()->Set_Booster(false);
		}

		}
	}
}

void CPlayer_Controller::LateTick(_float fTimeDelta)
{
	if (!Get_Enable())
	{
		m_pMyObject->Get_Component<CRigid_Body>()->Set_Booster(false);
	}
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

#include "AI_Controller.h"
#include "GameInstance.h"
#include "GameObject.h"

CAI_Controller::CAI_Controller()
{
}

CAI_Controller::CAI_Controller(const CAI_Controller& Prototype)
{
	*this = Prototype;
}

HRESULT CAI_Controller::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CAI_Controller::Initialize(void* pArg)
{
	return S_OK;
}

void CAI_Controller::Tick(_float fTimeDelta)
{
	if (Get_Enable())
	{
		if (!m_pMyTargeting)
			return;

		map<_float, CGameObject*>* TargetList = m_pMyTargeting->Get_Targetting();

		if (TargetList->empty())
		{
			m_pMyState_Move->State_Tick(m_pMyTransform, fTimeDelta);
		}
		else
		{
			CGameObject* Target = TargetList->begin()->second;
			if (!Target)
			{
				return;
			}
			m_pMyState_Move->State_Tagetting(Target->Get_Component<CTransform>(), fTimeDelta, 7.f);
		}
	}
}

void CAI_Controller::LateTick(_float fTimeDelta)
{
}

void CAI_Controller::OnEnable(void* pArg)
{
	m_pMyState_Move = m_pOwner->Get_Component<CState_Move>();
	WEAK_PTR(m_pMyState_Move);
	m_pMyTransform = m_pOwner->Get_Component<CTransform>();
	WEAK_PTR(m_pMyTransform);
	m_pMyTargeting = m_pOwner->Get_Component<CTargeting>();
	WEAK_PTR(m_pMyTargeting);
}

void CAI_Controller::OnDisable()
{
	RETURN_WEAKPTR(m_pMyState_Move);
	m_pMyState_Move = nullptr;
	RETURN_WEAKPTR(m_pMyTransform);
	m_pMyTransform = nullptr;
	RETURN_WEAKPTR(m_pMyTargeting);
	m_pMyTargeting = nullptr;
}

CAI_Controller* CAI_Controller::Create()
{
	CREATE_PIPELINE(CAI_Controller);
}

CController* CAI_Controller::Clone(void* pArg)
{
	CLONE_PIPELINE(CAI_Controller);
}

void CAI_Controller::Free()
{
	__super::Free();

	delete this;
}

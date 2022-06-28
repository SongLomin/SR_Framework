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
		map<_float, CGameObject*>* TargetList = m_pObject->Get_Component<CTargeting>()->Get_Targetting();

		if (TargetList->empty())
		{
			CState_Move* State = m_pObject->Get_Component<CState_Move>();
			CTransform* Transform = m_pObject->Get_Component<CTransform>();
			State->State_Change(Transform, fTimeDelta);
		}
		else
		{
			CGameObject* Target = TargetList->begin()->second;
			if (!Target)
			{
				return;
			}
			m_pObject->Get_Component<CState_Move>()->State_Tagetting(Target->Get_Component<CTransform>(), fTimeDelta, 7.f);
		}
	}
}

void CAI_Controller::LateTick(_float fTimeDelta)
{
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

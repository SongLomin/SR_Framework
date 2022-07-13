#include "AI_Controller.h"
#include "GameInstance.h"
#include "GameObject.h"
#include "Math_Utillity.h"


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

void CAI_Controller::Set_UsableStates(const vector<STATE>& _eUsableStates)
{
	for (size_t i = 0; i < _eUsableStates.size(); i++)
	{
		//인덱스 번호에 맞게 상태를 분류한다. 분류 단위는 100단위.
		m_eUsableStates[(_uint)_eUsableStates[i] / 100].push_back(_eUsableStates[i]);
	}

	int i = 0;
}

void CAI_Controller::Push_Front_Command(STATE _eStates, _float _BehaviorTime, _bool _IsClearCommand)
{
	if (_BehaviorTime < 0.f)
	{
		_BehaviorTime = m_fBehaviorTime;
	}

	if (_IsClearCommand)
	{
		m_CommandQueue.clear();
	}

	m_CommandQueue.push_back({ _eStates, _BehaviorTime });
}

vector<STATE> CAI_Controller::Get_States_Preset_AI_Default()
{
	vector<STATE> states{
		STATE::MOVETARGET_BACK,
		STATE::MOVETARGET_CHASE,
		STATE::MOVETARGET_LSPIN,
		STATE::MOVETARGET_RSPIN,
		STATE::MOVE_DOWN_FRONT,
		STATE::MOVE_JUMP_FRONT,
		STATE::MOVE_LIFT_BACK,
		STATE::MOVE_LIFT_FRONT,
		STATE::MOVE_UPPER_LEFT,
		STATE::MOVE_UPPER_RIGHT,
		//STATE::MOVETAGET_CHASE_PLAYER
	};

	return states;
}

void CAI_Controller::Tick(_float fTimeDelta)
{
	if (!Get_Enable())
		return;

	//커맨드 큐가 비어 있으면 다음 행동을 알려준다.
	if (m_CommandQueue.empty())
	{
		STATE eCurState = STATE::STATE_NONE;

		if (m_pMyTargeting)
		{
			map<_float, CGameObject*>* TargetList = m_pMyTargeting->Get_Targetting();

			if (!TargetList->empty())
			{
				CGameObject* Target = TargetList->begin()->second;

				if (Target)
				{
					eCurState = Command_MoveTarget();
					m_pMyState_Move->Set_TargetTransform(Target->Get_Component<CTransform>());
				}
			}
		}

		if (STATE::STATE_NONE == eCurState)
		{
			eCurState = Command_Move();
		}

		m_CommandQueue.push_back({ eCurState, m_fBehaviorTime });
	}

	//커맨드 큐에서 가장 앞 순서의 상태를 확인한다.
	m_pMyState_Move->Set_State(m_CommandQueue.front().first);

	//지속 시간이 다 된 상태는 꺼낸다.
	if (m_CommandQueue.front().second < 0.f)
	{
		m_CommandQueue.pop_front();
	} else
	{
		m_CommandQueue.front().second -= fTimeDelta;
	}
	
}

void CAI_Controller::LateTick(_float fTimeDelta)
{
}

STATE CAI_Controller::Command_MoveTarget()
{
	STATE eCurState = CMath_Utillity::Get_Random_Value_In_Vector<STATE>(m_eUsableStates[STATE_TYPE::STATE_MOVETARGET]);

	return eCurState;
}

STATE CAI_Controller::Command_Move()
{
	STATE eCurState = CMath_Utillity::Get_Random_Value_In_Vector<STATE>(m_eUsableStates[STATE_TYPE::STATE_MOVE]);

	return eCurState;
}

STATE CAI_Controller::Command_Attack()
{


	return STATE();
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

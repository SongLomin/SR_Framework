#pragma once
#include "Controller.h"

BEGIN(Engine)

class CState_Move;
class CTransform;
class CTargeting;

class ENGINE_DLL CAI_Controller final : public CController
{
public:
	CAI_Controller();
	CAI_Controller(const CAI_Controller& Prototype);
	virtual ~CAI_Controller() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);

public:
	//해당 컨트롤러가 사용할 수 있는 State 리스트를 넣어준다. 종류별로 해당 리스트 내에서 랜덤하게 행동한다.
	void Set_UsableStates(const vector<STATE>& _eUsableStates);
	//현재 명령 큐의 앞에 상태를 삽입한다. 
	//_BehaviorTime의 값이 음수라면 디폴트 행동 시간을 사용한다.
	//_IsClearCommand는 기존에 등록되어 있는 커맨드들을 삭제할 지 여부다.
	void Push_Front_Command(STATE _eStates, _float _BehaviorTime = -1.f, _bool _IsClearCommand = false);

public: //행동 프리셋
	vector<STATE> Get_States_Preset_AI_Default();
	vector<STATE> Get_States_Preset_ROLLER_Default();

public:
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);

private:
	CState_Move* m_pMyState_Move = nullptr;
	CTransform* m_pMyTransform = nullptr;
	CTargeting* m_pMyTargeting = nullptr;

private:
	STATE Command_MoveTarget();
	STATE Command_Move();
	STATE Command_Attack();

protected:
	list<pair<STATE, _float>> m_CommandQueue;
	vector<STATE> m_eUsableStates[9];

	_float m_fBehaviorTime = 3.f;

public:
	//객체의 상태가 활성화 상태로 변경될 때, 호출되는 이벤트입니다.
	virtual void OnEnable(void* pArg = nullptr) override;

	//객체의 상태가 비활성화 상태로 변경될 때, 호출되는 이벤트입니다.
	virtual void OnDisable() override;

private:

public:
	static CAI_Controller* Create();
	virtual CController* Clone(void* pArg) override;
	virtual void Free() override;
};

END
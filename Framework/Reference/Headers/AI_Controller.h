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
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);

private:
	CState_Move* m_pMyState_Move = nullptr;
	CTransform* m_pMyTransform = nullptr;
	CTargeting* m_pMyTargeting = nullptr;

public:
	//객체의 상태가 활성화 상태로 변경될 때, 호출되는 이벤트입니다.
	virtual void OnEnable(void* pArg = nullptr) override;

	//객체의 상태가 비활성화 상태로 변경될 때, 호출되는 이벤트입니다.
	virtual void OnDisable() override;

public:
	static CAI_Controller* Create();
	virtual CController* Clone(void* pArg) override;
	virtual void Free() override;
};

END
#pragma once

#include "Client_Defines.h"
#include "State.h"

BEGIN(Engine)

class CTransform;
class CRigid_Body;

END

BEGIN(Client)

class CState_Move final : public CState
{

private:
	CState_Move() = default;
	CState_Move(const CState_Move& Prototype);
	virtual ~CState_Move() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	void State_Start(_float fSpeedValue);
	void State_1(_float* fCountTime);
	void State_2(_float* fCountTime);
	void State_3(_float* fCountTime);
	void State_4(_float* fCountTime);
	void State_5(_float* fCountTime);

public:
	void State_Change(_float* fCountTime, _bool bStateCheck);


public:
	CRigid_Body* m_pRigidBody = nullptr;

public:
	
	STATE_MOVE    m_ePreMovement = STATE_MOVE::STATE_END;
	STATE_MOVE    m_eCurMovement = STATE_MOVE::STATE_END;
	

public:
	virtual CState* Clone(void* pArg) override;
	virtual void Free() override;

};

END


#pragma once

#include "Component.h"

BEGIN(Engine)

class CTransform;
class CRigid_Body;

class ENGINE_DLL CState : public CComponent
{
	
private:
	CState() = default;
	CState(const CState& Prototype);
	virtual ~CState() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Tick(_float fTimeDelta);

public:
	void State_Start(_float fSpeedValue);
	void State_1(_float fSpeedValue, _float* fCountTime);
	void State_2(_float fSpeedValue, _float* fCountTime);
	void State_3(_float fSpeedValue, _float* fCountTime);
	void State_4(_float fSpeedValue, _float* fCountTime);
	void State_5(_float fSpeedValue, _float* fCountTime);

public:
	void State_Change(_float fSpeedValue, _float* fCountTime, _bool bStateCheck);
	void Link_RigidBodyCom(CRigid_Body* pRigidBody);
	
	
private:
	CRigid_Body* m_pRigidBody = nullptr;

public:
	_float   m_fSpeedValue = 0.f;
	_float	 m_fCountTime = 0.f;
	STATE    m_ePreMovement = STATE::STATE_END;
	STATE    m_eCurMovement = STATE::STATE_END;
	bool     m_bStateCheck = false;

public:
	static CState* Create();
	virtual	CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END


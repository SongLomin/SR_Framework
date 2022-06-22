#pragma once

#include "Component.h"

BEGIN(Engine)

class CTransform;
class CRigid_Body;

class ENGINE_DLL CState : public CComponent
{
	
protected:
	CState() = default;
	CState(const CState& Prototype);
	virtual ~CState() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Tick(_float fTimeDelta);

public:
	void State_Start(_float fSpeedValue, _float fCountTime);
	void State_1(_float fSpeedValue, _float fCountTime);
	void State_2(_float fSpeedValue, _float fCountTime);
	void State_3(_float fSpeedValue, _float fCountTime);
	void State_4(_float fSpeedValue, _float fCountTime);
	void State_5(_float fSpeedValue, _float fCountTime);

public:
	void State_Change(_float fSpeedValue, _float fCountTime, STATE _eState);
	void Link_RigidBodyCom(CRigid_Body* pRigidBody);
	
	
protected:
	CRigid_Body* m_pRigidBody = nullptr;

protected:
	_float   m_fSpeedValue = 0.f;
	_float	 m_fCountTime = 0.f;
	STATE    m_ePreMovement = STATE::STATE_END;
	STATE    m_eCurMovement = STATE::STATE_END;
	bool     m_bMoveMentCheck = false;

public:
	static CState* Create();
	virtual	CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END


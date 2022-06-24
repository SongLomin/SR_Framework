#pragma once

#include "Component.h"

BEGIN(Engine)

class CTransform;
class CRigid_Body;

class ENGINE_DLL CState abstract : public CComponent
{
	
protected:
	CState() = default;
	CState(const CState& Prototype);
	virtual ~CState() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual void Tick(_float fTimeDelta) {};
	virtual void LateTick(_float fTimeDelta) {};
	virtual HRESULT Render() { return S_OK; };

public:
	void Link_RigidBodyCom(CRigid_Body* pRigidBody);

protected:
	CRigid_Body* m_pRigidBody = nullptr;

protected:
	_float   m_fSpeedValue = 0.f;
	_float	 m_fCountTime = 0.f;
	bool     m_bStateCheck = false;
	STATE    m_eState;

public: 
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END


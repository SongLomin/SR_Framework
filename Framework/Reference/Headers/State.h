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
	void Link_RigidBody(CRigid_Body* pRigidBody);
	void Link_AiTransform(CTransform* m_pAiTransform);

protected:
	CRigid_Body* m_pRigidBody = nullptr;
	CTransform* m_pTransform = nullptr;
	CTransform* m_pAiTransform = nullptr;
	CTransform* m_pPosinTransform = nullptr;
	CTransform* m_pBulletTransform = nullptr;

protected:
	_float	 m_fCurTime = 0.f;
	_float	 m_fMaxTime = 1.f;
	bool     m_bStateCheck = true;

public: 
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END


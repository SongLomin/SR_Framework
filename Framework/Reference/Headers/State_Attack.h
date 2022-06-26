#pragma once

#include "State.h"

BEGIN(Engine)

class CTransform;
class CRigid_Body;

class ENGINE_DLL CState_Attack final : public CState
{

private:
	CState_Attack() = default;
	CState_Attack(const CState_Attack& Prototype);
	virtual ~CState_Attack() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual void Tick(_float fTimeDelta) {};
	virtual void LateTick(_float fTimeDelta) {};
	virtual HRESULT Render() { return S_OK; };

public:
	void Attack_Bullet(_float fTimeDelta);
	void Attack_Rager(_float fTimeDelta);
	void Attack_Rest(_float fTimeDelta);

public:
	void State_Change(CTransform* pPlayerTransform, _float fTimeDelta);
	void Link_RigidBody(CRigid_Body* pRigidBody);
	void Link_Transform(CTransform* pTransform);

public:
	CRigid_Body* m_pRigidBody = nullptr;
	CTransform* m_pTransform = nullptr;
	CTransform* m_pPlayerTransform = nullptr;

public:

	STATE_ATTACK    m_ePreState = STATE_ATTACK::ATTACK_END;
	STATE_ATTACK    m_eCurState = STATE_ATTACK::ATTACK_BULLET;


public:
	static CState_Attack* Create();
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;

};

END


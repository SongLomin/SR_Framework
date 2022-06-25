#pragma once


#include "State.h"

BEGIN(Engine)

class CTransform;
class CRigid_Body;

class ENGINE_DLL CState_Move final : public CState
{

private:
	CState_Move() = default;
	CState_Move(const CState_Move& Prototype);
	virtual ~CState_Move() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual void Tick(_float fTimeDelta) {};
	virtual void LateTick(_float fTimeDelta) {};
	virtual HRESULT Render() { return S_OK; };

public:
	void State_Start(_float fTimeDelta);
	void State_1(_float fTimeDelta);
	void State_2(_float fTimeDelta);
	void State_3(_float fTimeDelta);
	void State_4(_float fTimeDelta);
	void State_5(_float fTimeDelta);
	void State_6(CTransform* pPlayerTransform, _float fTimeDelta);

public:
	void State_Change(CTransform* pPlayerTransform, _float fTimeDelta);
	void Link_RigidBody(CRigid_Body* pRigidBody);
	void Link_Transform(CTransform* pTransform);

public:
	CRigid_Body* m_pRigidBody = nullptr;
	CTransform* m_pTransform = nullptr;
	CTransform* m_pPlayerTransform = nullptr;

public:

	STATE_MOVE    m_ePreState = STATE_MOVE::STATE_END;
	STATE_MOVE    m_eCurState = STATE_MOVE::STATE_6;


public:
	static CState_Move* Create();
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;

};



END

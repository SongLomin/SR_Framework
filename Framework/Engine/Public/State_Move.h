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

public:
	void State_Change(_float fTimeDelta);
	void Link_RigidBody(CRigid_Body* pRigidBody);

public:
	CRigid_Body* m_pRigidBody = nullptr;

public:

	STATE_MOVE    m_ePreState = STATE_MOVE::STATE_END;
	STATE_MOVE    m_eCurState = STATE_MOVE::STATE_END;


public:
	static CState_Move* Create();
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;

};



END

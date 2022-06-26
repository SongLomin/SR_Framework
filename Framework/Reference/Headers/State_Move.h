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
	void Move_Upper_Right();
	void Move_Upper_Left();
	void Move_Down_Front();
	void Move_Lift_Front();
	void Move_Lift_Back();
	void Move_Jump_Front();
	void Move_Chase_Player(CTransform* pPlayerTransform, _float fTimeDelta);

public:
	void State_Change(CTransform* pPlayerTransform, _float fTimeDelta);

public:

	STATE_MOVE    m_ePreState = STATE_MOVE::STATE_END;
	STATE_MOVE    m_eCurState = STATE_MOVE::MOVE_UPPER_RIGHT;


public:
	static CState_Move* Create();
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;

};



END

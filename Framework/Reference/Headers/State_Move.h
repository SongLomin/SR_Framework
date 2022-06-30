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
	void MoveTarget_Chase(CTransform* pTargetTransform, _float fTimeDelta, _float fLimit);
	void MoveTarget_LSpin(CTransform* pTargetTransform, _float fTimeDelta , _float fLimit);
	void MoveTarget_RSpin(CTransform* pTargetTransform, _float fTimeDelta, _float fLimit);
	void MoveTarget_Back(_float fTimeDelta);

public:
	void State_Tick(CTransform* _Transform, _float fTimeDelta);
	void State_Tagetting(CTransform* _TargetTransform, _float fTimeDelta, _float fLimit);

public:

	STATE_MOVE    m_ePreState = STATE_MOVE::STATE_END;
	STATE_MOVE    m_eCurState = STATE_MOVE::MOVE_UPPER_RIGHT;

public:

	STATE_MOVETARGET m_eTargetPreState = STATE_MOVETARGET::MOVETARGET_END;
	STATE_MOVETARGET m_eTargetCurState = STATE_MOVETARGET::MOVETARGET_CHASE;

private:
	_float4x4 m_TargetWorldMat;
	_float		m_fDefaultBoundary = 10.f;

public:
	static CState_Move* Create();
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;

};



END

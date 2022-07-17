#pragma once


#include "State.h"

BEGIN(Engine)

class CTransform;
class CRigid_Body;

class ENGINE_DLL CState_Move final : public CState
{
#define SHOT_RANGE 20.f


private:
	CState_Move() = default;
	CState_Move(const CState_Move& Prototype);
	virtual ~CState_Move() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) {};
	virtual HRESULT Render() { return S_OK; };

public:
	void Set_TargetTransform(CTransform* _pTargetTransform);

public:
	void Move_Upper_Right();
	void Move_Upper_Left();
	void Move_Down_Front();
	void Move_Lift_Front();
	void Move_Lift_Back();
	void Move_Jump_Front();
	void MoveTaget_Chase_Player(_float fTimeDelta);
	void Move_Forward();

public:
	void MoveTarget_Chase(_float fTimeDelta, _float fLimit);
	void MoveTarget_LSpin(_float fTimeDelta , _float fLimit);
	void MoveTarget_RSpin(_float fTimeDelta, _float fLimit);
	void MoveTarget_Back(_float fTimeDelta);
	void MoveRoller_LSpin(_float fTimeDelta, _float fLimit);
	void MoveRoller_RSpin(_float fTimeDelta, _float fLimit);

public:
	//void State_Tick(CTransform* _Transform, _float fTimeDelta);
	//void State_Tagetting(CTransform* _TargetTransform, _float fTimeDelta, _float fLimit);

	void Set_State(STATE _eState);

public:


	STATE    m_ePreState = STATE::STATE_END;
	STATE    m_eCurState = STATE::STATE_END;

public:

	//STATE_MOVETARGET m_eTargetPreState = STATE_MOVETARGET::MOVETARGET_END;
	//STATE_MOVETARGET m_eTargetCurState = STATE_MOVETARGET::MOVETARGET_CHASE;

private:
	_float4x4 m_TargetWorldMat;
	_float		m_fDefaultBoundary = 100.f;
	CTransform* m_pTargetTransform = nullptr;

public:
	static CState_Move* Create();
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;

};



END

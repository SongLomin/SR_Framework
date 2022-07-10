#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CController abstract : public CComponent
{
protected:
	enum STATE_TYPE
	{
		STATE_MOVE = 0,
		STATE_MOVETARGET,
		STATE_ATTACK
	};

	CController();
	CController(const CController& Prototype);
	virtual ~CController() = default;


public:
	virtual void Tick(_float fTimeDelta) {};
	virtual void LateTick(_float fTimeDelta) {};


public:
	//사용하지 말 것.
	virtual void Link_Object(CGameObject* _pObject);
	void Set_Lock(_bool _bLock);
	_bool Get_Lock();

protected:
	CGameObject*	m_pMyObject = nullptr;

	//지금은 사용되지 않음.
	_bool			m_bLock = false;

public:
	virtual	CComponent* Clone(void* pArg) PURE;
	virtual void Free() override;

};

END
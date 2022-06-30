#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CController abstract : public CComponent
{
protected:
	CController();
	CController(const CController& Prototype);
	virtual ~CController() = default;


public:
	virtual void Tick(_float fTimeDelta) {};
	virtual void LateTick(_float fTimeDelta) {};


public:
	virtual void Link_Object(CGameObject* _pObject);

protected:
	CGameObject*	m_pMyObject = nullptr;

public:
	virtual	CComponent* Clone(void* pArg) PURE;
	virtual void Free() override;

};

END
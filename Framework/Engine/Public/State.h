#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CState : public CComponent
{
protected:
	CState() = default;
	CState(const CState& Prototype);
	virtual ~CState() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Tick(_float fTimeDelta);

public:
	static CComponent* Create();
	virtual	CComponent* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END


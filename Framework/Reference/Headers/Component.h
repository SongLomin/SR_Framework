#pragma once

#include "Base.h"

BEGIN(Engine)

class CGameObject;

class ENGINE_DLL CComponent : public CBase
{
protected:
	CComponent();
	CComponent(const CComponent& Prototype);
	virtual ~CComponent() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	HRESULT	Set_Owner(CGameObject* _pOwner);

protected:
	CGameObject* m_pOwner = nullptr;

public:
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END
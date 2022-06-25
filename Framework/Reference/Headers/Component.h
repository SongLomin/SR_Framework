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
	virtual void Tick(_float fTimeDelta) {};
	virtual void LateTick(_float fTimeDelta) {};
	virtual HRESULT Render_Begin() { return S_OK; }
	virtual HRESULT Render() { return S_OK; };

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	HRESULT	Set_Owner(CGameObject* _pOwner);
	CGameObject* Get_Owner();

protected:
	CGameObject* m_pOwner = nullptr;

public:
	static CComponent* Create();
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END
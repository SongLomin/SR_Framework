#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CTargetting final : public CComponent
{
private:
	CTargetting();
	virtual ~CTargetting() = default;


public:
	HRESULT Add_Targetting(CGameObject* pObject);
	


private:
	list<CGameObject*> m_pTargetting;

public:
	static CTargetting* Create();
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END
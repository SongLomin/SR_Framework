#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CTargeting final : public CComponent
{
private:
	CTargeting();
	virtual ~CTargeting() = default;

public:
	list<CGameObject*>* Get_Targetting() {
		return &m_pTargeting;
	}


public:
	void Make_TargetList(list<CGameObject*>* pLayer, _float fDist = 7.f);
	

private:
	void Clear_Targeting();

private:
	list<CGameObject*> m_pTargeting;

public:
	static CTargeting* Create();
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END
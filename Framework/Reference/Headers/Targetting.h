#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CTargetting final : public CComponent
{
private:
	CTargetting();
	virtual ~CTargetting() = default;

public:
	list<CGameObject*> Get_Targetting() {
		return m_pTargetting;
	}

public:
	void Update_Targetting();

public:
	void Make_TargetList(list<CGameObject*>* pLayer);
	


private:
	list<CGameObject*> m_pTargetting;

public:
	static CTargetting* Create();
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END
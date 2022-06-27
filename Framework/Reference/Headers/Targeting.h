#pragma once

#include "Component.h"

BEGIN(Engine)
class CTransform;
class ENGINE_DLL CTargeting final : public CComponent
{
private:
	CTargeting();
	virtual ~CTargeting() = default;

public:
	map<_float, CGameObject*>* Get_Targetting() {
		return &m_pTargeting;
	}


public:
	void Make_Player_TargetList(list<CGameObject*>* pLayer, _float fDist = 7.f);
	void Make_AI_TargetList(list<CGameObject*>* pTarget, CTransform* pObject, _float fDist = 7.f);

private:
	void Clear_Targeting();

private:
	map<_float, CGameObject*> m_pTargeting;

public:
	static CTargeting* Create();
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END
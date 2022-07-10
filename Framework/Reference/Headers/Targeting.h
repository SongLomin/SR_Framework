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
	
	TARGETMODE Get_TargetMode(){
		return m_eTargetMode;
	}

public:
	void Set_TargetMode(TARGETMODE _TargetMode) {
		m_eTargetMode = _TargetMode;
	}

public:
	void Make_Player_TargetList(list<CGameObject*>* pLayer, CTransform* pTransform, _float fDist = 20.f);
	void Make_AI_TargetList(list<CGameObject*>* pTarget, CTransform* pTransform, _float fDist = 40.f);
	void Make_TargetList_Distance(list<CGameObject*>* pTarget, _float3 _vPosition, _float _fRange);
	void Add_TargetList_Distance(list<CGameObject*>* pTarget, _float3 _vPosition, _float _fRange, _bool _bIsClear = false);
	
	static map<_float, CGameObject*> Get_Nearest_Target_Distance(list<CGameObject*>* pTarget, _float3 _vPosition, _float _fRange);


	bool IsTargetEmpty();

private:
	void Clear_Targeting();

private:
	map<_float, CGameObject*> m_pTargeting;
	TARGETMODE	m_eTargetMode = TARGETMODE::TARGET_END;

public:
	static CTargeting* Create();
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END
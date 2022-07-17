#pragma once

#include "Client_Defines.h"
#include "Level.h"

BEGIN(Client)

class CLevel_SunPlanet final : public CLevel
{
public:
	CLevel_SunPlanet();
	virtual ~CLevel_SunPlanet() = default;

public:
	virtual HRESULT Initialize();
	virtual void Tick(_float fTimeDelta);
	virtual HRESULT Render();
	virtual void Change_Level(void* pArg, _uint _iNextLevel);
	virtual HRESULT Complete_Condition() { return S_OK; }

public:
	virtual void OnTimerEvent(const _uint _iEventIndex);

private:
	_uint m_iSpawnCount = 0;
	_float m_fTextCount = 5.f;
	_bool m_bRollerDie = false;
public:

private:
	void SunPlanet_Event(_float fTimeDelta);


public:
	static CLevel_SunPlanet* Create();
	virtual void Free() override;
};

END


#pragma once

#include "Client_Defines.h"
#include "Level.h"

BEGIN(Client)

class CLevel_ExoPlanet final : public CLevel
{
public:
	CLevel_ExoPlanet();
	virtual ~CLevel_ExoPlanet() = default;

public:
	virtual HRESULT Initialize();
	virtual void Tick(_float fTimeDelta);
	virtual HRESULT Render();

private:
	void ExoPlanet_Event(float fTimeDelta);
	void Rock_Create(float fTimeDelta);

private:
	_float  m_fMaxTime = 200.f;
	_float  m_fRockSqawnTime = 1.f;
	virtual void Change_Level(void* pArg, _uint _iNextLevel) {}
	virtual HRESULT Complete_Condition() { return S_OK; }

public:
	static CLevel_ExoPlanet* Create();
	virtual void Free() override;
};

END


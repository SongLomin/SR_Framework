#pragma once

#include "Client_Defines.h"
#include "Level.h"

BEGIN(Client)

class CLevel_MagmaPlanet final : public CLevel
{
public:
	CLevel_MagmaPlanet();
	virtual ~CLevel_MagmaPlanet() = default;

public:
	virtual HRESULT Initialize();
	virtual void Tick(_float fTimeDelta);
	virtual HRESULT Render();
	virtual void Change_Level(void* pArg, _uint _iNextLevel);
	virtual HRESULT Complete_Condition() { return S_OK; }

private:
	void MagmaPlanet_Event(float fTimeDelta);

private:
	_float  m_fSpawnTime = 3.f;
	_float m_fMaxTime = 300.f;
	_bool  m_bSpawnCheck = true;
	_uint m_iSpawnCount = 0;

	_uint m_iMonsterCount = 0;

public:
	static CLevel_MagmaPlanet* Create();
	virtual void Free() override;
};

END


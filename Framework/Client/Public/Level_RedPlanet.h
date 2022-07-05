#pragma once

#include "Client_Defines.h"
#include "Level.h"

BEGIN(Engine)
class CGameObject;

END

BEGIN(Client)

class CLevel_RedPlanet final : public CLevel
{
public:
	CLevel_RedPlanet();
	virtual ~CLevel_RedPlanet() = default;

public:
	virtual HRESULT Initialize();
	virtual void Tick(_float TimeDelta);
	virtual HRESULT Render();

	virtual void Change_Level(void* pArg) {}
	virtual HRESULT Complete_Condition() { return S_OK; }

public:
	static CLevel_RedPlanet* Create();
	virtual void Free() override;

private:
	void RedPlanet_Event(float fTimeDelta);

private:
	_ulong	m_lPage[10];
	bool	m_bWaveCheck[10];

	_float  m_fSpawnTime = 2.f;

	_float m_fMaxTime = 180;

	CGameObject* m_pTextBoxObject = nullptr;
	CGameObject* m_pQuestBoxObject = nullptr;

};

END
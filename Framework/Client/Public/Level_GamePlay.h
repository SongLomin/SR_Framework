#pragma once

#include "Client_Defines.h"
#include "Level.h"

BEGIN(Client)

class CLevel_GamePlay final : public CLevel
{
public:
	CLevel_GamePlay();
	virtual ~CLevel_GamePlay() = default;

public:
	virtual HRESULT Initialize();
	virtual void Tick(_float TimeDelta);
	virtual HRESULT Render();

public:
	static CLevel_GamePlay* Create();
	virtual void Free() override;

private:
	void Ai_Create(_float TimeDelta);

private:
	_ulong	m_lPage[10];
	bool	m_bWaveCheck[10];

	_float  m_fSpawnTime = 2.f;
};

END
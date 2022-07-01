#pragma once

#include "Client_Defines.h"
#include "Level.h"

BEGIN(Client)

class CLevel_SelectPlanet final : public CLevel
{
public:
	CLevel_SelectPlanet();
	virtual ~CLevel_SelectPlanet() = default;

public:
	virtual HRESULT Initialize();
	virtual void Tick(_float fTimeDelta);
	virtual HRESULT Render();

public:
	static CLevel_SelectPlanet* Create();
	virtual void Free() override;

private:
	LEVEL m_eCurLevel = LEVEL_STATIC;
};

END


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



public:
	static CLevel_MagmaPlanet* Create();
	virtual void Free() override;
};

END


#pragma once

#include "Client_Defines.h"
#include "Level.h"

BEGIN(Client)

class CLevel_VenusPlanet final : public CLevel
{
public:
	CLevel_VenusPlanet();
	virtual ~CLevel_VenusPlanet() = default;

public:
	virtual HRESULT Initialize();
	virtual void Tick(_float fTimeDelta);
	virtual HRESULT Render();



public:
	static CLevel_VenusPlanet* Create();
	virtual void Free() override;
};

END


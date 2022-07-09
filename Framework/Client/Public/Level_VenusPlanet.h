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
	virtual void Change_Level(void* pArg, _uint _iNextLevel) {}
	virtual HRESULT Complete_Condition() { return S_OK; }

private:
	void VenusPlanet_Event(_float fTimeDelta);


public:
	static CLevel_VenusPlanet* Create();
	virtual void Free() override;
};

END


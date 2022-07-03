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
	_float  m_fMaxTime = 180;
	virtual void Change_Level() {}
	virtual HRESULT Complete_Condition() { return S_OK; }

public:
	static CLevel_ExoPlanet* Create();
	virtual void Free() override;
};

END


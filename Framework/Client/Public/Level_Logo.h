#pragma once

#include "Client_Defines.h"
#include "Level.h"

BEGIN(Client)

class CLevel_Logo final : public CLevel
{
public:
	CLevel_Logo();
	virtual ~CLevel_Logo() = default;

public:
	virtual HRESULT Initialize();
	virtual void Tick(_float TimeDelta);
	virtual HRESULT Render();

	virtual void Change_Level() {}
	virtual HRESULT Complete_Condition() { return S_OK; }

private:
	HRESULT Ready_Layer_BackGround(const _tchar* pLayerTag);

public:
	static CLevel_Logo* Create();
	virtual void Free() override;
};

END
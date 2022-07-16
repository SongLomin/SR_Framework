#pragma once

#include "Client_Defines.h"
#include "Level.h"

BEGIN(Client)

class CLevel_SunPlanet final : public CLevel
{
public:
	CLevel_SunPlanet();
	virtual ~CLevel_SunPlanet() = default;

public:
	virtual HRESULT Initialize();
	virtual void Tick(_float fTimeDelta);
	virtual HRESULT Render();
	virtual void Change_Level(void* pArg, _uint _iNextLevel);
	virtual HRESULT Complete_Condition() { return S_OK; }

private:
	void SunPlanet_Event(_float fTimeDelta);

private:
	CGameObject* m_pBossObject = nullptr;
	CGameObject* m_pBossHpObject = nullptr;
	CGameObject* m_pBossTableObject = nullptr;
	CGameObject* m_pBossNameObject = nullptr;

public:
	static CLevel_SunPlanet* Create();
	virtual void Free() override;
};

END


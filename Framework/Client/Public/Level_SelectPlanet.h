#pragma once

#include "Client_Defines.h"
#include "Level.h"

BEGIN(Engine)
class CGameObject;
END

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

	virtual void	Change_Level(void* pArg, _uint _iNextLevel) ;
	virtual HRESULT Complete_Condition() { return S_OK; }

public:
	static CLevel_SelectPlanet* Create();
	virtual void Free() override;


private:
	_float m_fTextBoxTime = 100;
	CGameObject* m_pTextObject = nullptr;

};

END


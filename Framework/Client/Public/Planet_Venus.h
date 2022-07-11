#pragma once
#include "Client_Defines.h"
#include "Planet.h"

BEGIN(Engine)
class CDirectionalLight;
class CPointLight;
class CSpotLight;
END

BEGIN(Client)

class CPlanet_Venus final : public CPlanet
{
public:
	CPlanet_Venus();
	CPlanet_Venus(const CPlanet_Venus& Prototype);
	virtual ~CPlanet_Venus() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;

private:
	CPointLight* m_pPointLightCom = nullptr;
	
protected:
	virtual void SetUp_Components_For_Child();

private:
	_bool m_bLevelChange = false;


public:
	static CPlanet_Venus* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END

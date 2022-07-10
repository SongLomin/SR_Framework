#pragma once
#include "Client_Defines.h"
#include "Planet.h"

BEGIN(Engine)
class CDirectionalLight;
END

BEGIN(Client)

class CPlanet_Select final : public CPlanet
{
private:
	CPlanet_Select();
	CPlanet_Select(const CPlanet_Select& Prototype);
	virtual ~CPlanet_Select() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;


protected:
	virtual void SetUp_Components_For_Child();

private:
	CGameObject* m_pDiveUi = nullptr;
	CDirectionalLight* m_pDirectionalLightCom2 = nullptr;

public:
	static CPlanet_Select* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END
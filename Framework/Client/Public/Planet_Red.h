#pragma once
#include "Client_Defines.h"
#include "Planet.h"

BEGIN(Engine)

END

BEGIN(Client)

class CPlanet_Red final : public CPlanet
{
private:
	CPlanet_Red();
	CPlanet_Red(const CPlanet_Red& Prototype);
	virtual ~CPlanet_Red() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;

public:
	virtual void SetUp_Components_For_Child();

public:
	static CPlanet_Red* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END

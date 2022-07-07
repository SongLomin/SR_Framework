#pragma once
#include "Client_Defines.h"
#include "Planet.h"

BEGIN(Engine)
END

BEGIN(Client)

class CPlanet_Sun final : public CPlanet
{
public:
	CPlanet_Sun();
	CPlanet_Sun(const CPlanet_Sun& Prototype);
	virtual ~CPlanet_Sun() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;

protected:
	virtual void SetUp_Components_For_Child();

private:
	//HRESULT SetUp_Components();
	//void LookAtCamera();
	//void Enter_Planet();

private:
	_bool m_bLevelChange = false;
	

public:
	static CPlanet_Sun* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END


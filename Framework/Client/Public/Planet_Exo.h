#pragma once
#include "Client_Defines.h"
#include "Planet.h"

BEGIN(Engine)

END

BEGIN(Client)

class CPlanet_Exo final : public CPlanet
{
public:
	CPlanet_Exo();
	CPlanet_Exo(const CPlanet_Exo& Prototype);
	virtual ~CPlanet_Exo() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;

private:/*
	HRESULT SetUp_Components();
	void LookAtCamera();
	void Enter_Planet();*/
	_bool m_bLevelChange = false;


protected:
	virtual void SetUp_Components_For_Child();

public:
	static CPlanet_Exo* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END

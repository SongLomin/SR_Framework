#pragma once
#include "Client_Defines.h"
#include "Planet.h"

BEGIN(Engine)
END

BEGIN(Client)

class CPlanet_Magma final : public CPlanet
{
public:
	CPlanet_Magma();
	CPlanet_Magma(const CPlanet_Magma& Prototype);
	virtual ~CPlanet_Magma() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;

public:
	virtual void SetUp_Components_For_Child();

//private:
//	HRESULT SetUp_Components();
//	void LookAtCamera();
//	void Enter_Planet();

private:
	_bool m_bLevelChange = false;

public:
	static CPlanet_Magma* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END

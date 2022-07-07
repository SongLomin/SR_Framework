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

//private:
//	HRESULT SetUp_Components();
//	void LookAtCamera();
//	void Enter_Planet();

protected:
	virtual void SetUp_Components_For_Child();

private:
	_bool m_bLevelChange = false;
	CGameObject* m_pDiveUi = nullptr;
	

public:
	static CPlanet_Red* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END

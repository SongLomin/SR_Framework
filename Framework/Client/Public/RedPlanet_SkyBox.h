#pragma once
#include "Client_Defines.h"
#include "SkyBox.h"

BEGIN(Engine)

END

BEGIN(Client)

class CRedPlanet_SkyBox final : public CSkyBox
{
private:
	CRedPlanet_SkyBox();
	CRedPlanet_SkyBox(const CRedPlanet_SkyBox& Prototype);
	virtual ~CRedPlanet_SkyBox() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;

public:
	virtual void SetUp_For_Child() override;

public:
	static CRedPlanet_SkyBox* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END


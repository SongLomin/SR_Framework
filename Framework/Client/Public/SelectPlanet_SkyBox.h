#pragma once
#include "Client_Defines.h"
#include "SkyBox.h"

BEGIN(Engine)

END

BEGIN(Client)

class CSelectPlanet_SkyBox final : public CSkyBox
{
private:
	CSelectPlanet_SkyBox();
	CSelectPlanet_SkyBox(const CSelectPlanet_SkyBox& Prototype);
	virtual ~CSelectPlanet_SkyBox() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;
	
public:
	virtual void SetUp_For_Child() override;

public:
	static CSelectPlanet_SkyBox* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END


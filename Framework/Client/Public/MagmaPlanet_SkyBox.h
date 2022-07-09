#pragma once
#include "Client_Defines.h"
#include "SkyBox.h"

BEGIN(Engine)

END

BEGIN(Client)

class CMagmaPlanet_SkyBox final : public CSkyBox
{
private:
	CMagmaPlanet_SkyBox();
	CMagmaPlanet_SkyBox(const CMagmaPlanet_SkyBox& Prototype);
	virtual ~CMagmaPlanet_SkyBox() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;

public:
	virtual void SetUp_For_Child() override;

public:
	static CMagmaPlanet_SkyBox* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END


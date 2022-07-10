#pragma once
#include "Client_Defines.h"
#include "SkyBox.h"

BEGIN(Engine)

END

BEGIN(Client)

class CExoPlanet_SkyBox final : public CSkyBox
{
private:
	CExoPlanet_SkyBox();
	CExoPlanet_SkyBox(const CExoPlanet_SkyBox& Prototype);
	virtual ~CExoPlanet_SkyBox() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;

public:
	virtual void SetUp_For_Child() override;

public:
	static CExoPlanet_SkyBox* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END


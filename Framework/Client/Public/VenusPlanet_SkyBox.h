#pragma once
#include "Client_Defines.h"
#include "SkyBox.h"

BEGIN(Engine)

END

BEGIN(Client)

class CVenusPlanet_SkyBox final : public CSkyBox
{
private:
	CVenusPlanet_SkyBox();
	CVenusPlanet_SkyBox(const CVenusPlanet_SkyBox& Prototype);
	virtual ~CVenusPlanet_SkyBox() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;

public:
	virtual void SetUp_For_Child() override;

public:
	static CVenusPlanet_SkyBox* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END


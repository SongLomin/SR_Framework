#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CSelectShip final : public CUI
{
private:
	CSelectShip();
	CSelectShip(const CSelectShip& Prototype);
	virtual ~CSelectShip() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;

private:
	virtual void SetUp_Components_For_Child();

public:
	static CSelectShip* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END



#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Engine)
END


BEGIN(Client)

class CDive final : public CUI
{
private:
	CDive();
	CDive(const CDive& Prototype);
	virtual ~CDive() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;

private:
	virtual void SetUp_Components_For_Child();

public:
	static CDive* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END
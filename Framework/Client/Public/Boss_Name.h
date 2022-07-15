#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CBossName final : public CUI
{
public:
	CBossName() = default;
	CBossName(const CBossName& Prototype);
	virtual ~CBossName() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;

private:
	virtual void SetUp_Components_For_Child();

public:
	static CBossName* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END

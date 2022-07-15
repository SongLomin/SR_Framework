#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CBossHpTable final : public CUI
{
public:
	CBossHpTable() = default;
	CBossHpTable(const CBossHpTable& Prototype);
	virtual ~CBossHpTable() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;

private:
	virtual void SetUp_Components_For_Child();

public:
	static CBossHpTable* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END


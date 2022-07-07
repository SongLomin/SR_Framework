#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Engine)
END


BEGIN(Client)

class CQuest final : public CUI
{
private:
	CQuest();
	CQuest(const CQuest& Prototype);
	virtual ~CQuest() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;

private:
	virtual void SetUp_Components_For_Child();

public:
	static CQuest* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END
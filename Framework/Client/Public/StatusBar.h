#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Engine)
END


BEGIN(Client)

class CStatusBar final : public CUI
{
public:
	CStatusBar() = default;
	CStatusBar(const CStatusBar& Prototype);
	virtual ~CStatusBar() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;

private:
	virtual void SetUp_Components_For_Child();

public:
	static CStatusBar* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END




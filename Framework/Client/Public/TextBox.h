#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Engine)
END


BEGIN(Client)

class CTextBox final : public CUI
{
private:
	CTextBox();
	CTextBox(const CTextBox& Prototype);
	virtual ~CTextBox() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;

private:
	virtual void SetUp_Components_For_Child();

public:
	static CTextBox* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END

#pragma once
#include "Client_Defines.h"
#include "UI.h"


BEGIN(Engine)
END


BEGIN(Client)

class CWarring final : public CUI
{
private:
	CWarring();
	CWarring(const CWarring& Prototype);
	virtual ~CWarring() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;

private:
	virtual void SetUp_Components_For_Child();

public:
	static CWarring* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END
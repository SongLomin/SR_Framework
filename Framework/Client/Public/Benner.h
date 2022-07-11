#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Client)

class CBenner final : public CUI
{
private:
	CBenner();
	CBenner(const CBenner& Prototype);
	virtual ~CBenner() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;

private:
	virtual void SetUp_Components_For_Child();

public:
	static CBenner* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END


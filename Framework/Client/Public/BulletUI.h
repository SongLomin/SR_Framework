#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Engine)
END


BEGIN(Client)

class CBulletUI final : public CUI
{
private:
	CBulletUI() = default;
	CBulletUI(const CBulletUI& Prototype);
	virtual ~CBulletUI() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;

private:
	virtual void SetUp_Components_For_Child();


public:
	static CBulletUI* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END


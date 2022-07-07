#pragma once
#include "Client_Defines.h"
#include "UI.h"

BEGIN(Engine)
END


BEGIN(Client)

class CBulletCountUI final : public CUI
{
public:
	CBulletCountUI() = default;
	CBulletCountUI(const CBulletCountUI& Prototype);
	virtual ~CBulletCountUI() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;


private:
	virtual void SetUp_Components_For_Child();

public:
	static CBulletCountUI* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END

#pragma once
#include "Client_Defines.h"
#include "UI.h"




BEGIN(Client)

class CTextBox final : public CUI
{
public:
	CTextBox() = default;
	CTextBox(const CTextBox& Prototype);
	virtual ~CTextBox() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;




private:
	HRESULT SetUp_Components();

public:
	static CTextBox* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END

#pragma once
#include "Controller.h"

BEGIN(Engine)

class ENGINE_DLL CLock_Controller final : public CController
{
private:
	CLock_Controller();
	CLock_Controller(const CLock_Controller& Prototype);
	virtual ~CLock_Controller() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
public:
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;

public:
	static CLock_Controller* Create();
	virtual CController* Clone(void* pArg) override;
	virtual void Free() override;
};

END
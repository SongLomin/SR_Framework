#pragma once
#include "Controller.h"

BEGIN(Engine)

class ENGINE_DLL CAI_Controller final : public CController
{
public:
	CAI_Controller();
	CAI_Controller(const CAI_Controller& Prototype);
	virtual ~CAI_Controller() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);

public:
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);


public:
	static CAI_Controller* Create();
	virtual CController* Clone(void* pArg) override;
	virtual void Free() override;
};

END
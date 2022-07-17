#pragma once
#include "Controller.h"

BEGIN(Engine)

class ENGINE_DLL CPlayer_Controller final : public CController
{
private:
	CPlayer_Controller();
	CPlayer_Controller(const CPlayer_Controller& Prototype);
	virtual ~CPlayer_Controller() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
public:
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);


private:
	_uint	m_iCurrentCam = 0;
	_float  m_fTime = 1.f;
	_uint   m_iCurrent_TargetMode = 0;

	_uint	m_iBoosterSoundChannelIndex = -1;
	_uint	m_iShotSoundChannelIndex = -1;

public:
	static CPlayer_Controller* Create();
	virtual CController* Clone(void* pArg) override;
	virtual void Free() override;
};

END
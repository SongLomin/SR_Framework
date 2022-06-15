#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CStatus final : public CComponent
{
public:
	enum STATUSID { STATUS_HP, STATUS_ATTACK, STATUS_ARMOR, STATUS_END};

public:
	typedef struct tagSTATUS
	{
		_float fHp;
		_float fAttack;
		_float fArmor;

	}STATUS;

public:
	CStatus();
	virtual ~CStatus() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);

public:
	STATUS Get_Status() {
		return m_tStatus;
	}

public:
	HRESULT Set_Status(STATUSID StatusID, _float value); // 값 수정
	HRESULT Add_Status(STATUSID StatusID, _float value); // 값 변경

private:
	STATUS		m_tStatus;

public:
	static CStatus* Create();
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END
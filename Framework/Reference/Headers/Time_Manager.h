#pragma once
#include "Base.h"

BEGIN(Engine)

class CTimer;

class CTime_Manager final :
    public CBase
{
    DECLARE_SINGLETON(CTime_Manager)
private:
    CTime_Manager() = default;
    virtual ~CTime_Manager() = default;

public:
	HRESULT Add_Timer(_uint eTimer);
	_float Compute_Timer(_uint eTimer);

private:
	map<_uint, CTimer*>			m_Timers;

private:
	class CTimer* Find_Timer(_uint eTimer);

public:
	virtual void Free();

};

END
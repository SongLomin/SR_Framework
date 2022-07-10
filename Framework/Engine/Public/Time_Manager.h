#pragma once
#include "Base.h"

BEGIN(Engine)

class CTimer;

class CTime_Manager final :
    public CBase
{
    DECLARE_SINGLETON(CTime_Manager)

private:
	typedef struct tag_TimerEvent
	{
		_float	fMaxTime = 0.f;
		_float	fCurTime = 0.f;
		_uint	iEventNum = 0;
		_bool	bLoop = false;
		_bool	bUseTimeScale = false;
		_bool	bAlwaysCall = false;
		CBase* pInstance = nullptr;

	}TIMEREVENT;


private:
    CTime_Manager() = default;
    virtual ~CTime_Manager() = default;

public:
	void Tick(const _float& _fOriginDeltaTime, const _float& _fTimeScale);

public:
	HRESULT Add_Timer(_uint eTimer);
	_float Compute_Timer(_uint eTimer);

	HRESULT Add_TimerEvent(_uint _iEventNum, CBase* _Instance, _float _fTime, _bool _bLoop = false, _bool _bUseTimeScale = false, _bool _bAlwaysCall = false);

private:
	map<_uint, CTimer*>			m_Timers;
	list<tag_TimerEvent>		m_TimerEvents;

private:
	class CTimer* Find_Timer(_uint eTimer);

public:
	virtual void Free();

};

END
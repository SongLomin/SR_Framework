#include "Time_Manager.h"
#include "Timer.h"

IMPLEMENT_SINGLETON(CTime_Manager)

void CTime_Manager::Tick(const _float& _fOriginDeltaTime, const _float& _fTimeScale)
{
	for (auto iter = m_TimerEvents.begin(); iter != m_TimerEvents.end();)
	{
		if (!(*iter).pInstance)
		{
			iter = m_TimerEvents.erase(iter);
			continue;
		}

		if ((*iter).fCurTime < 0.f)
		{
			(*iter).pInstance->OnTimerEvent((*iter).iEventNum);

			if ((*iter).bLoop)
			{
				(*iter).fCurTime = (*iter).fMaxTime;
				continue;
			}
			else
			{
				RETURN_WEAKPTR((*iter).pInstance);
				iter = m_TimerEvents.erase(iter);
				continue;
			}
		}

		(*iter).fCurTime -= (_float)(_fOriginDeltaTime * (_float)((*iter).bUseTimeScale ? _fTimeScale : 1.f));
		iter++;
	}

}

HRESULT CTime_Manager::Add_Timer(_uint eTimer)
{
	if (nullptr != Find_Timer(eTimer))
		return E_FAIL;

	CTimer* pTimer = CTimer::Create();
	if (nullptr == pTimer)
		return E_FAIL;

	m_Timers.emplace(eTimer, pTimer);

	return S_OK;
}

_float CTime_Manager::Compute_Timer(_uint eTimer)
{
	CTimer* pTimer = nullptr;

	// 타이머를 Find하면 프레임 저하가 생긴다.
	// 프로그램의 루프마다 호출되는 타이머가 있다.
	// 해당 타이머를 매 루프마다(빈도가 Tick보다 많다.) 그렇다면 Find하는게 맞을까?
	// 맞지 않다. 따라서 0번 타이머는 루프 시간을 검사하는 타이머로 고정시킨다.
	if (0 == eTimer)
	{
		pTimer = (*m_Timers.begin()).second;
	}

	else
	{
		pTimer = Find_Timer(eTimer);
	}

	
	if (nullptr == pTimer)
		return 0.f;

	return pTimer->Compute_Timer();
}

HRESULT CTime_Manager::Add_TimerEvent(_uint _iEventNum, CBase* _Instance, _float _fTime, _bool _bLoop, _bool _bUseTimeScale)
{
	TIMEREVENT TimerEvent;

	TimerEvent.fMaxTime = TimerEvent.fCurTime = _fTime;
	TimerEvent.iEventNum = _iEventNum;
	TimerEvent.pInstance = _Instance;
	WEAK_PTR(TimerEvent.pInstance);
	TimerEvent.bLoop = _bLoop;
	TimerEvent.bUseTimeScale = _bUseTimeScale;

	m_TimerEvents.push_back(TimerEvent);


	return S_OK;
}

CTimer* CTime_Manager::Find_Timer(_uint eTimer)
{

	auto iter = m_Timers.find(eTimer);

	if (m_Timers.end() == iter)
	{
		return nullptr;
	}

	return (*iter).second;
}

void CTime_Manager::Free()
{
	for (auto& Pair : m_Timers)
		Safe_Release(Pair.second);

	for (auto& elem : m_TimerEvents)
	{
		RETURN_WEAKPTR(elem.pInstance);
	}


	m_Timers.clear();

	delete this;
}

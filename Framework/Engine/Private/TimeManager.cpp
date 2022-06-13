#include "TimeManager.h"

IMPLEMENT_SINGLETON(CTime_Manager)

CTime_Manager::CTime_Manager()
{
}

HRESULT CTime_Manager::Add_Timer(const _tchar* pTimerTag)
{
	if (nullptr != Find_Timer(pTimerTag))
		return E_FAIL;

	CTimer* pTimer = CTimer::Create();
	if (nullptr == pTimer)
		return E_FAIL;

	m_Timers.emplace(pTimerTag, pTimer);

	return S_OK;
}

_float CTime_Manager::Compute_Timer(const _tchar* pTimerTag)
{
	CTimer* pTimer = Find_Timer(pTimerTag);
	if (nullptr == pTimer)
		return 0.f;

	return pTimer->Compute_Timer();
}

CTimer* CTime_Manager::Find_Timer(const _tchar* pTimerTag)
{
	auto	iter = find_if(m_Timers.begin(), m_Timers.end(), CTag_Finder(pTimerTag));
	if (iter == m_Timers.end())
		return nullptr;

	return iter->second;
}

void CTime_Manager::Free()
{
	for (auto& Pair : m_Timers)
		Safe_Release(Pair.second);

	m_Timers.clear();
}

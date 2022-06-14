#include "Time_Manager.h"
#include "Timer.h"

IMPLEMENT_SINGLETON(CTime_Manager)

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
	CTimer* pTimer = Find_Timer(eTimer);
	if (nullptr == pTimer)
		return 0.f;

	return pTimer->Compute_Timer();
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

	m_Timers.clear();

	delete this;
}

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
	CTimer* pTimer = nullptr;

	// Ÿ�̸Ӹ� Find�ϸ� ������ ���ϰ� �����.
	// ���α׷��� �������� ȣ��Ǵ� Ÿ�̸Ӱ� �ִ�.
	// �ش� Ÿ�̸Ӹ� �� ��������(�󵵰� Tick���� ����.) �׷��ٸ� Find�ϴ°� ������?
	// ���� �ʴ�. ���� 0�� Ÿ�̸Ӵ� ���� �ð��� �˻��ϴ� Ÿ�̸ӷ� ������Ų��.
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

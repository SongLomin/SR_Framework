#include "Status.h"

CStatus::CStatus()
{
	ZeroMemory(&m_tStatus, sizeof(STATUS));
}

HRESULT CStatus::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CStatus::Initialize(void* pArg)
{
	memcpy(&m_tStatus, pArg, sizeof(STATUS));
	return S_OK;
}

HRESULT CStatus::Set_Status(STATUSID StatusID, _float value)
{
	if (StatusID >= STATUS_END ||
		value < 0 )
		return E_FAIL;

	switch (StatusID)
	{
	case STATUS_HP:
		m_tStatus.fHp = value;
		break;

	case STATUS_ATTACK:
		m_tStatus.fAttack = value;
		break;

	case STATUS_ARMOR:
		m_tStatus.fArmor = value;
		break;
	}
	
	return S_OK;
}

HRESULT CStatus::Add_Status(STATUSID StatusID, _float value)
{
	if (StatusID >= STATUS_END)
		return E_FAIL;

	switch (StatusID)
	{
	case STATUS_HP:
		m_tStatus.fHp += value;
		break;

	case STATUS_ATTACK:
		m_tStatus.fAttack += value;
		break;

	case STATUS_ARMOR:
		m_tStatus.fArmor += value;
		break;
	}

	return S_OK;
}

CStatus* CStatus::Create()
{
	CStatus* pInstance = new CStatus();

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CStatus");
		//Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CStatus::Clone(void* pArg)
{
	CStatus* pInstance = new CStatus();

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CStatus");
		//Safe_Release(pInstance);
	}

	return pInstance;
}

void CStatus::Free()
{
	__super::Free();

	delete this;
}

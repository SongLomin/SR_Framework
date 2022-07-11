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

_float CStatus::Get_Status(STATUSID StatusID)
{
	switch (StatusID)
	{
	case STATUS_HP:
		return m_tStatus.fHp;

	case STATUS_MAXHP:
		return m_tStatus.fMaxHp;

	case STATUS_ATTACK:
		return m_tStatus.fAttack;

	case STATUS_ARMOR:
		return m_tStatus.fArmor;
	}

	return 0.f;
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

	case STATUS_MAXHP:
		m_tStatus.fMaxHp = value;
		break;

	case STATUS_ATTACK:
		m_tStatus.fAttack = value;
		break;

	case STATUS_ARMOR:
		m_tStatus.fArmor = value;
		break;

	case STATUS_MAXARMOR:
		m_tStatus.fMaxArmor = value;
		break;

	case STATUS_BOOSTER:
		m_tStatus.fBooster = value;
		break;

	case STATUS_MAXBOOSTER:
		m_tStatus.fMaxBooster = value;
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

	case STATUS_MAXHP:
		m_tStatus.fMaxHp += value;
		break;

	case STATUS_ATTACK:
		m_tStatus.fAttack += value;
		break;

	case STATUS_ARMOR:
		m_tStatus.fArmor += value;
		break;

	case STATUS_MAXARMOR:
		m_tStatus.fMaxArmor += value;
		break;

	case STATUS_BOOSTER:
		m_tStatus.fBooster += value;
		break;

	case STATUS_MAXBOOSTER:
		m_tStatus.fMaxBooster += value;
		break;
	}

	return S_OK;
}

HRESULT CStatus::Set_FULL_HP()
{
	Set_Status(STATUSID::STATUS_HP, Get_Status(STATUSID::STATUS_MAXHP));

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

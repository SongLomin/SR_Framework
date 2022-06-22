#include "State.h"

CState::CState(const CState& Prototype)
{
	*this = Prototype;
}

HRESULT CState::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CState::Initialize(void* pArg)
{
	return S_OK;
}

HRESULT CState::Tick(_float fTimeDelta)
{
	return S_OK;
}

CComponent* CState::Create()
{
	return nullptr;
}

CComponent* CState::Clone(void* pArg)
{
	return nullptr;
}

void CState::Free()
{
	__super::Free();
}

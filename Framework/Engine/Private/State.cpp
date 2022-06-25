#include "State.h"
#include "GameInstance.h"



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









void CState::Free()
{
	__super::Free();
}

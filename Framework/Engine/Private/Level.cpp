#include "..\Public\Level.h"

CLevel::CLevel()
{
	//Safe_AddRef(m_pGraphic_Device);
}

HRESULT CLevel::Initialize()
{
	return S_OK;
}

void CLevel::Tick(_float TimeDelta)
{
}

HRESULT CLevel::Render()
{
	return S_OK;
}

void CLevel::Free()
{
	//Safe_Release(m_pGraphic_Device);
}

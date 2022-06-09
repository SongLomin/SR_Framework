#include "..\Public\GameObject.h"
#include "GameInstance.h"
#include <iostream>

CGameObject::CGameObject()
{
	//Safe_AddRef(m_pGraphic_Device);
}

CGameObject::CGameObject(const CGameObject & Prototype)
{
	//Safe_AddRef(m_pGraphic_Device);
}

HRESULT CGameObject::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CGameObject::Initialize(void* pArg)
{
	return S_OK;
}

void CGameObject::Tick(_float fTimeDelta)
{
}

void CGameObject::LateTick(_float fTimeDelta)
{
}

HRESULT CGameObject::Render()
{

	return S_OK;
}

void CGameObject::Free()
{
	//Safe_Release(m_pGraphic_Device);
	__super::Free();

	for (auto& elem : m_pComs)
	{
		Safe_Release(elem.second);
	}

	m_pComs.clear();

	//delete this;
}

#include "..\Public\Component_Manager.h"
#include "Component.h"
#include <iostream>

IMPLEMENT_SINGLETON(CComponent_Manager)

CComponent_Manager::CComponent_Manager()
{

}

//HRESULT CComponent_Manager::Reserve_Container(_uint iNumLevels)
//{
//	if (nullptr != m_pPrototypes)
//		return E_FAIL;
//
//	m_iNumLevels = iNumLevels;
//
//	m_pPrototypes = new PROTOTYPES[iNumLevels];
//
//	return S_OK;
//}

HRESULT CComponent_Manager::Add_Prototype(const _char * pPrototypeTag, CComponent * pPrototype)
{
	if (nullptr != Find_Components(pPrototypeTag))
		return E_FAIL;

	m_pPrototypes.emplace(pPrototypeTag, pPrototype);
	
	return S_OK;
}

CComponent * CComponent_Manager::Clone_Component(const _char * pPrototypeTag, void * pArg)
{
	CComponent*		pPrototype = Find_Components(pPrototypeTag);

	if (nullptr == pPrototype)
	{
		return nullptr;
	}

	return pPrototype->Clone(pArg);
}

CComponent * CComponent_Manager::Find_Components(const _char * pPrototypeTag)
{
	auto	iter = find_if(m_pPrototypes.begin(), m_pPrototypes.end(), CTag_Finder_c_str(pPrototypeTag));

	if (iter == m_pPrototypes.end())
		return nullptr;

	return iter->second;
}

void CComponent_Manager::Free()
{
	__super::Free();

	for (auto& Pair : m_pPrototypes)
		Safe_Release(Pair.second);

	m_pPrototypes.clear();
	
	delete this;
}

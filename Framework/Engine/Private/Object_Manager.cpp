#include "..\Public\Object_Manager.h"
#include "Layer.h"
#include "GameObject.h"
#include "GameInstance.h"

IMPLEMENT_SINGLETON(CObject_Manager)

CObject_Manager::CObject_Manager()
{
}

HRESULT CObject_Manager::Reserve_Container(_uint iNumLevels)
{
	if (0 != m_pLayers.size())
		return E_FAIL;

	m_iNumLevels = iNumLevels;

	for(int i=0; i<iNumLevels; i++)
		m_pLayers.push_back({});
	
	return S_OK;
}

CGameObject* CObject_Manager::Get_Player()
{
	list<CGameObject*>* pLayer = Find_Layer(CURRENT_LEVEL, TEXT("0.Player_Body"));

	ISVALID(pLayer, nullptr);

	return pLayer->front();
}

void CObject_Manager::Tick(_float fTimeDelta)
{
	for (_uint i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			for(auto& elem_GameObject : Pair.second) 
			{
				//게임오브젝트가 활성화 상태면 Tick을 돌린다.
				if(elem_GameObject->Get_Enable())
					elem_GameObject->Tick(fTimeDelta);		
			}
		}
	}
}

void CObject_Manager::LateTick(_float fTimeDelta)
{	
	for (_uint i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			for (auto& elem_GameObject : Pair.second)
			{
				//게임오브젝트가 활성화 상태면 LateTick을 돌린다.
				if(elem_GameObject->Get_Enable())
					elem_GameObject->LateTick(fTimeDelta);
			}
		}
	}
}

void CObject_Manager::Remove_Dead_Object()
{

	for (_uint i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			for (auto iter = Pair.second.begin(); iter != Pair.second.end();)
			{
				if ((*iter)->Get_Dead())
				{
					Safe_Release((*iter));
					iter = Pair.second.erase(iter);
				}
				else
				{
					iter++;
				}
			}
		}
	}


}

void CObject_Manager::Clear(_uint iLevelIndex)
{
	if (iLevelIndex >= m_iNumLevels)
		return;

	for (auto& Pair : m_pLayers[iLevelIndex])
	{
		for (auto& elem_GameObject : Pair.second)
		{
			if(elem_GameObject)
				Safe_Release(elem_GameObject);
		}
	}
		

	m_pLayers[iLevelIndex].clear();
}

CGameObject * CObject_Manager::Find_Prototype(const _char * pPrototypeTag)
{
	auto	iter = find_if(m_Prototypes.begin(), m_Prototypes.end(), CTag_Finder_c_str(pPrototypeTag));

	if (iter == m_Prototypes.end())
		return nullptr;

	return iter->second;
}

list<CGameObject*>* CObject_Manager::Find_Layer(_uint iLevelIndex, const _tchar * pLayerTag)
{
	if (iLevelIndex >= m_iNumLevels)
		return nullptr;

	auto	iter = find_if(m_pLayers[iLevelIndex].begin(), m_pLayers[iLevelIndex].end(), CTag_Finder(pLayerTag));

	if (iter == m_pLayers[iLevelIndex].end())
		return nullptr;

	return &iter->second;	
}

void CObject_Manager::Free()
{
	for (_uint i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			for (auto& elem_GameObject : Pair.second)
			{
				Safe_Release(elem_GameObject);
			}
			int i = 0;
		}
		m_pLayers[i].clear();
	}

	for (auto& Pair : m_Prototypes)	
		Safe_Release(Pair.second);

	m_Prototypes.clear();
	
	delete this;
}

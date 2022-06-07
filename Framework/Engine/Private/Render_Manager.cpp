#include "..\Public\Render_Manager.h"
#include "GameObject.h"

IMPLEMENT_SINGLETON(CRender_Manager)

CRender_Manager::CRender_Manager()
{
}

HRESULT CRender_Manager::Add_RenderGroup(RENDERGROUP eGroup, CGameObject* pGameObject)
{
	if ((_uint)eGroup >= (_uint)RENDERGROUP::RENDER_END ||
		nullptr == pGameObject)
		return E_FAIL;

	m_RenderObjects[(_uint)eGroup].push_back(pGameObject);

	//Safe_AddRef(pGameObject);

	return S_OK;
}

HRESULT CRender_Manager::Draw_RenderGroup()
{
	for (_uint i = 0; i < (_uint)RENDERGROUP::RENDER_END; ++i)
	{
		for (auto& pGameObject : m_RenderObjects[i])
		{
			if (nullptr != pGameObject)
				pGameObject->Render();

			//Safe_Release(pGameObject);
		}
		m_RenderObjects[i].clear();
	}

	return S_OK;
}

void CRender_Manager::Free()
{
	__super::Free();
	
	delete this;
}

#include "..\Public\Renderer.h"
#include "GameObject.h"
#include "GameInstance.h"

CRenderer::CRenderer()
{
}

HRESULT CRenderer::Add_RenderGroup(RENDERGROUP eGroup, CGameObject* pGameObject)
{
	if ((_uint)eGroup >= (_uint)RENDERGROUP::RENDER_END ||
		nullptr == pGameObject)
		return E_FAIL;

	CGameInstance::Get_Instance()->Add_RenderGroup(eGroup, pGameObject);

	//Safe_AddRef(pGameObject);

	return S_OK;
}

HRESULT CRenderer::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CRenderer::Initialize(void * pArg)
{
	return S_OK;
}

CRenderer * CRenderer::Create()
{
	CRenderer*		pInstance = new CRenderer();

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CRenderer");
		//Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CRenderer::Clone(void * pArg)
{

	return this;	
}

void CRenderer::Free()
{
	__super::Free();

	delete this;
}

#include "..\Public\Renderer.h"
#include "GameObject.h"
#include "GameInstance.h"

CRenderer::CRenderer()
{
}

CRenderer::CRenderer(const CRenderer& Prototype)
{
	*this = Prototype;
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

HRESULT CRenderer::Set_Textures_From_Key(const _tchar* _Str_Key, MEMORY_TYPE _eType)
{
	m_ppTextures = CGameInstance::Get_Instance()->Get_Textures_From_Key(_Str_Key, _eType);

	if (!m_ppTextures)
		return E_FAIL;

	return S_OK;
}

HRESULT CRenderer::Update_Textures(_uint _iIndex)
{
	if (nullptr == m_ppTextures)
	{
		return E_FAIL;
	}

	DEVICE->SetTexture(0, (*m_ppTextures)[_iIndex]);

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

	CRenderer* pInstance = new CRenderer();

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CRenderer");
		//Safe_Release(pInstance);
	}

	return pInstance;
}

void CRenderer::Free()
{
	__super::Free();

	delete this;
}

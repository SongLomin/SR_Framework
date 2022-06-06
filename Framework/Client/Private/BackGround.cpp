#include "stdafx.h"
#include "..\Public\BackGround.h"
#include "GameInstance.h"

CBackGround::CBackGround(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{

}

CBackGround::CBackGround(const CBackGround & Prototype)
	: CGameObject(Prototype)
{
}

HRESULT CBackGround::Initialize_Prototype()
{
	/* 백엔드로부터 값ㅇ를 어덩오낟. */

	return S_OK;
}

HRESULT CBackGround::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	
	return S_OK;
}

void CBackGround::Tick(_float fTimeDelta)
{
	int a = 10;
}

void CBackGround::LateTick(_float fTimeDelta)
{
	if (nullptr == m_pRendererCom)
		return;

	
	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_PRIORITY, this);
}

HRESULT CBackGround::Render()
{
	return S_OK;
}

HRESULT CBackGround::SetUp_Components()
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	//Safe_AddRef(pGameInstance);

	/* For.Com_Renderer */ 
	m_pRendererCom = (CRenderer*)pGameInstance->Clone_Component(LEVEL_STATIC, TEXT("Prototype_Component_Renderer"));
	if (nullptr == m_pRendererCom)
		return E_FAIL;




	Safe_Release(pGameInstance);
	return S_OK;
}

CBackGround * CBackGround::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBackGround*		pInstance = new CBackGround(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CBackGround");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBackGround::Clone(void* pArg)
{
	CBackGround*		pInstance = new CBackGround(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Created : CBackGround");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBackGround::Free()
{
	__super::Free();

	Safe_Release(m_pRendererCom);
	delete this;
}

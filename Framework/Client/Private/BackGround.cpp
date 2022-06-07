#include "stdafx.h"
#include "..\Public\BackGround.h"
#include "GameInstance.h"
#include <iostream>

CBackGround::CBackGround()
{

}

CBackGround::CBackGround(const CBackGround & Prototype)
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

	
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_PRIORITY, this);
}

HRESULT CBackGround::Render()
{
	m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CBackGround::SetUp_Components()
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	//Safe_AddRef(pGameInstance);

	/* For.Com_Renderer */ 
	m_pRendererCom = (CRenderer*)pGameInstance->Clone_Component(typeid(CRenderer).name());
	if (nullptr == m_pRendererCom)
		return E_FAIL;

	m_pVIBufferCom = (CVIBuffer_Rect*)pGameInstance->Clone_Component(typeid(CVIBuffer_Rect).name());
	if (nullptr == m_pVIBufferCom)
		return E_FAIL;


	//Safe_Release(pGameInstance);
	return S_OK;
}

CBackGround * CBackGround::Create()
{
	CBackGround*		pInstance = new CBackGround();

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

	//Safe_Release(m_pRendererCom);
	Safe_Release(m_pVIBufferCom);
	delete this;
}

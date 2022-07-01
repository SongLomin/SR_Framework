#include "stdafx.h"
#include "..\Public\Terrain.h"
#include "GameInstance.h"

CTerrain::CTerrain(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{

}

CTerrain::CTerrain(const CTerrain & Prototype)
	: CGameObject(Prototype)
{
}

HRESULT CTerrain::Initialize_Prototype()
{
	/* 백엔드로부터 값ㅇ를 어덩오낟. */

	return S_OK;
}

HRESULT CTerrain::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;


	
	return S_OK;
}

void CTerrain::Tick(_float fTimeDelta)
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();

	Safe_AddRef(pGameInstance);

	_float3		vPickedPos;


	Safe_Release(pGameInstance);
}

void CTerrain::LateTick(_float fTimeDelta)
{
	if (nullptr == m_pRendererCom)
		return;

	
	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
}

HRESULT CTerrain::Render()
{
	if (FAILED(m_pTextureCom->Bind_Texture(0)))
		return E_FAIL;

	m_pTransformCom->Bind_WorldMatrix();	

	m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CTerrain::SetUp_Components()
{
	/* For.Com_Renderer */ 
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), TEXT("Com_Renderer"), (CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_VIBuffer_Terrain"), TEXT("Com_VIBuffer"), (CComponent**)&m_pVIBufferCom)))
		return E_FAIL;	

	/* For.Com_Texture */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Terrain"), TEXT("Com_Texture"), (CComponent**)&m_pTextureCom)))
		return E_FAIL;

	/* For.Com_Transform */
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.fSpeedPerSec = 5.0f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);	

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Transform"), TEXT("Com_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc)))
		return E_FAIL;
	
	
	return S_OK;
}

CTerrain * CTerrain::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CTerrain*		pInstance = new CTerrain(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CTerrain");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CTerrain::Clone(void* pArg)
{
	CTerrain*		pInstance = new CTerrain(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Created : CTerrain");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTerrain::Free()
{
	__super::Free();

	Safe_Release(m_pTransformCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
}

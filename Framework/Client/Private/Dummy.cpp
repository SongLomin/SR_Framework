#include "stdafx.h"
#include "..\Public\Dummy.h"
#include "GameInstance.h"

CDummy* CDummy::Create()
{
	CDummy* pInstance = new CDummy();

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CBackGround");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CDummy::Clone(void* pArg)
{
	CDummy* pInstance = new CDummy();

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Created : CBackGround");
		Safe_Release(pInstance);
	}

	return pInstance;
}



CDummy::CDummy(const CDummy& Prototype)
{
	*this = Prototype;
}

HRESULT CDummy::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CDummy::Initialize(void* pArg)
{
	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);

	m_pTransformCom = Add_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);

	m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(2.f, 0.f, 0.f));

	return S_OK;
}

void CDummy::Tick(_float fTimeDelta)
{

}

void CDummy::LateTick(_float fTimeDelta)
{
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_PRIORITY, this);
}

HRESULT CDummy::Render()
{
	m_pTransformCom->Bind_WorldMatrix();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pRendererCom->Update_Textures(1);
	m_pVIBufferCom->Render();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}

void CDummy::Free()
{
	__super::Free();
	delete this;
}
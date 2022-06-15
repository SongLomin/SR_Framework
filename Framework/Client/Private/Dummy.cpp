#include "stdafx.h"
#include "..\Public\Dummy.h"
#include "GameInstance.h"

CDummy* CDummy::Create()
{
	CREATE_PIPELINE(CDummy);
}

CGameObject* CDummy::Clone(void* pArg)
{
	CLONE_PIPELINE(CDummy);
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

	m_pRendererCom->Set_Textures_From_Key(TEXT("Test"),MEMORY_TYPE::MEMORY_DYNAMIC);

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

	m_pRendererCom->Bind_Texture(1);
	m_pVIBufferCom->Render();
	m_pRendererCom->UnBind_Texture();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}

void CDummy::Free()
{
	__super::Free();
	delete this;
}
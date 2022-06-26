#include "stdafx.h"
#include "Logo.h"
#include "GameInstance.h"


CLogo::CLogo(const CLogo& Prototype)
{
	*this = Prototype;
}

HRESULT CLogo::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CLogo::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	

	return S_OK;
}

void CLogo::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

}

void CLogo::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_UI, this);
}

HRESULT CLogo::Render()
{
	__super::Render();

	m_pTransformCom->Bind_WorldMatrix();


	m_pRendererCom->Bind_Texture(0);
	m_pVIBufferCom->Render();

	m_pRendererCom->UnBind_Texture();

	

	return S_OK;
}

HRESULT CLogo::SetUp_Components()
{
	Add_Component<CTransform>();

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);
	m_pRendererCom->Set_Textures_From_Key(TEXT("Logo"), MEMORY_TYPE::MEMORY_STATIC);


	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(0.f, 0.f, 0.f));
	m_pTransformCom->Scaling(_float3(1.f, 1.f, 1.f));
	
	return S_OK;
}

CLogo* CLogo::Create()
{
	CREATE_PIPELINE(CLogo);
}

CGameObject* CLogo::Clone(void* pArg)
{
	CLONE_PIPELINE(CLogo);
}

void CLogo::Free()
{
	__super::Free();

	delete this;
}

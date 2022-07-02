#include "stdafx.h"
#include "Loading.h"
#include "GameInstance.h"


CLoading::CLoading(const CLoading& Prototype)
{
	*this = Prototype;
}

HRESULT CLoading::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CLoading::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;



	return S_OK;
}

void CLoading::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

}

void CLoading::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_UI, this);
}

HRESULT CLoading::Render()
{
	__super::Render();

	m_pTransformCom->Bind_WorldMatrix();


	m_pRendererCom->Bind_Texture(0);
	m_pVIBufferCom->Render();

	m_pRendererCom->UnBind_Texture();



	return S_OK;
}

HRESULT CLoading::SetUp_Components()
{
	Add_Component<CTransform>();

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);
	m_pRendererCom->Set_Textures_From_Key(TEXT("Loading"), MEMORY_TYPE::MEMORY_STATIC);


	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(0.f, 0.f, 0.f));
	m_pTransformCom->Scaling(_float3(2.f, 2.f, 1.f));

	return S_OK;
}

CLoading* CLoading::Create()
{
	CREATE_PIPELINE(CLoading);
}

CGameObject* CLoading::Clone(void* pArg)
{
	CLONE_PIPELINE(CLoading);
}

void CLoading::Free()
{
	__super::Free();

	delete this;
}


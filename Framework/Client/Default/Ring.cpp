#include "stdafx.h"
#include "Ring.h"
#include "GameInstance.h"

CRing::CRing()
{
}

CRing::CRing(const CRing& Prototype)
{
	*this = Prototype;
}

HRESULT CRing::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CRing::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);


	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);

	m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(4.f, 2.0f, 0.f));
	m_pTransformCom->Scaling(_float3(0.5f, 0.5f, 0.5f));


	return S_OK;
}

void CRing::Tick(_float fTimeDelta)
{
	m_pTransformCom->Go_BackAndForth(5.f, fTimeDelta);
	m_pTransformCom->Turn(_float3(0.f, 1.f, 0.f), -1.f,fTimeDelta);
}

void CRing::LateTick(_float fTimeDelta)
{
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CRing::Render()
{
	m_pTransformCom->Bind_WorldMatrix();

	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pRendererCom->Bind_Texture(1);
	m_pVIBufferCom->Render();
	m_pRendererCom->UnBind_Texture();

	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}



inline HRESULT CRing::SetUp_Components()
{
	//CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	/*CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.fSpeedPerSec = 8.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(600.f);*/

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr((void**)&m_pTransformCom);

	return S_OK;
}



CRing* CRing::Create()
{
	CREATE_PIPELINE(CRing);
}

CGameObject* CRing::Clone(void* pArg)
{
	CLONE_PIPELINE(CRing);
}

void CRing::Free()
{
	__super::Free();

	delete this;
}

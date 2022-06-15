#include "stdafx.h"
#include "Posin.h"
#include "GameInstance.h"

CPosin::CPosin()
{
}

CPosin::CPosin(const CPosin& Prototype)
{
	*this = Prototype;
}

HRESULT CPosin::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CPosin::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);


	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);

	m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(2.f, 1.5f, 0.f));
	m_pTransformCom->Scaling(_float3(0.5f, 0.5f, 0.5f));
	

	return S_OK;
}

void CPosin::Tick(_float fTimeDelta)
{
    if (GetKeyState('A') & 0x8000)
	    m_pTransformCom->Turn(_float3(0.f, 1.f, 0.f), fTimeDelta);
    
	if (GetKeyState('D') & 0x8000)
		m_pTransformCom->Turn(_float3(0.f, 1.f, 0.f), fTimeDelta * -1);

	
}

void CPosin::LateTick(_float fTimeDelta)
{
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CPosin::Render()
{
	m_pTransformCom->Bind_WorldMatrix();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pRendererCom->Bind_Texture(1);
	m_pVIBufferCom->Render();
	m_pRendererCom->UnBind_Texture();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}



inline HRESULT CPosin::SetUp_Components()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.fSpeedPerSec = 100.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(250.0f);

	m_pTransformCom = Add_Component<CTransform>(&TransformDesc);
	m_pTransformCom->Set_WeakPtr((void**)&m_pTransformCom);

	return S_OK;
}

void CPosin::LookAt_CamTPS()
{
}

CPosin* CPosin::Create()
{
	CPosin* pInstance = new CPosin();

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CPosin");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CPosin::Clone(void* pArg)
{
	CPosin* pInstance = new CPosin();

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CPosin");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPosin::Free()
{
	__super::Free();

	delete this;
}

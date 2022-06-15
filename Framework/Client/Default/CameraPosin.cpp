#include "stdafx.h"
#include "CameraPosin.h"
#include "GameInstance.h"

CCameraPosin::CCameraPosin()
{
}

CCameraPosin::CCameraPosin(const CCameraPosin& Prototype)
{
	*this = Prototype;
}

HRESULT CCameraPosin::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCameraPosin::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);


	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);

	m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(0.f, 2.f, 0.f));
	m_pTransformCom->Scaling(_float3(0.5f, 0.5f, 0.5f));
	return S_OK;

}

void CCameraPosin::Tick(_float fTimeDelta)
{
	LookAt_CamTPS();
}

void CCameraPosin::LateTick(_float fTimeDelta)
{
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_PRIORITY, this);

}

HRESULT CCameraPosin::Render()
{
	m_pTransformCom->Bind_WorldMatrix();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pRendererCom->Bind_Texture(1);
	m_pVIBufferCom->Render();
	m_pRendererCom->UnBind_Texture();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}

void CCameraPosin::Link_CameraTransfrom(CTransform* pTransform)
{
	m_pCameraTransformCom = pTransform;

	m_pCameraTransformCom->Set_WeakPtr(&m_pTransformCom);
}

HRESULT CCameraPosin::SetUp_Components()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.fSpeedPerSec = 100.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(250.0f);

	m_pTransformCom = Add_Component<CTransform>(&TransformDesc);
	m_pTransformCom->Set_WeakPtr((void**)&m_pTransformCom);

	return S_OK;
}

void CCameraPosin::LookAt_CamTPS()
{
	m_pTransformCom->LookAt(m_pCameraTransformCom);
}

CCameraPosin* CCameraPosin::Create()
{
	CCameraPosin* pInstance = new CCameraPosin();

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CCameraPosin");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CCameraPosin::Clone(void* pArg)
{
	CCameraPosin* pInstance = new CCameraPosin();

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CCameraPosin");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCameraPosin::Free()
{
	__super::Free();

	delete this;
}

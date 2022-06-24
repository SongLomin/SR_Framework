#include "stdafx.h"
#include "TargetingBox.h"
#include "GameInstance.h"

CTargetingBox::CTargetingBox()
{
}

CTargetingBox::CTargetingBox(const CTargetingBox& Prototype)
{
	*this = Prototype;

	Add_Component<CTransform>();
}

HRESULT CTargetingBox::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CTargetingBox::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;


	return S_OK;
}

void CTargetingBox::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

}

void CTargetingBox::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);


	LookAtCamera();


	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CTargetingBox::Render()
{

	m_pTransformCom->Bind_WorldMatrix();

	m_pRendererCom->Bind_Texture(0);

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 250);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pVIBufferCom->Render();

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);


	m_pRendererCom->UnBind_Texture();

	return S_OK;
}


HRESULT CTargetingBox::SetUp_Components()
{
	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);
	m_pRendererCom->Set_Textures_From_Key(TEXT("Targeting"), MEMORY_TYPE::MEMORY_STATIC);


	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);


	return S_OK;
}

void CTargetingBox::LookAtCamera()
{
	_float4x4		ViewMatrix;

	DEVICE->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	_float3 Scaled = m_pTransformCom->Get_Scaled();

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, *(_float3*)&ViewMatrix.m[0][0],true);
	m_pTransformCom->Set_State(CTransform::STATE_UP, *(_float3*)&ViewMatrix.m[1][0],true);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, *(_float3*)&ViewMatrix.m[2][0],true);

	_float3 vWorldPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION, true);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, *(_float3*)&ViewMatrix.m[2][0] * -1.f + vWorldPos,true);

	m_pTransformCom->Scaling(Scaled * 2.5f, true);
}

CTargetingBox* CTargetingBox::Create()
{
	CREATE_PIPELINE(CTargetingBox);
}

CGameObject* CTargetingBox::Clone(void* pArg)
{
	CLONE_PIPELINE(CTargetingBox);

}

void CTargetingBox::Free()
{
	__super::Free();


	delete this;
}

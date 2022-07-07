#include "stdafx.h"
#include "Effect.h"
#include "GameInstance.h"

CEffect::CEffect()
{
}

HRESULT CEffect::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CEffect::Initialize(void* pArg)
{


	return S_OK;
}

void CEffect::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	LookAtCamera();
}

void CEffect::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
}

HRESULT CEffect::Render_Begin(ID3DXEffect** Shader)
{
	return S_OK;
}

HRESULT CEffect::Render()
{
	m_pTransformCom->Scaling(_float3(15.f, 15.f, 15.f), true);
	m_pTransformCom->Bind_WorldMatrix();


	m_pRendererCom->Bind_Texture(m_iTexture_Min);

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 0);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	__super::Render();


	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pRendererCom->UnBind_Texture();

	return S_OK;
}

void CEffect::Set_Pos(_float3 _Pos)
{
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _Pos);
}

void CEffect::LookAtCamera()
{

	_float4x4		ViewMatrix;

	DEVICE->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	_float3 Scaled = m_pTransformCom->Get_Scaled();

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, *(_float3*)&ViewMatrix.m[0][0], true);
	m_pTransformCom->Set_State(CTransform::STATE_UP, *(_float3*)&ViewMatrix.m[1][0], true);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, *(_float3*)&ViewMatrix.m[2][0], true);

	_float3 vWorldPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION, true);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, *(_float3*)&ViewMatrix.m[2][0] * -1.f + vWorldPos, true);

	m_pTransformCom->Scaling(Scaled * 3.5f, true);

}

HRESULT CEffect::SetUp_Components()
{
	m_pTransformCom = Add_Component<CTransform>();
	WEAK_PTR(m_pTransformCom);
	m_pRendererCom = Add_Component<CRenderer>();
	WEAK_PTR(m_pRendererCom);


	SetUp_Components_For_Child();
	return S_OK;
}



void CEffect::Free()
{
	__super::Free();
}

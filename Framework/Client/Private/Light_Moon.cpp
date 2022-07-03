#include "stdafx.h"
#include "Light_Moon.h"
#include "GameInstance.h"
#include "Math_Utillity.h"

CLight_Moon::CLight_Moon()
{
}

CLight_Moon::CLight_Moon(const CLight_Moon& Prototype)
{
	*this = Prototype;
}

HRESULT CLight_Moon::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CLight_Moon::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(1.f, 1.f, 300.f));


	return S_OK;
}

void CLight_Moon::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	_float3 CamWorldPos = GAMEINSTANCE->Get_Camera()->Get_Transform()->Get_World_State(CTransform::STATE_POSITION);
	_float3 MyWorldPos;
	MyWorldPos.x = 1.f + CamWorldPos.x;
	MyWorldPos.y = 1.f + CamWorldPos.y;
	MyWorldPos.z = 300.f + CamWorldPos.z;


	m_pTransformCom->Set_State(CTransform::STATE_POSITION, MyWorldPos, true);

}

void CLight_Moon::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);


	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);

	LookAtCamera();

}

HRESULT CLight_Moon::Render()
{
	m_pTransformCom->Scaling(_float3(80.f, 80.f, 50.f), true);

	m_pTransformCom->Bind_WorldMatrix();

	_float3 ScreenPos = _float3(0.f, 0.f, 0.f);

	CMath_Utillity::WorldToScreen(&m_pTransformCom->Get_State(CTransform::STATE_POSITION, true), &ScreenPos);

	_float3 Look = m_pTransformCom->Get_State(CTransform::STATE_LOOK, true);

	/*GAMEINSTANCE->Add_Text(_point{ (LONG)ScreenPos.x, (LONG)ScreenPos.y }, TEXT("%d, %d, %d"), 3, (_uint)Look.x, (_uint)Look.y, (_uint)Look.z);*/

	GAMEINSTANCE->Add_Text(_point{ (LONG)ScreenPos.x + 20, (LONG)ScreenPos.y }, TEXT("Light Test"), 0);

	m_pRendererCom->Bind_Texture(0);

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 253);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pVIBufferCom->Render();

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pRendererCom->UnBind_Texture();



	return S_OK;
}


HRESULT CLight_Moon::SetUp_Components()
{

	Add_Component<CTransform>();

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);
	m_pRendererCom->Set_Textures_From_Key(TEXT("Light_Moon"), MEMORY_TYPE::MEMORY_STATIC);


	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);

	m_pPointLightCom = Add_Component<CPointLight>();
	m_pPointLightCom->Set_WeakPtr(&m_pPointLightCom);
	m_pPointLightCom->Set_Preset_SunLight();

	return S_OK;
}

void CLight_Moon::LookAtCamera()
{
	_float4x4		ViewMatrix;

	DEVICE->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, *(_float3*)&ViewMatrix.m[0][0], true);
	m_pTransformCom->Set_State(CTransform::STATE_UP, *(_float3*)&ViewMatrix.m[1][0], true);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, *(_float3*)&ViewMatrix.m[2][0], true);

}

CLight_Moon* CLight_Moon::Create()
{
	CREATE_PIPELINE(CLight_Moon);
}

CGameObject* CLight_Moon::Clone(void* pArg)
{
	CLONE_PIPELINE(CLight_Moon);
}

void CLight_Moon::Free()
{
	__super::Free();

	RETURN_WEAKPTR(m_pTransformCom);
	RETURN_WEAKPTR(m_pRendererCom);
	RETURN_WEAKPTR(m_pVIBufferCom);

	delete this;
}

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

	CCamera* pCurrentCam = GAMEINSTANCE->Get_Camera();

	ISVALID(pCurrentCam, );

	_float3 CamWorldPos = pCurrentCam->Get_Transform()->Get_World_State(CTransform::STATE_POSITION);
	_float3 MyWorldPos;
	MyWorldPos.x = 1.f + CamWorldPos.x;
	MyWorldPos.y = 1.f + CamWorldPos.y;
	MyWorldPos.z = 300.f + CamWorldPos.z;


	m_pTransformCom->Set_State(CTransform::STATE_POSITION, MyWorldPos, true);

}

void CLight_Moon::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);


	//m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);

	LookAtCamera();

}

HRESULT CLight_Moon::Render()
{
	/*m_pTransformCom->Scaling(_float3(80.f, 80.f, 50.f), true);

	m_pTransformCom->Bind_WorldMatrix();

	m_pRendererCom->Bind_Texture(0);

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 253);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pVIBufferCom->Render();

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pRendererCom->UnBind_Texture();*/



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


	//m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	//m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);

	m_pDirectionalLightCom1 = Add_Component<CDirectionalLight>();
	m_pDirectionalLightCom1->Set_WeakPtr(&m_pDirectionalLightCom1);
	m_pDirectionalLightCom1->Set_Light_Variables(D3DCOLOR_RGBA(255,255,255,255),0.5f,0.8f,1.f,
		_float3(0.f,0.f,0.f),_float3(-1.f,-1.f,-1.f),600.f);
	/*m_pPointLightCom1->Set_Light_Variables(D3DXCOLOR(1.f, 1.f, 1.f, 1.f), 0.3f, 0.5f, 0.6f, _float3(0.f, 0.f, -2.f), D3DXVECTOR3(-1.f, -1.f, -1.f),
		600.f, 1.f, 0.007f, 0.001f, 0.5f, 0.05f, 0.1f);*/


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
	//RETURN_WEAKPTR(m_pVIBufferCom);

	delete this;
}

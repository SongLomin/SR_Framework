#include "stdafx.h"
#include "SkyBox.h"
#include "GameInstance.h"
#include "Level_SelectPlanet.h"
#include "Level_GamePlay.h"
#include "Level_Loading.h"

CSkyBox::CSkyBox()
{
}

CSkyBox::CSkyBox(const CSkyBox& Prototype)
{
	*this = Prototype;

	Add_Component<CTransform>();
}

HRESULT CSkyBox::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CSkyBox::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	return S_OK;
}

void CSkyBox::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


}

void CSkyBox::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	_float4x4		ViewMatrix;
	DEVICE->GetTransform(D3DTS_VIEW, &ViewMatrix);

	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, *(_float3*)&ViewMatrix.m[3][0], true);

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_PRIORITY, this);

}

HRESULT CSkyBox::Render()
{

	m_pTransformCom->Bind_WorldMatrix();

	
	m_pRendererCom->Bind_Texture(7);
	

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	DEVICE->SetRenderState(D3DRS_ZENABLE, FALSE);
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	__super::Render();

	DEVICE->SetRenderState(D3DRS_ZENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	m_pRendererCom->UnBind_Texture();
	return S_OK;
}

HRESULT CSkyBox::SetUp_Components()
{

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);
	m_pRendererCom->Set_Textures_From_Key(TEXT("Sky_Test"), MEMORY_TYPE::MEMORY_STATIC);

	m_pVIBufferCom = Add_Component<CVIBuffer_Cube>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);



	return S_OK;
}

CSkyBox* CSkyBox::Create()
{
	CREATE_PIPELINE(CSkyBox);
}

CGameObject* CSkyBox::Clone(void* pArg)
{
	CLONE_PIPELINE(CSkyBox);
}

void CSkyBox::Free()
{
	__super::Free();

	delete this;
}

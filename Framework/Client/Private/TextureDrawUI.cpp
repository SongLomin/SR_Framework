#include "stdafx.h"
#include "TextureDrawUI.h"
#include "GameInstance.h"

CTextureDrawUI::CTextureDrawUI(const CTextureDrawUI& Prototype)
{
}

HRESULT CTextureDrawUI::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CTextureDrawUI::Initialize(void* pArg)
{
	SetUp_Components();

	m_fSizeX = (g_iWinCX / 4);
	m_fSizeY = (g_iWinCY / 4);
	m_fX = (g_iWinCX / 4) / 2;
	m_fY = (g_iWinCY / 4) / 2;

	return S_OK;
}

void CTextureDrawUI::Tick(_float fTimeDelta) 
{
	__super::Tick(fTimeDelta);
}

void CTextureDrawUI::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pTransformCom->Scaling(_float3(m_fSizeX, m_fSizeY, 1.f));
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_fX - (g_iWinCX >> 1), -m_fY + (g_iWinCY >> 1), 0.f));

	m_pRendererCom->Add_RenderGroup(m_eRenderGroup, this);
}

HRESULT CTextureDrawUI::Render_Begin(ID3DXEffect** Shader)
{
	//m_pTransformCom->Bind_WorldMatrix();
	D3DXHANDLE viewHandle = (*Shader)->GetParameterByName(0, "view");
	D3DXHANDLE projHandle = (*Shader)->GetParameterByName(0, "proj");
	D3DXHANDLE worldHandle = (*Shader)->GetParameterByName(0, "world");

	_float4x4	ViewMatrix;
	D3DXMatrixIdentity(&ViewMatrix);

	(*Shader)->SetMatrix(projHandle, &m_ProjMatrix);
	(*Shader)->SetMatrix(viewHandle, &ViewMatrix);
	(*Shader)->SetMatrix(worldHandle, &m_pTransformCom->Get_WorldMatrix());


	__super::Render_Begin(Shader);

	return S_OK;
}

HRESULT CTextureDrawUI::Render()
{
	//DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//DEVICE->SetRenderState(D3DRS_ALPHAREF, 230);
	//DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

	/*_float4x4 CurView, CurProj;
	DEVICE->GetTransform(D3DTS_VIEW, &CurView);
	DEVICE->GetTransform(D3DTS_PROJECTION, &CurProj);

	_float4x4	ViewMatrix;
	D3DXMatrixIdentity(&ViewMatrix);

	DEVICE->SetTransform(D3DTS_VIEW, &ViewMatrix);
	DEVICE->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);*/

	__super::Render();

	//DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	/*DEVICE->SetTransform(D3DTS_VIEW, &CurView);
	DEVICE->SetTransform(D3DTS_PROJECTION, &CurProj);*/

	return S_OK;
}

void CTextureDrawUI::Set_Option(_float2 _UI_Position, _float2 _UI_Size, RENDERGROUP _eRenderGroup)
{
	m_fSizeX = _UI_Size.x;
	m_fSizeY = _UI_Size.y;
	m_fX = _UI_Position.x;
	m_fY = _UI_Position.y;

	m_eRenderGroup = _eRenderGroup;
}

void CTextureDrawUI::SetUp_Components()
{
	m_pTransformCom = Add_Component<CTransform>();
	WEAK_PTR(m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	WEAK_PTR(m_pRendererCom);

	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	WEAK_PTR(m_pVIBufferCom);

	D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinCX, g_iWinCY, 0.0f, 1.f);
}


CTextureDrawUI* CTextureDrawUI::Create()
{
	CREATE_PIPELINE(CTextureDrawUI);
}

CGameObject* CTextureDrawUI::Clone(void* pArg)
{
	CLONE_PIPELINE(CTextureDrawUI);
}

void CTextureDrawUI::Free()
{
	__super::Free();

	delete this;
}

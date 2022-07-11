#include "stdafx.h"
#include "CharacterLogo.h"
#include "GameInstance.h"

CCharacterLogo::CCharacterLogo(const CCharacterLogo& Prototype)
{
	*this = Prototype;

	m_pTransformCom = Add_Component<CTransform>();
}


HRESULT CCharacterLogo::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCharacterLogo::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinCX, g_iWinCY, 0.0f, 1.f);

	m_fX = 640.f;
	m_fY = 360.f;

	m_fSizeX = 400.f;
	m_fSizeY = 360.f;


	return S_OK;
}

void CCharacterLogo::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	GetCursorPos(&m_ptMouse);
	ScreenToClient(g_hWnd, &m_ptMouse);


	SetRect(&m_rcRect, m_fX - m_fSizeX * 0.5f, m_fY - m_fSizeY * 0.5f,
		m_fX + m_fSizeX * 0.5f, m_fY + m_fSizeY * 0.5f);
}

void CCharacterLogo::LateTick(_float fTimeDelta)
{

	__super::LateTick(fTimeDelta);

	m_pTransformCom->Scaling(_float3(m_fSizeX, m_fSizeY, 1.f) * 2);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_fX - (g_iWinCX >> 1), -m_fY + (g_iWinCY >> 1), 0.f));

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_PRIORITY, this);
}

HRESULT CCharacterLogo::Render()
{
	m_pTransformCom->Bind_WorldMatrix();

	m_pRendererCom->Bind_Texture(0);

	DEVICE->SetRenderState(D3DRS_ZENABLE, FALSE);
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	_float4x4 CurView, CurProj;
	DEVICE->GetTransform(D3DTS_VIEW, &CurView);
	DEVICE->GetTransform(D3DTS_PROJECTION, &CurProj);

	_float4x4	ViewMatrix;
	D3DXMatrixIdentity(&ViewMatrix);

	DEVICE->SetTransform(D3DTS_VIEW, &ViewMatrix);
	DEVICE->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	m_pVIBufferCom->Render();

	m_pRendererCom->UnBind_Texture();

	DEVICE->SetTransform(D3DTS_VIEW, &CurView);
	DEVICE->SetTransform(D3DTS_PROJECTION, &CurProj);


	DEVICE->SetRenderState(D3DRS_ZENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);


	return S_OK;
}

HRESULT CCharacterLogo::SetUp_Components()
{
	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);
	m_pRendererCom->Set_Textures_From_Key(TEXT("Character_Logo"), MEMORY_TYPE::MEMORY_STATIC);

	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);


	return S_OK;
}

CCharacterLogo* CCharacterLogo::Create()
{
	CREATE_PIPELINE(CCharacterLogo);
}

CGameObject* CCharacterLogo::Clone(void* pArg)
{
	CLONE_PIPELINE(CCharacterLogo);
}

void CCharacterLogo::Free()
{
	__super::Free();

	delete this;
}

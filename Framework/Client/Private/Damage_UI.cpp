#include "stdafx.h"
#include "GameInstance.h"
#include "Damage_UI.h"



CDamage_UI::CDamage_UI(const CDamage_UI& Prototype)
{
	*this = Prototype;

	m_pTransformCom = Add_Component<CTransform>();


}

HRESULT CDamage_UI::Initialize_Prototype()
{

	return S_OK;
}

HRESULT CDamage_UI::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinCX, g_iWinCY, 0.0f, 1.f);

	m_fX = 60.f;
	m_fY = 60.f;

	m_fSizeX = 55.0f;
	m_fSizeY = 10.0f;

	return S_OK;
}

void CDamage_UI::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	GetCursorPos(&m_ptMouse);
	ScreenToClient(g_hWnd, &m_ptMouse);


	SetRect(&m_rcRect, m_fX - m_fSizeX * 0.5f, m_fY - m_fSizeY * 0.5f,
		m_fX + m_fSizeX * 0.5f, m_fY + m_fSizeY * 0.5f);

	
	if (KEY_INPUT((KEY::LEFT), KEY_STATE::TAP))
	{
		m_iIndex = max(0, m_iIndex - 1);
	}

	if (KEY_INPUT((KEY::RIGHT), KEY_STATE::TAP))
	{
		m_iIndex = min(3, m_iIndex + 1);
	}

	switch (m_iIndex)
	{
	case 0:
		GAMEINSTANCE->Add_Text(_point{ (LONG)120, (LONG)50 }, D3DCOLOR_ARGB(255, 227, 245, 244), 0.f, TEXT(": 7 (공격력) "), 0);
		break;

	case 1:
		GAMEINSTANCE->Add_Text(_point{ (LONG)120, (LONG)50 }, D3DCOLOR_ARGB(255, 227, 245, 244), 0.f, TEXT(": 5 (공격력) "), 0);
		break;

	case 2:
		GAMEINSTANCE->Add_Text(_point{ (LONG)120, (LONG)50 }, D3DCOLOR_ARGB(255, 227, 245, 244), 0.f, TEXT(": 10 (공격력) "), 0);
		break;

	case 3:
		GAMEINSTANCE->Add_Text(_point{ (LONG)120, (LONG)50 }, D3DCOLOR_ARGB(255, 227, 245, 244), 0.f, TEXT(": 3 (공격력) "), 0);
		break;
	}


	/*if (KEY_INPUT((KEY::LEFT), KEY_STATE::TAP))
	{
		m_bSwitchTaget = false;
	}

	if (KEY_INPUT((KEY::RIGHT), KEY_STATE::TAP))
	{
		m_bSwitchTaget = true;
	}

	if (!m_bSwitchTaget)
	{
		GAMEINSTANCE->Add_Text(_point{ (LONG)120, (LONG)50 }, D3DCOLOR_ARGB(255, 227, 245, 244), 0.f, TEXT(": 7 (공격력) "), 0);
	}

	if (m_bSwitchTaget)
	{
		GAMEINSTANCE->Add_Text(_point{ (LONG)120, (LONG)50 }, D3DCOLOR_ARGB(255, 227, 245, 244), 0.f, TEXT(": 10 (공격력) "), 0);
	}*/


	

}

void CDamage_UI::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pTransformCom->Scaling(_float3(m_fSizeX, m_fSizeY, 1.f) * 2);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_fX - (g_iWinCX >> 1), -m_fY + (g_iWinCY >> 1), 0.f));

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_UI, this);
}

HRESULT CDamage_UI::Render()
{
	m_pTransformCom->Bind_WorldMatrix();

	m_pRendererCom->Bind_Texture(1);

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 120);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	_float4x4 CurView, CurProj;
	DEVICE->GetTransform(D3DTS_VIEW, &CurView);
	DEVICE->GetTransform(D3DTS_PROJECTION, &CurProj);

	_float4x4	ViewMatrix;
	D3DXMatrixIdentity(&ViewMatrix);

	DEVICE->SetTransform(D3DTS_VIEW, &ViewMatrix);
	DEVICE->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	m_pVIBufferCom->Render();

	m_pRendererCom->UnBind_Texture();

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	DEVICE->SetTransform(D3DTS_VIEW, &CurView);
	DEVICE->SetTransform(D3DTS_PROJECTION, &CurProj);

	return S_OK;
}


void CDamage_UI::Link_Status(CStatus* pStatus)
{
	m_pStatusCom = pStatus;
}

HRESULT CDamage_UI::SetUp_Components()
{
	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);
	m_pRendererCom->Set_Textures_From_Key(TEXT("Font_UI"), MEMORY_TYPE::MEMORY_STATIC);

	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);


	return S_OK;
}

CDamage_UI* CDamage_UI::Create()
{
	CREATE_PIPELINE(CDamage_UI);
}

CGameObject* CDamage_UI::Clone(void* pArg)
{
	CLONE_PIPELINE(CDamage_UI);
}

void CDamage_UI::Free()
{
	__super::Free();

	delete this;
}
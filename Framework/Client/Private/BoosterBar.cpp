#include "stdafx.h"
#include "StatusBar.h"
#include "GameInstance.h"
#include "BoosterBar.h"



CBoosterBar::CBoosterBar(const CBoosterBar& Prototype)
{
	*this = Prototype;

	m_pTransformCom = Add_Component<CTransform>();


}

HRESULT CBoosterBar::Initialize_Prototype()
{

	return S_OK;
}

HRESULT CBoosterBar::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinCX, g_iWinCY, 0.0f, 1.f);

	m_fX = 220.f;
	m_fY = 40.f;

	m_fSizeX = 150.0f;
	m_fSizeY = 5.0f;

	return S_OK;
}

void CBoosterBar::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	CCamera* pCurrentCam = GAMEINSTANCE->Get_Camera();

	ISVALID(pCurrentCam, );

	CTransform* TransformCom = pCurrentCam->Get_Target();


	if (TransformCom)
	{
		CStatus* pPlayerStatusCom = TransformCom->Get_Owner()->Get_Component<CStatus>();

		if (KEY_INPUT(KEY::LSHIFT, KEY_STATE::HOLD))
		{
			m_fX -= 0.5f;
			m_fSizeX -= 0.5f;

			if (m_fX <= 0 || m_fSizeX <= 0)
			{
				m_fX = 71;
				m_fSizeX = 1;
			}
		}

		if (KEY_INPUT(KEY::LSHIFT, KEY_STATE::NONE))
		{
			
			if (m_fX >= 220.f)
			{
				m_fX = 220.f;
			}

			if (m_fSizeX >= 150.f)
			{
				m_fSizeX = 150.f;
			}

			else 
			{
				m_fX += 0.5f;
				m_fSizeX += 0.5f;
			}
			
		}
	}


	GetCursorPos(&m_ptMouse);
	ScreenToClient(g_hWnd, &m_ptMouse);
	SetRect(&m_rcRect, m_fX - m_fSizeX * 0.5f, m_fY - m_fSizeY * 0.5f,
		m_fX + m_fSizeX * 0.5f, m_fY + m_fSizeY * 0.5f);



	m_pTransformCom->Scaling(_float3(m_fSizeX, m_fSizeY, 1.f) * 2);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_fX - (g_iWinCX >> 1), -m_fY + (g_iWinCY >> 1), 0.f));
}

void CBoosterBar::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pTransformCom->Scaling(_float3(m_fSizeX, m_fSizeY, 1.f) * 2);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_fX - (g_iWinCX >> 1), -m_fY + (g_iWinCY >> 1), 0.f));

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_UI, this);
}

HRESULT CBoosterBar::Render()
{
	m_pTransformCom->Bind_WorldMatrix();

	m_pRendererCom->Bind_Texture(0);

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


HRESULT CBoosterBar::SetUp_Components()
{
	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);
	m_pRendererCom->Set_Textures_From_Key(TEXT("Booster"), MEMORY_TYPE::MEMORY_STATIC);

	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);


	return S_OK;
}

CBoosterBar* CBoosterBar::Create()
{
	CREATE_PIPELINE(CBoosterBar);
}

CGameObject* CBoosterBar::Clone(void* pArg)
{
	CLONE_PIPELINE(CBoosterBar);
}

void CBoosterBar::Free()
{
	__super::Free();

	delete this;
}


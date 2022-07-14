#include "stdafx.h"
#include "UI.h"
#include "GameInstance.h"


CUI::CUI()
{
}

HRESULT CUI::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CUI::Initialize(void* pArg)
{
	return S_OK;
}

void CUI::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	GetCursorPos(&m_ptMouse);
	ScreenToClient(g_hWnd, &m_ptMouse);

	if (m_bMove)
	{
		switch (m_eMoveDir)
		{
		case MOVE_UI_DIR::MOVE_UI_END:
			m_bMove = false;
			break;

		case MOVE_UI_DIR::MOVE_UI_RIGHT:
			m_fX += m_fMovement;

			if (m_fX >= m_fEndPos)
			{
				m_bMove = false;
			}
			break;

		case MOVE_UI_DIR::MOVE_UI_LEFT:
			m_fX -= m_fMovement;

			if (m_fX <= m_fEndPos)
			{
				m_bMove = false;
			}
			break;

		case MOVE_UI_DIR::MOVE_UI_UP:
			m_fY -= m_fMovement;

			if (m_fY <= m_fEndPos)
			{
				m_bMove = false;
			}
			break;

		case MOVE_UI_DIR::MOVE_UI_DOWN:
			m_fY += m_fMovement;

			if (m_fY >= m_fEndPos)
			{
				m_bMove = false;
			}
			break;
		}
	}

	SetRect(&m_rcRect, m_fX - m_fSizeX * 0.5f, m_fY - m_fSizeY * 0.5f,
		m_fX + m_fSizeX * 0.5f, m_fY + m_fSizeY * 0.5f);

}

void CUI::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pTransformCom->Scaling(_float3(m_fSizeX, m_fSizeY, 1.f) * 2);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_fX - (g_iWinCX >> 1), -m_fY + (g_iWinCY >> 1), 0.f));

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_UNDER_UI, this);
}

HRESULT CUI::Render()
{
	m_pTransformCom->Bind_WorldMatrix();

	m_pRendererCom->Bind_Texture(m_iTextureIndex);

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, m_iAlphaValue);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);


	_float4x4 CurView, CurProj;
	DEVICE->GetTransform(D3DTS_VIEW, &CurView);
	DEVICE->GetTransform(D3DTS_PROJECTION, &CurProj);

	_float4x4	ViewMatrix;
	D3DXMatrixIdentity(&ViewMatrix);

	DEVICE->SetTransform(D3DTS_VIEW, &ViewMatrix);
	DEVICE->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	__super::Render();


	m_pRendererCom->UnBind_Texture();



	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	DEVICE->SetTransform(D3DTS_VIEW, &CurView);
	DEVICE->SetTransform(D3DTS_PROJECTION, &CurProj);

	return S_OK;
}

HRESULT CUI::SetUp_Components()
{
	m_pTransformCom = Add_Component<CTransform>();
	WEAK_PTR(m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	WEAK_PTR(m_pRendererCom);

	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	WEAK_PTR(m_pVIBufferCom);

	SetUp_Components_For_Child();
	return S_OK;
}

void CUI::SetUp_Varialbes_For_Child(_float _fX, _float _fY, _float _fSizeX, _float _fSizeY, _uint TextureIndex, _uint AlphaValue)
{
	m_fX = _fX;
	m_fY = _fY;
	m_fSizeX = _fSizeX;
	m_fSizeY = _fSizeY;

	m_iTextureIndex = TextureIndex;
	m_iAlphaValue = AlphaValue;

	D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinCX, g_iWinCY, 0.0f, 1.f);
}

void CUI::Set_Texture_Key(_tchar* _Text, MEMORY_TYPE _MemoryType)
{
	m_pRendererCom->Set_Textures_From_Key(_Text, _MemoryType);
}

void CUI::Moving_UI(MOVE_UI_DIR _Dir, _float _movement, _float _EndPos)
{
	m_bMove = true;
	m_eMoveDir = _Dir;
	m_fEndPos = _EndPos;
	m_fMovement = _movement;
}


void CUI::Free()
{
	__super::Free();
}

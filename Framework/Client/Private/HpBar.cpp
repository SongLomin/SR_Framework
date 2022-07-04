#include "stdafx.h"
#include "StatusBar.h"
#include "GameInstance.h"
#include "HpBar.h"



CHpBar::CHpBar(const CHpBar& Prototype)
{
	*this = Prototype;

	m_pTransformCom = Add_Component<CTransform>();


}

HRESULT CHpBar::Initialize_Prototype()
{

	return S_OK;
}

HRESULT CHpBar::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinCX, g_iWinCY, 0.0f, 1.f);

	m_fX = 220.f;
	m_fY = 50.f;

	m_fSizeX = 150.0f;
	m_fSizeY = 5.0f;

	

	return S_OK;
}

void CHpBar::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	CTransform* TransformCom =  GAMEINSTANCE->Get_Camera()->Get_Target();

	// HP 10  fx = 220, 22  m_fSizeX = 150  15
	if (TransformCom)
	{
		CStatus* pPlayerStatusCom = TransformCom->Get_Owner()->Get_Component<CStatus>();



		if (pPlayerStatusCom->Get_Status().fHp == 10)
		{
			m_fX = 220;
			m_fSizeX = 150;
		}

		 if (pPlayerStatusCom->Get_Status().fHp == 9)
		{

		 if (m_fX <= 205 || m_fSizeX <= 135)
			 {
				 m_fX = 205;
				 m_fSizeX = 135;
			 }
			
		 else
			 m_fX -= 0.3;
			 m_fSizeX -= 0.3;
		}

		 if (pPlayerStatusCom->Get_Status().fHp == 8)
		 {
			 if (m_fX <= 190 || m_fSizeX <= 120)
			 {
				 m_fX = 190;
				 m_fSizeX = 120;
			 }

			 else
				 m_fX -= 0.3;
			 m_fSizeX -= 0.3;
		 }

		 if (pPlayerStatusCom->Get_Status().fHp == 7)
		 {

			 if (m_fX <= 175 || m_fSizeX <= 105)
			 {
				 m_fX = 175;
				 m_fSizeX = 105;
			 }

			 else
				 m_fX -= 0.3;
			 m_fSizeX -= 0.3;
		
		 }

		 if (pPlayerStatusCom->Get_Status().fHp == 6)
		 {
			 if (m_fX <= 160 || m_fSizeX <= 90)
			 {
				 m_fX = 160;
				 m_fSizeX = 90;
			 }

			 else
				 m_fX -= 0.3;
			 m_fSizeX -= 0.3;

		 }

		 if (pPlayerStatusCom->Get_Status().fHp == 5)
		 {

			 if (m_fX <= 145 || m_fSizeX <= 75)
			 {
				 m_fX = 145;
				 m_fSizeX = 75;
			 }

			 else
				 m_fX -= 0.3;
			 m_fSizeX -= 0.3;
		
		 }

		 if (pPlayerStatusCom->Get_Status().fHp == 4)
		 {

			 if (m_fX <= 130 || m_fSizeX <= 60)
			 {
				 m_fX = 130;
				 m_fSizeX = 60;
			 }

			 else
				 m_fX -= 0.3;
			 m_fSizeX -= 0.3;
		
		 }

		 if (pPlayerStatusCom->Get_Status().fHp == 3)
		 {
			 if (m_fX <= 115 || m_fSizeX <= 45)
			 {
				 m_fX = 115;
				 m_fSizeX = 45;
			 }

			 else
				 m_fX -= 0.3;
			 m_fSizeX -= 0.3;
		 }

		 if (pPlayerStatusCom->Get_Status().fHp == 2)
		 {
			 if (m_fX <= 100 || m_fSizeX <= 30)
			 {
				 m_fX = 100;
				 m_fSizeX = 30;
			 }

			 else
				 m_fX -= 0.3;
			 m_fSizeX -= 0.3;
		 }

		 if (pPlayerStatusCom->Get_Status().fHp == 1)
		 {
			 if (m_fX <= 85 || m_fSizeX <= 15)
			 {
				 m_fX = 85;
				 m_fSizeX = 15;
			 }

			 else
				 m_fX -= 0.3;
			 m_fSizeX -= 0.3;
		 }

		 if (pPlayerStatusCom->Get_Status().fHp == 0)
		 {
			 if (m_fX <= 70 || m_fSizeX <= 0)
			 {
				 m_fX = 70;
				 m_fSizeX = 0;
			 }

			 else
				 m_fX -= 0.3;
			 m_fSizeX -= 0.3;
		 }


		
	}

	
	m_pTransformCom->Scaling(_float3(m_fSizeX, m_fSizeY, 1.f) * 2);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_fX - (g_iWinCX >> 1), -m_fY + (g_iWinCY >> 1), 0.f));

	

	//몬스터의 스테이터스를 가져올 수 있다.
	//CStatus* pMonsterStatusCom = m_pTransformCom->Get_Parent()->Get_Owner()->Get_Component<CStatus>();
	
	

	GetCursorPos(&m_ptMouse);
	ScreenToClient(g_hWnd, &m_ptMouse);
	SetRect(&m_rcRect, m_fX - m_fSizeX * 0.5f, m_fY - m_fSizeY * 0.5f,
		m_fX + m_fSizeX * 0.5f, m_fY + m_fSizeY * 0.5f);

}

void CHpBar::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_UI, this);
}

HRESULT CHpBar::Render()
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




void CHpBar::Update_Hp_Bar(CStatus* pStatus)
{
	m_pStatusCom = pStatus;
}

HRESULT CHpBar::SetUp_Components()
{
	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);
	m_pRendererCom->Set_Textures_From_Key(TEXT("HP"), MEMORY_TYPE::MEMORY_STATIC);

	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);

	


	return S_OK;
}

CHpBar* CHpBar::Create()
{
	CREATE_PIPELINE(CHpBar);
}

CGameObject* CHpBar::Clone(void* pArg)
{
	CLONE_PIPELINE(CHpBar);
}

void CHpBar::Free()
{
	__super::Free();

	delete this;
}


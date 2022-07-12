#include "stdafx.h"
#include "GPS.h"
#include "GameInstance.h"
#include "Math_Utillity.h"

CGPS::CGPS()
{
}


HRESULT CGPS::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CGPS::Initialize(void* pArg)
{
	D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinCX, g_iWinCY, 0.0f, 1.f);
	
	m_fX = 0.f;
	m_fY = 0.f;
	m_fSizeX = 25.0f;
	m_fSizeY = 25.0f;
	
	SetRect(&m_rcGPSBox, m_fX - m_fSizeX * 0.5f, m_fY - m_fSizeY * 0.5f,
		m_fX + m_fSizeX * 0.5f, m_fY + m_fSizeY * 0.5f);

	return S_OK;
}

void CGPS::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	
	Culling();

	if(m_bCulling)
		SetRect(&m_rcGPSBox, m_fX - m_fSizeX * 0.5f, m_fY - m_fSizeY * 0.5f,
			m_fX + m_fSizeX * 0.5f, m_fY + m_fSizeY * 0.5f);

	//if (!m_bCulling)
	//	m_pTransformCom->Add_Position(_float3(0.f, 1.f, 0.f), true);

}

void CGPS::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);


	if(!m_bCulling)
		LookAtCamera();

	if (m_bCulling)
	{
		m_pTransformCom->Scaling(_float3(m_fSizeX, m_fSizeY, 1.f) * 2.f);
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_fX - (g_iWinCX >> 1), -m_fY + (g_iWinCY >> 1), 0.f));
	}

	
	
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_UI, this);
}

HRESULT CGPS::Render()
{

	if (m_bCulling)
	{
		m_pTransformCom->Bind_WorldMatrix();

		m_pRendererCom->Bind_Texture(0);


		DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		DEVICE->SetRenderState(D3DRS_ALPHAREF, 120);
		DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

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
	else if (!m_bCulling)
	{
		m_pTransformCom->Bind_WorldMatrix();

		m_pRendererCom->Bind_Texture(0);

		DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		DEVICE->SetRenderState(D3DRS_ALPHAREF, 250);
		DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

		m_pVIBufferCom->Render();

		DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);


		m_pRendererCom->UnBind_Texture();

		return S_OK;
	}
}


HRESULT CGPS::SetUp_Components()
{
	m_pTransformCom = Add_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);


	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);
	//m_pRendererCom->Set_Textures_From_Key(TEXT("Aim_Default"), MEMORY_TYPE::MEMORY_STATIC);

	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);

	SetUp_For_Child();
	return S_OK;
}

void CGPS::SetUp_Varialbes_For_Child(GPS_TYPE _Type, _tchar* TextureTag)
{
	m_eType = _Type;


	m_pRendererCom->Set_Textures_From_Key(TextureTag, MEMORY_TYPE::MEMORY_STATIC);
}


void CGPS::LookAtCamera()
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
	m_pTransformCom->Scaling(Scaled / 2.f, true);
}

void CGPS::Culling()
{

	_float3 MyPos = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);
	//_float3 MyPos = m_pTransformCom->Get_Owner()->Get_Component<CTransform>()->Get_World_State(CTransform::STATE_POSITION);

	if (!GAMEINSTANCE->IsIn(&MyPos))
	{
		_uint WinCX = GAMEINSTANCE->Get_Graphic_Desc().iWinCX;
		_uint WinCY = GAMEINSTANCE->Get_Graphic_Desc().iWinCY;

		CMath_Utillity::WorldToScreen(&MyPos, &MyPos);
		MyPos.z = 0.f;

		_float CullingX = max(min(MyPos.x, 1200.f), 0.f);
		_float CullingY = max(min(MyPos.y, 680.f), 0.f);

		m_bCulling = true;
		m_fX = CullingX;
		m_fY = CullingY;

	}
	else
	{
		m_bCulling = false;
	}

	int i = 10;
}


void CGPS::Free()
{
	__super::Free();

}

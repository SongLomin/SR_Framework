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

	//m_pTransformCom->Add_Position(_float3(0.f, 5.f, 0.f), true);

	SetRect(&m_rcGPSBox, m_fX - m_fSizeX * 0.5f, m_fY - m_fSizeY * 0.5f,
		m_fX + m_fSizeX * 0.5f, m_fY + m_fSizeY * 0.5f);

	
}

void CGPS::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pTransformCom->Set_World_State(CTransform::STATE_RIGHT, _float3(1.f, 0.f, 0.f));
	m_pTransformCom->Set_World_State(CTransform::STATE_UP, _float3(0.f, 1.f, 0.f));
	m_pTransformCom->Set_World_State(CTransform::STATE_LOOK, _float3(0.f, 0.f, 1.f));

	m_pTransformCom->Scaling(_float3(m_fSizeX, m_fSizeY, 1.f), true);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_fX - (g_iWinCX >> 1), -m_fY + (g_iWinCY >> 1), 0.f), true);

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

		__super::Render();


		m_pRendererCom->UnBind_Texture();

		DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		DEVICE->SetTransform(D3DTS_VIEW, &CurView);
		DEVICE->SetTransform(D3DTS_PROJECTION, &CurProj);

		return S_OK;
	}
}


HRESULT CGPS::SetUp_Components()
{
	m_pTransformCom = Add_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);


	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);

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



void CGPS::Culling()
{

	_float3 MyPos = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);
	

	CTransform* CameraTransform = GAMEINSTANCE->Get_Camera(CURRENT_CAMERA)->Get_Transform();
	

	if (!GAMEINSTANCE->IsIn(&MyPos))
	{
		_uint WinCX = GAMEINSTANCE->Get_Graphic_Desc().iWinCX;
		_uint WinCY = GAMEINSTANCE->Get_Graphic_Desc().iWinCY;

		_float3 CameraPos = CameraTransform->Get_World_State(CTransform::STATE_POSITION);
		_float3 CameraLook = CameraTransform->Get_World_State(CTransform::STATE_LOOK);
		D3DXVec3Normalize(&CameraLook, &CameraLook);

		_float3 CameraToMyPos = MyPos - CameraPos;

		_float Dotproduct = D3DXVec3Dot(&CameraLook, &CameraToMyPos);

		CMath_Utillity::WorldToScreen(&MyPos, &MyPos);
		_float CullingX = max(min(MyPos.x, 1200.f), 20.f);
		m_fX = CullingX;

		if (Dotproduct < 0.f)
		{
			m_fY = 680.f;
		}
		else
		{
			_float CullingY = max(min(MyPos.y, 680.f), 20.f);
			m_fY = CullingY;
		}

		m_bCulling = true;
	}
	else
	{
		m_bCulling = false;
	}

}


void CGPS::Free()
{
	__super::Free();

}

void CGPS::OnDisable()
{
	printf("È£Ãâ");
}

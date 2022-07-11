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
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinCX, g_iWinCY, 0.0f, 1.f);

	m_fX = m_ptMouse.x;
	m_fY = m_ptMouse.y;
	m_fSizeX = 50.0f;
	m_fSizeY = 50.0f;

	SetRect(&m_rcGPSBox, m_fX - m_fSizeX * 0.5f, m_fY - m_fSizeY * 0.5f,
		m_fX + m_fSizeX * 0.5f, m_fY + m_fSizeY * 0.5f);

	return S_OK;
}

void CGPS::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	
	m_pCurrentCamera = GAMEINSTANCE->Get_Camera(CURRENT_CAMERA)->Get_Transform();
	WEAK_PTR(m_pCurrentCamera);

	switch (m_eType)
	{
	case GPS_TYPE::GPS_FRIENDLY:
		Friendly_GPS();
		break;

	case GPS_TYPE::GPS_ENEMY:
		Enemy_GPS();
		break;
	}
	
	RETURN_WEAKPTR(m_pCurrentCamera);
}

void CGPS::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_UI, this);
}

HRESULT CGPS::Render()
{
	m_pTransformCom->Bind_WorldMatrix();

	m_pRendererCom->Bind_Texture(0);


	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	_float4x4 CurView, CurProj;
	DEVICE->GetTransform(D3DTS_VIEW, &CurView);
	DEVICE->GetTransform(D3DTS_PROJECTION, &CurProj);

	_float4x4	ViewMatrix;
	D3DXMatrixIdentity(&ViewMatrix);

	DEVICE->SetTransform(D3DTS_VIEW, &ViewMatrix);
	DEVICE->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	m_pVIBufferCom->Render();

	m_pRendererCom->UnBind_Texture();

	//DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	DEVICE->SetTransform(D3DTS_VIEW, &CurView);
	DEVICE->SetTransform(D3DTS_PROJECTION, &CurProj);

	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	return S_OK;
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


	return S_OK;
}

void CGPS::SetUp_Varialbes_For_Child(GPS_TYPE _Type, _tchar* TextureTag)
{
	m_eType = _Type;



	m_pRendererCom->Set_Textures_From_Key(TextureTag, MEMORY_TYPE::MEMORY_STATIC);
}

void CGPS::Enemy_GPS()
{
	auto Monster = GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("Monster"));

	for (auto& elem : *Monster)
	{
		if (!GAMEINSTANCE->IsIn(&elem->Get_Component<CTransform>()->Get_World_State(CTransform::STATE_POSITION)))
		{

			_float3 CameraPos = m_pCurrentCamera->Get_World_State(CTransform::STATE_POSITION);
			_float3 MonsterPos = elem->Get_Component<CTransform>()->Get_World_State(CTransform::STATE_POSITION);

			_float3 Distance = MonsterPos - CameraPos;

			D3DXVec3Normalize(&Distance, &Distance);

			m_pTransformCom->Set_State(CTransform::STATE_POSITION, MonsterPos, true);

		}

	}
}

void CGPS::Friendly_GPS()
{
	auto Friendly = GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("AI_Friendly"));

	for (auto& elem : *Friendly)
	{
		if (!GAMEINSTANCE->IsIn(&elem->Get_Component<CTransform>()->Get_World_State(CTransform::STATE_POSITION)))
		{
			_float3 CameraPos = m_pCurrentCamera->Get_World_State(CTransform::STATE_POSITION);
			_float3 FriendlyPos = elem->Get_Component<CTransform>()->Get_World_State(CTransform::STATE_POSITION);

			_float3 Distance = FriendlyPos - CameraPos;

			D3DXVec3Normalize(&Distance, &Distance);

			m_pTransformCom->Set_State(CTransform::STATE_POSITION, FriendlyPos, true);
		}

	}
}


void CGPS::Free()
{
	__super::Free();

}

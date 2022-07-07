#include "stdafx.h"
#include "Planet_Sun.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "Level_Loading.h"
#include "Dive.h"


CPlanet_Sun::CPlanet_Sun()
{
}

CPlanet_Sun::CPlanet_Sun(const CPlanet_Sun& Prototype)
{
	*this = Prototype;
}

HRESULT CPlanet_Sun::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;
	_float3 StartPos = { 200.f, 100.f, 400.f };
	_tchar* PontText = TEXT("Sun \n 보스 구역 \n [Warring]   \n 보상 : XXX");
	_point PontPos = { (LONG)m_vScreenPos.x + 40, (LONG)m_vScreenPos.y - 10 };
	_float3 MyScale = _float3(100.f, 100.f, 50.f);
	_uint TextureIndex = 4;

	// 레벨 추가 안되있음
	SetUp_Varialbes_For_Child(StartPos, PontText, PontPos, TextureIndex, LEVEL::LEVEL_END, MyScale);


	m_pDiveUi = GAMEINSTANCE->Add_GameObject<CDive>(LEVEL_SELECTPLANET, TEXT("Dive"));
	m_pDiveUi->Set_Enable(false);


	return S_OK;
}
//}
//
//
//void CPlanet_Sun::SetUp_Components_For_Child()
//	_float3 MouseEndPos;
//	RAY	MouseWorldPos;
//	MouseWorldPos = CMath_Utillity::Get_MouseRayInWorldSpace();
//	MouseEndPos = MouseWorldPos.Pos + (MouseWorldPos.Dir * 10000.f);
//
//	_float3 ScreenPos = _float3(0.f, 0.f, 0.f);
//
//	CMath_Utillity::WorldToScreen(&m_pTransformCom->Get_State(CTransform::STATE_POSITION, true), &ScreenPos);
//
//
//
//	if (true == CMath_Utillity::Picking_VIBuffer(m_pVIBufferCom, m_pTransformCom, MouseWorldPos, &MouseEndPos))
//	{
//		GAMEINSTANCE->Add_Text(_point{ (LONG)ScreenPos.x + 40, (LONG)ScreenPos.y - 10 }, TEXT("Sun \n 보스 구역 \n [Warring]   \n 보상 : XXX"), 0);
//		m_pDiveUi->Set_Enable(true);
//	}
//
//
//
//	if (KEY_INPUT(KEY::F, KEY_STATE::HOLD) && !m_bLevelChange)
//	{
//
//		/*if (true == CMath_Utillity::Picking_VIBuffer(m_pVIBufferCom, m_pTransformCom, MouseWorldPos, &MouseEndPos))
//		{
//			if (FAILED(GAMEINSTANCE->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(LEVEL_GAMEPLAY))))
//				return;
//		}*/
//
//
//	}
//
//	CCamera* pCurrentCam = GAMEINSTANCE->Get_Camera();
//
//	ISVALID(pCurrentCam, );
//
//	_float3 CamWorldPos = pCurrentCam->Get_Transform()->Get_World_State(CTransform::STATE_POSITION);
//	_float3 MyWorldPos;
//	MyWorldPos.x = 200.f + CamWorldPos.x;
//	MyWorldPos.y = 100.f + CamWorldPos.y;
//	MyWorldPos.z = 400.f + CamWorldPos.z;
//
//
//	m_pTransformCom->Set_State(CTransform::STATE_POSITION, MyWorldPos, true);
//
//	Enter_Planet();
//}
//
//void CPlanet_Sun::LateTick(_float fTimeDelta)
//{
//	__super::LateTick(fTimeDelta);
//
//
//	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
//
//
//}
//
//HRESULT CPlanet_Sun::Render()
//{
//
//	m_pTransformCom->Bind_WorldMatrix();
//
//
//	
//	m_pRendererCom->Bind_Texture(4);
//
//	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
//	DEVICE->SetRenderState(D3DRS_ALPHAREF, 253);
//	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
//
//	m_pVIBufferCom->Render();
//
//	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
//
//	m_pRendererCom->UnBind_Texture();
//
//
//
//	return S_OK;
//}
//
//
//HRESULT CPlanet_Sun::SetUp_Components()
//{
//
//	Add_Component<CTransform>();
//
//	m_pTransformCom = Get_Component<CTransform>();
//	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);
//
//	m_pRendererCom = Add_Component<CRenderer>();
//	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);
//	m_pRendererCom->Set_Textures_From_Key(TEXT("Planet"), MEMORY_TYPE::MEMORY_STATIC);
//
//
//	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
//	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);
//
//	return S_OK;
//}
//
//void CPlanet_Sun::LookAtCamera()
//{
//	_float4x4		ViewMatrix;
//
//	DEVICE->GetTransform(D3DTS_VIEW, &ViewMatrix);
//	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);
//
//	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, *(_float3*)&ViewMatrix.m[0][0], true);
//	m_pTransformCom->Set_State(CTransform::STATE_UP, *(_float3*)&ViewMatrix.m[1][0], true);
//	m_pTransformCom->Set_State(CTransform::STATE_LOOK, *(_float3*)&ViewMatrix.m[2][0], true);
//
//}
//
//void CPlanet_Sun::Enter_Planet()
//{
//
//	CCamera* pCurrentCam = GAMEINSTANCE->Get_Camera();
//
//	ISVALID(pCurrentCam, );
//
//	_float3 CamWorldPos = pCurrentCam->Get_Transform()->Get_World_State(CTransform::STATE_POSITION);
//	_float3 MyWorldPos;
//	MyWorldPos.x = 200.f + CamWorldPos.x;
//	MyWorldPos.y = 100.f + CamWorldPos.y;
//	MyWorldPos.z = 400.f + CamWorldPos.z;
//
//
//	m_pTransformCom->Set_State(CTransform::STATE_POSITION, MyWorldPos, true);
//
//
//	LookAtCamera();
//
//	m_pTransformCom->Scaling(_float3(100.f, 100.f, 50.f), true);
//
//	_float3 MouseEndPos;
//	RAY	MouseWorldRay;
//	MouseWorldRay = CMath_Utillity::Get_MouseRayInWorldSpace();
//	MouseEndPos = MouseWorldRay.Pos + (MouseWorldRay.Dir * 10000.f);
//
//	_float3 ScreenPos = _float3(0.f, 0.f, 0.f);
//
//	CMath_Utillity::WorldToScreen(&m_pTransformCom->Get_State(CTransform::STATE_POSITION, true), &ScreenPos);
//
//	if (true == CMath_Utillity::Picking_VIBuffer(m_pVIBufferCom, m_pTransformCom, MouseWorldRay, &MouseEndPos))
//	{
//		m_pDiveUi->Set_Enable(true);
//		GAMEINSTANCE->Add_Text(_point{ (LONG)ScreenPos.x + 40, (LONG)ScreenPos.y - 10 }, TEXT("Sun \n 보스 구역 \n [Warring]   \n 보상 : XXX"), 0);
//
//		if (KEY_INPUT(KEY::F, KEY_STATE::HOLD) && !m_bLevelChange)
//		{
//			/*GAMEINSTANCE->Get_CurrentLevel()->Change_Level(this, LEVEL::LEVEL_REDPLANET);*/
//			m_bLevelChange = true;
//			return;
//		}
//	}
//
//	else
//	{
//		m_pDiveUi->Set_Enable(false);
//	}
//}

void CPlanet_Sun::SetUp_Components_For_Child()
{
}

CPlanet_Sun* CPlanet_Sun::Create()
{
	CREATE_PIPELINE(CPlanet_Sun);
}

CGameObject* CPlanet_Sun::Clone(void* pArg)
{
	CLONE_PIPELINE(CPlanet_Sun);
}

void CPlanet_Sun::Free()
{
	__super::Free();

	delete this;
}

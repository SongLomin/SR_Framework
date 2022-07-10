#include "stdafx.h"
#include "Planet_Venus.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "Level_Loading.h"
#include "Dive.h"


CPlanet_Venus::CPlanet_Venus()
{
}

CPlanet_Venus::CPlanet_Venus(const CPlanet_Venus& Prototype)
{
	*this = Prototype;
}

HRESULT CPlanet_Venus::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_float3 StartPos = { 1.f, 100.f, 300.f };
	_tchar* PontText = TEXT("Venus Planet \n 저 위험 구역 \n \n 임무 : 장애물 돌파 \n 난이도 :『★★★』  \n 보상 : XXX");
	_point PontPos = { (LONG)m_vScreenPos.x + 40, (LONG)m_vScreenPos.y - 10 };
	_float3 MyScale = _float3(80.f, 80.f, 50.f);
	_uint TextureIndex = 0;

	SetUp_Varialbes_For_Child(StartPos, PontText, PontPos, TextureIndex, LEVEL::LEVEL_VENUSPLANET, MyScale);
	m_pDiveUi = GAMEINSTANCE->Add_GameObject<CDive>(LEVEL_SELECTPLANET, TEXT("Dive"));
	m_pDiveUi->Set_Enable(false);


	return S_OK;
}

void CPlanet_Venus::SetUp_Components_For_Child()
{
}

//void CPlanet_Venus::Tick(_float fTimeDelta)
//{
//	__super::Tick(fTimeDelta);
//
//
//	Enter_Planet();
//}
//
//void CPlanet_Venus::LateTick(_float fTimeDelta)
//{
//	__super::LateTick(fTimeDelta);
//
//
//	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
//
//
//
//}
//
//HRESULT CPlanet_Venus::Render()
//{
//	
//
//	m_pTransformCom->Bind_WorldMatrix();
//
//	m_pRendererCom->Bind_Texture(0);
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
//HRESULT CPlanet_Venus::SetUp_Components()
//{
//}
//
//void CPlanet_Venus::Enter_Planet()
//{
//
//	CCamera* pCurrentCam = GAMEINSTANCE->Get_Camera();
//
//	ISVALID(pCurrentCam, );
//
//	_float3 CamWorldPos = pCurrentCam->Get_Transform()->Get_World_State(CTransform::STATE_POSITION);
//	_float3 MyWorldPos;
//	MyWorldPos.x = 1.f + CamWorldPos.x;
//	MyWorldPos.y = 100.f + CamWorldPos.y;
//	MyWorldPos.z = 300.f + CamWorldPos.z;
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
//		GAMEINSTANCE->Add_Text(_point{ (LONG)ScreenPos.x + 20, (LONG)ScreenPos.y }, TEXT("Venus Planet \n 저 위험 구역 \n 임무 : 기체 조작연습  \n 난이도 :『★』 \n 보상 : XXX"), 0);
//
//		if (KEY_INPUT(KEY::F, KEY_STATE::HOLD) && !m_bLevelChange)
//		{
//			GAMEINSTANCE->Get_CurrentLevel()->Change_Level(this, LEVEL::LEVEL_VENUSPLANET);
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

CPlanet_Venus* CPlanet_Venus::Create()
{
	CREATE_PIPELINE(CPlanet_Venus);
}

CGameObject* CPlanet_Venus::Clone(void* pArg)
{
	CLONE_PIPELINE(CPlanet_Venus);
}

void CPlanet_Venus::Free()
{
	__super::Free();

	delete this;
}

#include "stdafx.h"
#include "../Public/Auto_Aim.h"
#include "GameInstance.h"
#include "Math_Utillity.h"

CAuto_Aim::CAuto_Aim()
{
}

CAuto_Aim::CAuto_Aim(const CAuto_Aim& Prototype)
{
	*this = Prototype;

	Add_Component<CTransform>();
}



HRESULT CAuto_Aim::Initialize_Prototype()
{

	return S_OK;
}

HRESULT CAuto_Aim::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	return S_OK;
}

void CAuto_Aim::Tick(_float fTimeDelta)
{
	m_pTransformCom->Update_WorldMatrix();

	if (KEY_INPUT(KEY::M, KEY_STATE::TAP))
	{
		m_bUse = !m_bUse;

		//_float3 Mousept;
		//GetCursorPos(&m_pt);
		//ScreenToClient(g_hWnd, &m_pt);
		//Mousept.x = m_pt.x;
		//Mousept.y = m_pt.y;
		//Mousept.z = 0.f;

		//_float3 WorldMouse;
		//CMath_Utillity::ScreenToWorld(&Mousept, &WorldMouse);
		//D3DVIEWPORT9 view;
		//DEVICE->GetViewport(&view);
		//WorldMouse.x -= view.X * 0.5f;
		//WorldMouse.y -= view.Y * 0.5f;
		//// Auto_Aim 적용 코드 삽입
		////if (만약에 가까운적이 있으면)
		////{
		////	 에임을 고정시킨다.
		////}
		//
		////_float3 CameraPos = GAMEINSTANCE->Get_Camera(CURRENT_CAMERA)->Get_Transform()->Get_State(CTransform::STATE_POSITION);

		//_float4x4 CameraWorld = GAMEINSTANCE->Get_Camera(CURRENT_CAMERA)->Get_CameraWorldMat();

		//_float3 CameraPos = { CameraWorld._41, CameraWorld._42, CameraWorld._43 };

		//int i = 10;

		//_float3 vecPos;
		//
		//CMath_Utillity::WorldToScreen(&CameraPos, &vecPos);

		//SetCursorPos((int)vecPos.x + WorldMouse.x, (int)vecPos.y + WorldMouse.y);

		

		

		/*GAMEINSTANCE->Add_Text(
			_point{ (long)MyScreenPos.x, (long)MyScreenPos.y },
			L"병수형",
			0);*/

	}


	if (m_bUse)
	{
		list<CGameObject*>* Monster = GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("Monster"));

		ISVALID(Monster, );

		_float4x4 MyWorldMat = Monster->front()->Get_Component<CTransform>()->Get_WorldMatrix();
		_float3 MyPos{ MyWorldMat._41, MyWorldMat._42, MyWorldMat._43 };

		/*_float4x4 CamWorldMat = GAMEINSTANCE->Get_Camera()->Get_CameraWorldMat();

		_float3 CamPos{ CamWorldMat._41, CamWorldMat._42, CamWorldMat._43 };*/
		_float3 MyScreenPos;

		CMath_Utillity::WorldToScreen(&MyPos, &MyScreenPos);

		_point MousePos{ (int)MyScreenPos.x, (int)MyScreenPos.y };

		//Win32 좌표계
		ClientToScreen(g_hWnd, &MousePos);

		SetCursorPos(MousePos.x, MousePos.y);
	}
}

void CAuto_Aim::LateTick(_float fTimeDelta)
{
	if (m_pRendererCom == nullptr)
		return;

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_UI, this);
}

HRESULT CAuto_Aim::Render()
{
	return S_OK;
}

HRESULT CAuto_Aim::SetUp_Components()
{
	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);


	return S_OK;
}


CAuto_Aim* CAuto_Aim::Create()
{
	CREATE_PIPELINE(CAuto_Aim);
}

CGameObject* CAuto_Aim::Clone(void* pArg)
{
	CLONE_PIPELINE(CAuto_Aim);
}

void CAuto_Aim::Free()
{
	__super::Free();

	delete this;
}

#include "stdafx.h"
#include "Cam_TPS.h"
#include "GameInstance.h"

CCam_TPS::CCam_TPS(const CCam_TPS& Prototype)
{
	*this = Prototype;
}

HRESULT CCam_TPS::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCam_TPS::Initialize(void* pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.fSpeedPerSec = 5.0f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);

	m_pTransformCom = Add_Component<CTransform>(&TransformDesc);
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pCameraCom = Add_Component<CCamera>();
	m_pCameraCom->Set_WeakPtr(&m_pCameraCom);

	m_pCameraCom->Link_TransformCom(m_pTransformCom);

	m_pRigidBodyCom = Add_Component<CRigid_Body>();
	m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(0.0, 6.f, -6.f));
	m_pTransformCom->LookAt(_float3(0.f, 0.f, 0.f));

	m_CurCursorPosition = _float3(0.f, 0.f, 0.f);
	m_PreCursorPosition = POINT{ 0, 0 };
	m_MouseRealPosition = _float3(0.f, 0.f, 0.f);

	return S_OK;
}

void CCam_TPS::Tick(_float fTimeDelta)
{
	m_CurCursorPosition = Get_MousePos(GAMEINSTANCE->Get_Window_Handle());

	POINT ptMouse{ 0, 0 };

	if (GetFocus() == g_hWnd)
	{
		//ptMouse.x = GAMEINSTANCE->Get_Graphic_Desc().iWinCX * 0.5f; // 윈도우 기준으로 (400, 300)으로 설정
		//ptMouse.y = GAMEINSTANCE->Get_Graphic_Desc().iWinCY * 0.5f;

		//m_MouseRealPosition.x += m_CurCursorPosition.x - ptMouse.x;
		//m_MouseRealPosition.y += m_CurCursorPosition.y - ptMouse.y;

		//ClientToScreen(g_hWnd, &ptMouse); // 클라이언트 기준 좌표를 바탕화면 기준으로 변환한다

		//SetCursorPos(ptMouse.x, ptMouse.y); // 커서를 윈도우 기준으로 (400, 300)에 위치시킨다
		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);
	}

	POINT Cursor_Weight{};
	Cursor_Weight.x  = ptMouse.x - 640;
	Cursor_Weight.y = ptMouse.y - 360;


	m_pRigidBodyCom->Add_RotationX(-Cursor_Weight.y);
	m_pRigidBodyCom->Add_RotationY(Cursor_Weight.x);
	m_pTransformCom->LookAt(_float3(0.f, 0.f, 0.f));
	
	ptMouse.x = 640;
	ptMouse.y = 360;

	ScreenToClient(g_hWnd, &ptMouse);
	SetCursorPos(ptMouse.x, ptMouse.y);

	if (FAILED(m_pCameraCom->Bind_PipeLine()))
		return;
}

void CCam_TPS::LateTick(_float fTimeDelta)
{
}

HRESULT CCam_TPS::Render()
{
	return S_OK;
}

CCam_TPS* CCam_TPS::Create()
{
	CREATE_PIPELINE(CCam_TPS);
}

CGameObject* CCam_TPS::Clone(void* pArg)
{
	CLONE_PIPELINE(CCam_TPS);
}

void CCam_TPS::Free()
{
	__super::Free();

	delete this;
}

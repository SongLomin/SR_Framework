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
	m_PreCursorPosition = _float3(0.f, 0.f, 0.f);
	m_MouseRealPosition = _float3(0.f, 0.f, 0.f);

	return S_OK;
}

void CCam_TPS::Tick(_float fTimeDelta)
{
	m_CurCursorPosition = Get_MousePos(GAMEINSTANCE->Get_Window_Handle());

	POINT ptMouse{ 0, 0 };

	if (GetFocus() == g_hWnd)
	{
		ptMouse.x = GAMEINSTANCE->Get_Graphic_Desc().iWinCX * 0.5f; // ������ �������� (400, 300)���� ����
		ptMouse.y = GAMEINSTANCE->Get_Graphic_Desc().iWinCY * 0.5f;

		m_MouseRealPosition.x += m_CurCursorPosition.x - ptMouse.x;
		m_MouseRealPosition.y += m_CurCursorPosition.y - ptMouse.y;

		ClientToScreen(g_hWnd, &ptMouse); // Ŭ���̾�Ʈ ���� ��ǥ�� ����ȭ�� �������� ��ȯ�Ѵ�

		SetCursorPos(ptMouse.x, ptMouse.y); // Ŀ���� ������ �������� (400, 300)�� ��ġ��Ų��
		
	}

	_float3 Cursor_Weight = m_MouseRealPosition - m_PreCursorPosition;

	m_pTransformCom->Rotation(_float3(1.f,0.f,0.f),Cursor_Weight.x* 0.001f);
	m_pTransformCom->Rotation(_float3(0.f, 1.f, 0.f),Cursor_Weight.y* 0.001f);
	m_pTransformCom->LookAt(_float3(0.f, 0.f, 0.f));
	
	m_PreCursorPosition = m_MouseRealPosition;

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

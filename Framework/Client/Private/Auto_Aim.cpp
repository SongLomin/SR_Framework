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
	if (GAMEINSTANCE->Get_DIMouseMoveState(MOUSEMOVE::MMS_X))
	{
		_float3 Mousept;
		GetCursorPos(&m_pt);
		ScreenToClient(g_hWnd, &m_pt);
		Mousept.x = m_pt.x;
		Mousept.y = m_pt.y;
		Mousept.z = 1.f;

		_float3 WorldMouse;
		CMath_Utillity::ScreenToWorld(&Mousept, &WorldMouse);
		// Auto_Aim 적용 코드 삽입
		//if (만약에 가까운적이 있으면)
		//{
		//	 에임을 고정시킨다.
		//}
		WorldMouse;
		int i = 0;
		CMath_Utillity::WorldToScreen(&WorldMouse, &WorldMouse);

		SetCursorPos((int)WorldMouse.x, (int)WorldMouse.y);

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

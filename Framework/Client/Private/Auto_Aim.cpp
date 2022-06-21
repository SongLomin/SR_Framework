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
	}


	if (m_bUse)
	{
		list<CGameObject*>* Monster = GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("Monster"));

		ISVALID(Monster, );

		//몬스터랑 거리 비교가 끝나고, 몬스터 좌표에 마우스를 붙이는 코드
		//거리 비교가 성공했다는 가정
		_float4x4 MyWorldMat = Monster->front()->Get_Component<CTransform>()->Get_WorldMatrix();
		_float3 MyPos{ MyWorldMat._41, MyWorldMat._42, MyWorldMat._43 };

		_float3 MyScreenPos;

		CMath_Utillity::WorldToScreen(&MyPos, &MyScreenPos);

		_point MousePos{ (int)MyScreenPos.x, (int)MyScreenPos.y };

		//Win32 좌표계 변환
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

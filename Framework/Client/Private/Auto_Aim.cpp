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
	__super::Tick(fTimeDelta);

	if (KEY_INPUT(KEY::M, KEY_STATE::TAP))
	{
		m_bUse = !m_bUse;
	}

	if (m_bUse)
	{
		m_pTargettingCom->Update_Targetting();
		CTransform* CameraTransform = GAMEINSTANCE->Get_Camera(CURRENT_CAMERA)->Get_Transform();

		m_pTargetList = GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("Monster"));


		for (auto iter = m_pTargetList->begin();
			iter != m_pTargetList->end();
			++iter)
		{
			_float3 MonsterPos = (*iter)->Get_Component<CTransform>()->Get_World_State(CTransform::STATE_POSITION);


			_float3 CameraPos = CameraTransform->Get_World_State(CTransform::STATE_POSITION);


			RAY MouseRay = CMath_Utillity::Get_MouseRayInWorldSpace();
			D3DXVec3Normalize(&MouseRay.Dir, &MouseRay.Dir);

			_float3 MonsterRay = MonsterPos - MouseRay.Pos;

			_float Dotproduct = D3DXVec3Dot(&MouseRay.Dir, &MonsterRay);

			if (Dotproduct > 0.f)
			{
				_float3 Projection = Dotproduct * MouseRay.Dir;

				Projection += MouseRay.Pos;

				_float3 Lenght = MonsterPos - Projection;

				_float Range = D3DXVec3Length(&Lenght);



				if (Range < 5.f)
				{
					//list<CGameObject*>* Monster = GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("Monster"));
					//
					//ISVALID(Monster, );
					//
					//_float4x4 MyWorldMat = Monster->front()->Get_Component<CTransform>()->Get_WorldMatrix();
					//_float3 MyPos{ MyWorldMat._41, MyWorldMat._42, MyWorldMat._43 };
					//
					//_float3 MyScreenPos;
					//
					//CMath_Utillity::WorldToScreen(&MyPos, &MyScreenPos);
					//
					//_point MousePos{ (int)MyScreenPos.x, (int)MyScreenPos.y };
					//
					////Win32 좌표계
					////Win32에선 이걸 클라이언트 좌표라고 주장함... 바보들...
					//ClientToScreen(g_hWnd, &MousePos);
					//
					//SetCursorPos(MousePos.x, MousePos.y);

					
				}
			}
		}
	}

}

void CAuto_Aim::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	if (m_pRendererCom == nullptr)
		return;

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_UI, this);
}

HRESULT CAuto_Aim::Render()
{
	__super::Render();

	return S_OK;
}

HRESULT CAuto_Aim::SetUp_Components()
{
	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);

	m_pTargettingCom = Add_Component<CTargetting>();
	m_pTargettingCom->Set_WeakPtr(&m_pTargettingCom);


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

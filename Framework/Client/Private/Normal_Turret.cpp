#include "stdafx.h"
#include "Normal_Turret.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "Normal_Bullet.h"
#include "Roket_Bullet.h"



CNormal_Turret::CNormal_Turret(const CNormal_Turret& Prototype)
{
	*this = Prototype;
	Add_Component<CTransform>();


}

HRESULT CNormal_Turret::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CNormal_Turret::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;






	m_fCurTime = m_fMaxTime;

	return S_OK;
}

void CNormal_Turret::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	m_fCurTime -= fTimeDelta;

	if (Get_Controller() == CONTROLLER::PLAYER)
	{
		if (!LookAt_Targeting())
		{
			LookAt_Aim();
		}

		if (KEY_INPUT(KEY::LBUTTON, KEY_STATE::HOLD))
		{
			if (m_fCurTime < 0.f)
			{
				COLLISION_TYPE eColType = COLLISION_TYPE::MONSTER_ATTACK;
				CGameObject* Bullet = GAMEINSTANCE->Add_GameObject<CNormal_Bullet>(CURRENT_LEVEL, TEXT("Normal_Bullet"), nullptr, &eColType);
				static_cast<CNormal_Bullet*>(Bullet)->Init_BulletPosition(&m_pTransformCom->Get_WorldMatrix());
				//((CNormal_Bullet*)Bullet)->Link_PosinTransform(m_pTransformCom);

				GAMEINSTANCE->Add_Shaking(0.1f, 0.005f);

				m_fCurTime = 0.1f;
			}
		}

		if (KEY_INPUT(KEY::CTRL, KEY_STATE::HOLD))
		{
			if (m_fCurTime < 0.f)
			{
				COLLISION_TYPE eColType = COLLISION_TYPE::MONSTER_ATTACK;
				CGameObject* Bullet = GAMEINSTANCE->Add_GameObject<CRoket_Bullet>(CURRENT_LEVEL, TEXT("Roket_Bullet"), nullptr, &eColType);
				static_cast<CRoket_Bullet*>(Bullet)->Init_BulletPosition(&m_pTransformCom->Get_WorldMatrix());

				m_fCurTime = 0.3f;
			}
		}
	}

}

void CNormal_Turret::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	// 타겟 체크
	if (Get_Controller() == CONTROLLER::AI)
	{
		if (m_pTarget)
		{
			_float3 TargetPos = m_pTarget->Get_Component<CTransform>()->Get_World_State(CTransform::STATE_POSITION);
			m_pTransformCom->LookAt(TargetPos, true);

			if (m_pTarget && m_fCurTime <= 0)
			{
				COLLISION_TYPE eColType = COLLISION_TYPE::MONSTER_ATTACK;
				CGameObject* Bullet = GAMEINSTANCE->Add_GameObject<CNormal_Bullet>(CURRENT_LEVEL, TEXT("Normal_Bullet"), nullptr, &eColType);
				static_cast<CNormal_Bullet*>(Bullet)->Init_BulletPosition(&m_pTransformCom->Get_WorldMatrix());

				m_fMaxTime = (_float)(rand() % 11 + 5) * 0.1f;
				m_fCurTime = m_fMaxTime;
			}
		}
	}
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_DEFERRED, this);
}

HRESULT CNormal_Turret::Render_Begin(ID3DXEffect** Shader)
{
	m_pTransformCom->Scaling(_float3(0.01f, 0.01f, 0.01f), true);
	m_pTransformCom->Bind_WorldMatrix(D3D_ALL, D3D_ALL);

	D3DXHANDLE ColorHandle = (*Shader)->GetParameterByName(0, "Color");

	float floatArray[3];
	floatArray[0] = 0.2f;
	floatArray[1] = 0.2f;
	floatArray[2] = 0.2f;

	(*Shader)->SetFloatArray(ColorHandle, floatArray, 3);


	return S_OK;
}

HRESULT CNormal_Turret::Render()
{
	



	__super::Render();
	m_pMeshCom->Render_Mesh();



	return S_OK;
}

void CNormal_Turret::Set_Target(CGameObject* _Target)
{

	//if (m_pTargetObject != _Object)
	//{
	//	if (m_pTargetObject)
	//	{
	//		m_pTargetObject->Return_WeakPtr(&m_pTargetObject);
	//	}


	//	m_pTargetObject = _Object;		
	//}

	//if (nullptr == m_pTargetObject)
	//{
	//	//m_pTransformCom->LookAt(_float3(0.f, 1.f, 0.f), true);
	//	return;
	//}
	//else
	//{
	//	m_pTargetObject->Set_WeakPtr(&m_pTargetObject);
	//}

	//기존에 타겟 인스턴스가 살아 있는데 바뀐 경우는
	if (m_pTarget)
	{
		if(m_pBoxObject)
			m_pBoxObject->Set_Enable(false);
	}

	if (!_Target)
	{
		m_pTarget = nullptr;
		m_pBoxObject = nullptr;

		return;
	}


	m_pTarget = _Target;
	WEAK_PTR(m_pTarget);


	list<CGameObject*> Targetings = m_pTarget->Get_Children_From_Key(TEXT("Targeting"));
	if (Targetings.empty())
		return;

	m_pBoxObject = Targetings.front();
	WEAK_PTR(m_pBoxObject);

}

_bool CNormal_Turret::LookAt_Targeting()
{
	if (!m_pTarget)
	{
		return false;
	}

	m_pTransformCom->LookAt(m_pTarget->Get_Component<CTransform>(), true);

	m_pBoxObject->Set_Enable(true);

	return true;
}

void CNormal_Turret::LookAt_Aim()
{
	_float3 MouseEndPos;
	RAY	MouseWorldPos;
	MouseWorldPos = CMath_Utillity::Get_MouseRayInWorldSpace();
	MouseEndPos = MouseWorldPos.Pos + (MouseWorldPos.Dir * 1000.f);

	m_pTransformCom->LookAt(MouseEndPos, true);
}





HRESULT CNormal_Turret::SetUp_Components()
{

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);


	m_pMeshCom = Add_Component<CMesh_Canon>();
	m_pMeshCom->Set_WeakPtr(&m_pMeshCom);
	m_pMeshCom->Set_Texture(TEXT("Mesh_Cube"), MEMORY_TYPE::MEMORY_STATIC);

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr((void**)&m_pTransformCom);


	return S_OK;
}

void CNormal_Turret::On_Change_Controller(const CONTROLLER& _eController)
{
	m_fMaxTime = m_fCurTime = 0.34f;

}

CNormal_Turret* CNormal_Turret::Create()
{
	CREATE_PIPELINE(CNormal_Turret);
}

CGameObject* CNormal_Turret::Clone(void* pArg)
{
	CLONE_PIPELINE(CNormal_Turret);
}

void CNormal_Turret::Free()
{
	__super::Free();

	delete this;
}
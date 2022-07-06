#include "stdafx.h"
#include "Normal_Turret.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "Normal_Bullet.h"
#include "Roket_Bullet.h"
#include "Fire_PSystem.h"


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


	if(pArg)
		m_eBulletCollisionType = *(COLLISION_TYPE*)pArg;



	m_fCurTime = m_fMaxTime;

	return S_OK;
}

void CNormal_Turret::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	m_fCurTime -= fTimeDelta;

	_bool m_bTarget = LookAt_Targeting();

	// 타겟을 성공적으로 쳐다봤다면 이대로 Tick을 종료한다.
	if (m_bTarget)
		return;


	// 타겟이 없는 경우 플레이어는 Aim을 바라본다.
	if (Get_Controller() == CONTROLLER::PLAYER)
	{
		LookAt_Aim();
	}

	// AI는 정면을 바라본다.
	else if (Get_Controller() == CONTROLLER::AI)
	{
		m_pTransformCom->LookAt(_float3(0.f, 0.f, 1.f));
	}

}

void CNormal_Turret::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	// 타겟 체크
	//if (Get_Controller() == CONTROLLER::AI)
	//{
	//	if (m_pTarget)
	//	{
	//		_float3 TargetPos = m_pTarget->Get_Component<CTransform>()->Get_World_State(CTransform::STATE_POSITION);
	//		m_pTransformCom->LookAt(TargetPos, true);
	//	}

	//	/*if (m_fCurTime <= 0)
	//	{
	//		CGameObject* Bullet = GAMEINSTANCE->Add_GameObject<CNormal_Bullet>(CURRENT_LEVEL, TEXT("Normal_Bullet"), nullptr, &m_eBulletCollisionType);
	//		static_cast<CNormal_Bullet*>(Bullet)->Init_BulletPosition(&m_pTransformCom->Get_WorldMatrix());

	//		m_fMaxTime = (_float)(rand() % 11 + 5) * 0.1f;
	//		m_fCurTime = m_fMaxTime;
	//	}*/
	//}
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_DEFERRED, this);
}

HRESULT CNormal_Turret::Render_Begin(ID3DXEffect** Shader)
{
	m_pTransformCom->Scaling(_float3(0.1f, 0.4f, 3.f), true);
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

	//기존에 타겟 인스턴스가 살아 있는데 바뀐 경우는
	if (m_pTarget)
	{
		m_pTarget->Return_WeakPtr(&m_pTarget);
		m_pTarget = nullptr;

	}

	if (m_pBoxObject)
	{
		m_pBoxObject->Set_Enable(false);
		m_pBoxObject->Return_WeakPtr(&m_pBoxObject);
		m_pBoxObject = nullptr;
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


	if(m_pBoxObject)
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

void CNormal_Turret::Command_Fire()
{
	if (m_fCurTime <= 0)
	{
		CGameObject* Bullet = GAMEINSTANCE->Add_GameObject<CNormal_Bullet>(CURRENT_LEVEL, TEXT("Normal_Bullet"), nullptr, &m_eBulletCollisionType);
		static_cast<CNormal_Bullet*>(Bullet)->Init_BulletPosition(&m_pTransformCom->Get_WorldMatrix());

		//m_fMaxTime = (_float)(rand() % 11 + 5) * 0.1f;
		m_fCurTime = m_fMaxTime;
	}


}





HRESULT CNormal_Turret::SetUp_Components()
{

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);


	m_pMeshCom = Add_Component<CMesh_Cube>();
	m_pMeshCom->Set_WeakPtr(&m_pMeshCom);
	m_pMeshCom->Set_Texture(TEXT("Mesh_Cube"), MEMORY_TYPE::MEMORY_STATIC);

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr((void**)&m_pTransformCom);


	return S_OK;
}

void CNormal_Turret::On_Change_Controller(const CONTROLLER& _eController)
{
	//m_fMaxTime = m_fCurTime = 0.34f;

}

void CNormal_Turret::On_EventMessage(void* _Arg)
{
	wstring* Message = reinterpret_cast<wstring*>(_Arg);

	//발사 명령
	if (lstrcmpW(Message->c_str(), TEXT("Fire")) == 0)
	{
		Command_Fire();
	}
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

	RETURN_WEAKPTR(m_pTarget);
	RETURN_WEAKPTR(m_pBoxObject);

	delete this;
}
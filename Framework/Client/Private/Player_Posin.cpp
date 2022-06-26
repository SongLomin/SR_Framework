#include "stdafx.h"
#include "Player_Posin.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "Player_Bullet.h"
#include <TargetingBox.h>


CPlayer_Posin::CPlayer_Posin()
{
}

CPlayer_Posin::CPlayer_Posin(const CPlayer_Posin& Prototype)
{
	*this = Prototype;
	//m_szName = L"Posin";
	Add_Component<CTransform>();
}

HRESULT CPlayer_Posin::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CPlayer_Posin::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);


	m_pMeshCom = Add_Component<CMesh_Cube>();
	m_pMeshCom->Set_WeakPtr(&m_pMeshCom);
	m_pMeshCom->Set_Texture(TEXT("Mesh_Cube"), MEMORY_TYPE::MEMORY_STATIC);

	


	return S_OK;
}

void CPlayer_Posin::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	if (!LookAt_Targeting())
	{
		LookAt_Aim();
	}

	// 1초에 한번 호출
	m_fTime += fTimeDelta;
	if (1.f > m_fTime)
	{
		//LookAt_Targeting();
		m_fTime = 0.f;
	}

	if (KEY_INPUT(KEY::LBUTTON, KEY_STATE::TAP))
	{
		CGameObject* Bullet = GAMEINSTANCE->Add_GameObject<CPlayer_Bullet>(CURRENT_LEVEL, TEXT("Bullet"));

		((CPlayer_Bullet*)Bullet)->Link_PosinTransform(m_pTransformCom);
	}
}

void CPlayer_Posin::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CPlayer_Posin::Render()
{
	m_pTransformCom->Scaling(_float3(0.4f, 0.24f, 1.6f), true);
	m_pTransformCom->Bind_WorldMatrix(D3D_ALL, D3D_ALL);

	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pRendererCom->Bind_Texture(1);

	__super::Render();

	if (Get_Controller() == CONTROLLER::PLAYER)
		m_pMeshCom->Render_Mesh();
	m_pRendererCom->UnBind_Texture();

	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}

void CPlayer_Posin::Set_Target(CGameObject* _Target)
{
	//기존에 타겟 인스턴스가 살아 있는데 바뀐 경우는
	if (m_pTarget)
	{
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
	m_pBoxObject = Targetings.front();
	WEAK_PTR(m_pBoxObject);
}



inline HRESULT CPlayer_Posin::SetUp_Components()
{
	//CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	/*CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.fSpeedPerSec = 100.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(250.0f);*/

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr((void**)&m_pTransformCom);

	return S_OK;
}

_bool CPlayer_Posin::LookAt_Targeting()
{
	//map<_float, CGameObject*>* Monster = m_pTransformCom->Get->Get_Component<CTargeting>()->Get_Targetting();

	/*if (Monster->empty())
	{
		return false;
	}*/

	if (!m_pTarget)
	{
		return false;
	}

	m_pTransformCom->LookAt(m_pTarget->Get_Component<CTransform>(), true);

	m_pBoxObject->Set_Enable(true);

	return true;
}

void CPlayer_Posin::LookAt_Aim()
{
	_float3 MouseEndPos;
	RAY	MouseWorldPos;
	MouseWorldPos = CMath_Utillity::Get_MouseRayInWorldSpace();
	MouseEndPos = MouseWorldPos.Pos + (MouseWorldPos.Dir * 1000.f);

	m_pTransformCom->LookAt(MouseEndPos, true);

}



CPlayer_Posin* CPlayer_Posin::Create()
{
	CREATE_PIPELINE(CPlayer_Posin);
}

CGameObject* CPlayer_Posin::Clone(void* pArg)
{
	CLONE_PIPELINE(CPlayer_Posin);
}

void CPlayer_Posin::Free()
{
	__super::Free();

	RETURN_WEAKPTR(m_pBoxObject);

	delete this;
}


#include "stdafx.h"
#include "Player_Posin.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include <Bullet.h>


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

	m_pTransformCom->Scaling(_float3(0.5f, 0.5f, 0.5f));


	return S_OK;
}

void CPlayer_Posin::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	LookAt_Targeting();

	// 1초에 한번 호출
	m_fTime += fTimeDelta;
	if (1.f > m_fTime)
	{
		//LookAt_Targeting();
		m_fTime = 0.f;
	}

	if (KEY_INPUT(KEY::LBUTTON, KEY_STATE::TAP))
	{
		CGameObject* Bullet = GAMEINSTANCE->Add_GameObject<CBullet>(CURRENT_LEVEL, TEXT("Bullet"));

		((CBullet*)Bullet)->Link_PosinTransform(m_pTransformCom);
	}
}

void CPlayer_Posin::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CPlayer_Posin::Render()
{
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

void CPlayer_Posin::LookAt_Targeting()
{
	list<CGameObject*>* Monster = GAMEINSTANCE->Get_Player_GameObject()->Get_Component<CTargeting>()->Get_Targetting();
	if (!Monster->empty())
	{
		for (auto& elem : *Monster)
		{
			if(elem)
				m_pTransformCom->LookAt(elem->Get_Component<CTransform>(), true);
		}
	}
	else
	{
		_float3 MouseEndPos;
		RAY	MouseWorldPos;
		MouseWorldPos = CMath_Utillity::Get_MouseRayInWorldSpace();
		MouseEndPos = MouseWorldPos.Pos + (MouseWorldPos.Dir * 1000.f);

		m_pTransformCom->LookAt(MouseEndPos, true);
	}
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

	delete this;
}


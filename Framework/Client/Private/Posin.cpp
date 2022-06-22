#include "stdafx.h"
#include "Posin.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include <Bullet.h>


CPosin::CPosin()
{
}

CPosin::CPosin(const CPosin& Prototype)
{
	*this = Prototype;
	//m_szName = L"Posin";
	Add_Component<CTransform>();
}

HRESULT CPosin::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CPosin::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);


	m_pMeshCom = Add_Component<CMesh_Cube>();
	m_pMeshCom->Set_WeakPtr(&m_pMeshCom);

	m_pTransformCom->Scaling(_float3(0.5f, 0.5f, 0.5f));


	return S_OK;
}

void CPosin::Tick(_float fTimeDelta)
{
	m_pTransformCom->Update_WorldMatrix();

	LookAt_Targetting();

	if (KEY_INPUT(KEY::LBUTTON, KEY_STATE::TAP))
	{
		CGameObject* Bullet = GAMEINSTANCE->Add_GameObject<CBullet>(CURRENT_LEVEL, TEXT("Bullet"));

		((CBullet*)Bullet)->Link_PosinTransform(m_pTransformCom);
	}

}


void CPosin::LateTick(_float fTimeDelta)
{
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CPosin::Render()
{
	m_pTransformCom->Bind_WorldMatrix(D3D_ALL, D3D_ALL);

	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pRendererCom->Bind_Texture(1);
	if (Get_Controller() == CONTROLLER::PLAYER)
		m_pMeshCom->Render();
	m_pRendererCom->UnBind_Texture();

	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}



inline HRESULT CPosin::SetUp_Components()
{
	//CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	/*CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.fSpeedPerSec = 100.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(250.0f);*/

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr((void**)&m_pTransformCom);

	return S_OK;
}

void CPosin::LookAt_Targetting()
{
	auto Monster = GAMEINSTANCE->Get_Player_GameObject()->Get_Component<CTargetting>()->Get_Targetting();
	if (!Monster.empty())
	{
		for (auto& iter : Monster)
		{
			m_pTransformCom->LookAt(iter->Get_Component<CTransform>(), true);
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



CPosin* CPosin::Create()
{
	CREATE_PIPELINE(CPosin);
}

CGameObject* CPosin::Clone(void* pArg)
{
	CLONE_PIPELINE(CPosin);
}

void CPosin::Free()
{
	__super::Free();

	delete this;
}


#include "stdafx.h"
#include "..\Public\Dummy.h"
#include "GameInstance.h"

CDummy* CDummy::Create()
{
	CREATE_PIPELINE(CDummy);
}

CGameObject* CDummy::Clone(void* pArg)
{
	CLONE_PIPELINE(CDummy);
}

CDummy::CDummy(const CDummy& Prototype)
{
	*this = Prototype;
	Add_Component<CTransform>();
}

HRESULT CDummy::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CDummy::Initialize(void* pArg)
{
	//m_szName = L"Dummy";
	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);

	m_pRendererCom->Set_Textures_From_Key(TEXT("Test"), MEMORY_TYPE::MEMORY_DYNAMIC);

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);


	m_pMeshCom = Add_Component<CMesh_Cube>();
	m_pMeshCom->Set_WeakPtr(&m_pMeshCom);

	m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(2.f, 0.f, 0.f));



	return S_OK;
}

void CDummy::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	m_pTransformCom->Update_WorldMatrix();
}

void CDummy::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CDummy::Render()
{
	

	m_pTransformCom->Bind_WorldMatrix();

	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pRendererCom->Bind_Texture(1);

	__super::Render();
	if (Get_Controller() == CONTROLLER::PLAYER)
		m_pMeshCom->Render_Mesh();


	m_pRendererCom->UnBind_Texture();

	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}

void CDummy::Free()
{
	__super::Free();

	delete this;
}
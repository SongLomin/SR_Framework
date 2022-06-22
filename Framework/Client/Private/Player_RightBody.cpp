#include "stdafx.h"
#include "Player_RightBody.h"
#include "GameInstance.h"

CPlayer_RightBody* CPlayer_RightBody::Create()
{
	CREATE_PIPELINE(CPlayer_RightBody);
}

CGameObject* CPlayer_RightBody::Clone(void* pArg)
{
	CLONE_PIPELINE(CPlayer_RightBody);
}

CPlayer_RightBody::CPlayer_RightBody(const CPlayer_RightBody& Prototype)
{
	*this = Prototype;
	Add_Component<CTransform>();
}

HRESULT CPlayer_RightBody::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CPlayer_RightBody::Initialize(void* pArg)
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

void CPlayer_RightBody::Tick(_float fTimeDelta)
{
	m_pTransformCom->Update_WorldMatrix();
}

void CPlayer_RightBody::LateTick(_float fTimeDelta)
{
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CPlayer_RightBody::Render()
{
	m_pTransformCom->Bind_WorldMatrix();

	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pRendererCom->Bind_Texture(1);
	if (Get_Controller() == CONTROLLER::PLAYER)
		m_pMeshCom->Render();
	m_pRendererCom->UnBind_Texture();

	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}

void CPlayer_RightBody::Free()
{
	__super::Free();

	delete this;
}
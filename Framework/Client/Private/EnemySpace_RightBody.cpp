#include "stdafx.h"
#include "EnemySpace_RightBody.h"
#include "GameInstance.h"

CEnemySpace_RightBody* CEnemySpace_RightBody::Create()
{
	CREATE_PIPELINE(CEnemySpace_RightBody);
}

CGameObject* CEnemySpace_RightBody::Clone(void* pArg)
{
	CLONE_PIPELINE(CEnemySpace_RightBody);
}

CEnemySpace_RightBody::CEnemySpace_RightBody(const CEnemySpace_RightBody& Prototype)
{
	*this = Prototype;
	Add_Component<CTransform>();
}

HRESULT CEnemySpace_RightBody::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CEnemySpace_RightBody::Initialize(void* pArg)
{

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

void CEnemySpace_RightBody::Tick(_float fTimeDelta)
{
	m_pTransformCom->Update_WorldMatrix();
}

void CEnemySpace_RightBody::LateTick(_float fTimeDelta)
{
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CEnemySpace_RightBody::Render()
{
	m_pTransformCom->Bind_WorldMatrix();


	m_pRendererCom->Bind_Texture(1);
	m_pMeshCom->Render();
	m_pRendererCom->UnBind_Texture();


	return S_OK;
}

void CEnemySpace_RightBody::Free()
{
	__super::Free();

	delete this;
}


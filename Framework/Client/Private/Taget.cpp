#include "stdafx.h"
#include "Taget.h"
#include "GameInstance.h"
#include "Level_VenusPlanet.h"

CTaget::CTaget(const CTaget& Prototype)
{
	*this = Prototype;
}

HRESULT CTaget::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CTaget::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	__super::Initialize(pArg);

	return S_OK;
}

void CTaget::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CTaget::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
	LookAt_Camera();
}

HRESULT CTaget::Render_Begin(ID3DXEffect** Shader)
{
	m_pTransformCom->Scaling(_float3(7.f, 5.f, 5.f), true);
	m_pTransformCom->Bind_WorldMatrix();

	return S_OK;
}

HRESULT CTaget::Render()
{
	__super::Render();
	m_pRendererCom->Bind_Texture(0);

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 100);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pVIBufferCom->Render();

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pRendererCom->UnBind_Texture();

	return S_OK;
}

void CTaget::LookAt_Camera()
{
	_float4x4		ViewMatrix;

	DEVICE->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, *(_float3*)&ViewMatrix.m[0][0], true);
	m_pTransformCom->Set_State(CTransform::STATE_UP, *(_float3*)&ViewMatrix.m[1][0], true);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, *(_float3*)&ViewMatrix.m[2][0], true);
}

void CTaget::SetUp_Components_For_Child()
{
	CStatus::STATUS Status;
	Status.fAttack = 1.f;
	Status.fArmor = 5.f;
	Status.fMaxHp = 20.f;
	Status.fHp = Status.fMaxHp;

	m_pStatusCom = Add_Component<CStatus>(&Status);
	m_pStatusCom->Set_WeakPtr(&m_pStatusCom);

	

	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.Set_Preset_EnemySpace_Body();

	m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);

	m_pRendererCom->Set_Textures_From_Key(TEXT("Taget"), MEMORY_TYPE::MEMORY_STATIC);

	m_pStateCom->Link_RigidBody(m_pRigidBodyCom);
	m_pStateCom->Link_AI_Transform(m_pTransformCom);


	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);


	m_pAIControllerCom->Link_Object(this);
	m_pAIControllerCom->Set_Enable(false);
	m_pAIControllerCom->Set_UsableStates(m_pAIControllerCom->Get_States_Preset_AI_Default());



	m_pColliderCom->Link_Transform(m_pTransformCom);
	m_pColliderCom->Set_Collider_Size(_float3(4.f, 4.f, 4.f));
	m_pColliderCom->Set_WeakPtr(&m_pColliderCom);

	Set_Controller(CONTROLLER::AI);
}

void CTaget::On_Change_Controller(const CONTROLLER& _IsAI)
{
	__super::On_Change_Controller(_IsAI);
}

void CTaget::On_Collision_Enter(CCollider* _Other_Collider)
{
	__super::On_Collision_Enter(_Other_Collider);
}

void CTaget::On_Collision_Stay(CCollider* _Other_Collider)
{
	__super::On_Collision_Stay(_Other_Collider);
}

void CTaget::On_Collision_Exit(CCollider* _Other_Collider)
{
	__super::On_Collision_Exit(_Other_Collider);
}

CTaget* CTaget::Create()
{
	CREATE_PIPELINE(CTaget);
}

CGameObject* CTaget::Clone(void* pArg)
{
	CLONE_PIPELINE(CTaget);
}

void CTaget::Free()
{
	__super::Free();

	delete this;
}

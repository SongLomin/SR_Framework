#include "stdafx.h"
#include "Enemy_TagetBoard.h"
#include "GameInstance.h"
#include "Level_VenusPlanet.h"

CEnemy_TagetBoard::CEnemy_TagetBoard(const CEnemy_TagetBoard& Prototype)
{
	*this = Prototype;
}

HRESULT CEnemy_TagetBoard::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CEnemy_TagetBoard::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	__super::Initialize(pArg);

	return S_OK;
}

void CEnemy_TagetBoard::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CEnemy_TagetBoard::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
	LookAt_Camera();
}

HRESULT CEnemy_TagetBoard::Render_Begin(ID3DXEffect** Shader)
{
	m_pTransformCom->Scaling(_float3(7.f, 5.f, 5.f), true);
	m_pTransformCom->Bind_WorldMatrix();

	return S_OK;
}

HRESULT CEnemy_TagetBoard::Render()
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



void CEnemy_TagetBoard::SetUp_Components_For_Child()
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

void CEnemy_TagetBoard::On_Change_Controller(const CONTROLLER& _IsAI)
{
	__super::On_Change_Controller(_IsAI);
}

void CEnemy_TagetBoard::On_Collision_Enter(CCollider* _Other_Collider)
{
	__super::On_Collision_Enter(_Other_Collider);
}

void CEnemy_TagetBoard::On_Collision_Stay(CCollider* _Other_Collider)
{
	__super::On_Collision_Stay(_Other_Collider);
}

void CEnemy_TagetBoard::On_Collision_Exit(CCollider* _Other_Collider)
{
	__super::On_Collision_Exit(_Other_Collider);
}

CEnemy_TagetBoard* CEnemy_TagetBoard::Create()
{
	CREATE_PIPELINE(CEnemy_TagetBoard);
}

CGameObject* CEnemy_TagetBoard::Clone(void* pArg)
{
	CLONE_PIPELINE(CEnemy_TagetBoard);
}

void CEnemy_TagetBoard::Free()
{
	__super::Free();

	delete this;
}

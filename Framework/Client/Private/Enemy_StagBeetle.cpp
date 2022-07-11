#include "stdafx.h"
#include "Enemy_StagBeetle.h"
#include "GameInstance.h"
#include "Normal_Turret.h"
#include "Rocket_Turret.h"
#include "Move_PSystem.h"

CEnemy_StagBeetle::CEnemy_StagBeetle(const CEnemy_StagBeetle& Prototype)
{
	*this = Prototype;
}

HRESULT CEnemy_StagBeetle::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CEnemy_StagBeetle::Initialize(void* pArg)
{
	
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	__super::Initialize(pArg);

	return S_OK;
}

void CEnemy_StagBeetle::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CEnemy_StagBeetle::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);


	_float3 Speed = m_pRigidBodyCom->Get_Vector(RIGID_BODY::SPEED);

	if (fabs(D3DXVec3Length(&Speed)) > 5.f)
	{
		D3DCOLOR color = D3DCOLOR_ARGB(255, 0, 255, 0);
		((CMove_PSystem*)GAMEINSTANCE->Get_ParticleSystem<CMove_PSystem>(CURRENT_LEVEL, TEXT("Particle_Smoke")))->AddParticle(500 * fTimeDelta, m_pTransformCom, color);
	}


	m_pRigidBodyCom->Update_Transform(fTimeDelta);
	_float3 vPos = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);

	if (GAMEINSTANCE->IsIn(&vPos))
		m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_DEFERRED, this);
}

HRESULT CEnemy_StagBeetle::Render_Begin(ID3DXEffect** Shader)
{
	m_pTransformCom->Scaling(_float3(1.f, 1.f, 1.f), true);
	m_pTransformCom->Bind_WorldMatrix();

	D3DXHANDLE ColorHandle = (*Shader)->GetParameterByName(0, "Color");

	float floatArray[3];
	floatArray[0] = 0.7f;
	floatArray[1] = 0.0f;
	floatArray[2] = 0.0f;

	(*Shader)->SetFloatArray(ColorHandle, floatArray, 3);


	return S_OK;
}

HRESULT CEnemy_StagBeetle::Render()
{
	__super::Render();

	m_pMeshCom->Render_Mesh();

	return S_OK;
}

void CEnemy_StagBeetle::Update_Target(CGameObject* _Target)
{
}

void CEnemy_StagBeetle::SetUp_Components_For_Child()
{
	CStatus::STATUS Status;
	Status.fAttack = 1.f;
	Status.fArmor = 5.f;
	Status.fMaxHp = 20.f;
	Status.fHp = Status.fMaxHp;


	m_pStatusCom = Add_Component<CStatus>(&Status);
	m_pStatusCom->Set_WeakPtr(&m_pStatusCom);

	m_pMeshCom = Add_Component<CMesh_Ship2>();
	m_pMeshCom->Set_WeakPtr((void**)&m_pMeshCom);
	m_pMeshCom->Set_Texture(TEXT("Red_Cube"), MEMORY_TYPE::MEMORY_STATIC);

	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.Set_Preset_StagBeetle();

	m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);


	COLLISION_TYPE eBulletCollisionType = COLLISION_TYPE::MONSTER_ATTACK;

	CNormal_Turret* Posin = static_cast<CNormal_Turret*>(GAMEINSTANCE->Add_GameObject<CNormal_Turret>(CURRENT_LEVEL, TEXT("Normal_Turret"), m_pTransformCom, &eBulletCollisionType));
	Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(2.f, 1.0f, 2.f));
	m_pPosinList.push_back(Posin);
	Posin->Set_WeakPtr(&m_pPosinList.back());

	Posin = static_cast<CNormal_Turret*>(GAMEINSTANCE->Add_GameObject<CNormal_Turret>(CURRENT_LEVEL, TEXT("Normal_Turret"), m_pTransformCom, &eBulletCollisionType));
	Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(-2.f, 1.0f, 2.f));
	m_pPosinList.push_back(Posin);
	Posin->Set_WeakPtr(&m_pPosinList.back());


	m_pStateCom->Link_RigidBody(m_pRigidBodyCom);
	m_pStateCom->Link_AI_Transform(m_pTransformCom);
	

	m_pAIControllerCom->Link_Object(this);
	m_pAIControllerCom->Set_Enable(false);
	m_pAIControllerCom->Set_UsableStates(m_pAIControllerCom->Get_States_Preset_AI_Default());


	m_pColliderCom->Link_Transform(m_pTransformCom);
	m_pColliderCom->Set_Collider_Size(_float3(3.f, 3.f, 3.f));
	m_pColliderCom->Set_WeakPtr(&m_pColliderCom);

	Set_Controller(CONTROLLER::AI);
}

void CEnemy_StagBeetle::On_Change_Controller(const CONTROLLER& _IsAI)
{
	__super::On_Change_Controller(_IsAI);
}

void CEnemy_StagBeetle::On_Collision_Enter(CCollider* _Other_Collider)
{
	__super::On_Collision_Enter(_Other_Collider);
}

void CEnemy_StagBeetle::On_Collision_Stay(CCollider* _Other_Collider)
{
	__super::On_Collision_Stay(_Other_Collider);
}

void CEnemy_StagBeetle::On_Collision_Exit(CCollider* _Other_Collider)
{
	__super::On_Collision_Exit(_Other_Collider);
}

CEnemy_StagBeetle* CEnemy_StagBeetle::Create()
{
	CREATE_PIPELINE(CEnemy_StagBeetle);
}

CGameObject* CEnemy_StagBeetle::Clone(void* pArg)
{
	CLONE_PIPELINE(CEnemy_StagBeetle);
}

void CEnemy_StagBeetle::Free()
{
	__super::Free();

	delete this;
}

#include "stdafx.h"
#include "Enemy_Scourge.h"
#include "GameInstance.h"
#include "Move_PSystem.h"
#include "Normal_Turret.h"
#include "Bomb_Effect.h"
#include "Fire_PSystem.h"

CEnemy_Scourge::CEnemy_Scourge(const CEnemy_Scourge& Prototype)
{
	*this = Prototype;
}

HRESULT CEnemy_Scourge::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CEnemy_Scourge::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	__super::Initialize(pArg);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(rand() % 1000, rand() % 150, rand() % 1000));

	return S_OK;
}

void CEnemy_Scourge::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CEnemy_Scourge::LateTick(_float fTimeDelta)
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

	m_pTransformCom->Scaling(_float3(0.5f, 0.5f, 0.5f), true);

	if (GAMEINSTANCE->IsIn(&vPos))
		m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_DEFERRED, this);
}

HRESULT CEnemy_Scourge::Render_Begin(ID3DXEffect** Shader)
{
	m_pTransformCom->Bind_WorldMatrix();

	D3DXHANDLE ColorHandle = (*Shader)->GetParameterByName(0, "Color");

	float floatArray[3];
	floatArray[0] = 0.7f;
	floatArray[1] = 0.0f;
	floatArray[2] = 0.0f;

	(*Shader)->SetFloatArray(ColorHandle, floatArray, 3);


	return S_OK;
}

HRESULT CEnemy_Scourge::Render()
{
	__super::Render();

	m_pMeshCom->Render_Mesh();

	return S_OK;
}

void CEnemy_Scourge::SetUp_Components_For_Child()
{
	CStatus::STATUS Status;
	Status.fAttack = 1.f;
	Status.fArmor = 5.f;
	Status.fMaxHp = 20.f;
	Status.fHp = Status.fMaxHp;


	m_pStatusCom = Add_Component<CStatus>(&Status);
	m_pStatusCom->Set_WeakPtr(&m_pStatusCom);

	m_pMeshCom = Add_Component<CMesh_Ship1>();
	m_pMeshCom->Set_WeakPtr((void**)&m_pMeshCom);
	m_pMeshCom->Set_Texture(TEXT("Red_Cube"), MEMORY_TYPE::MEMORY_STATIC);

	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.Set_Preset_Scourge();

	m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);



	COLLISION_TYPE	eCollisiontype = COLLISION_TYPE::OBJECT;
	m_pColliderCom = Add_Component<CCollider_Sphere>(&eCollisiontype);
	m_pColliderCom->Set_WeakPtr(&m_pColliderCom);
	m_pColliderCom->Link_Transform(m_pTransformCom);
	m_pColliderCom->Set_Collider_Size(_float3(3.f, 3.f, 3.f));
	m_pColliderCom->Set_WeakPtr(&m_pColliderCom);


	m_pStateCom->Link_RigidBody(m_pRigidBodyCom);
	m_pStateCom->Link_AI_Transform(m_pTransformCom);


	m_pAIControllerCom->Link_Object(this);
	m_pAIControllerCom->Set_Enable(false);
	m_pAIControllerCom->Set_UsableStates({ STATE::MOVETAGET_CHASE_PLAYER });

	
	Set_Controller(CONTROLLER::AI);
}

void CEnemy_Scourge::On_Change_Controller(const CONTROLLER& _IsAI)
{
	__super::On_Change_Controller(_IsAI);
}

void CEnemy_Scourge::On_Collision_Enter(CCollider* _Other_Collider)
{
	//__super::On_Collision_Enter(_Other_Collider);

	if (_Other_Collider->Get_Collision_Type() == COLLISION_TYPE::PLAYER)
	{
	
		CGameObject* pOtherCollider = _Other_Collider->Get_Owner();
		_float3		pRockPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION, true);
		_float3 vOtherColliderSpeed = pOtherCollider->Get_Component<CRigid_Body>()->Get_Vector(RIGID_BODY::SPEED);
		_float3 vCollisionDirection = pRockPos - pOtherCollider->Get_Component<CTransform>()->Get_State(CTransform::STATE_POSITION, true);

		D3DXVec3Normalize(&vCollisionDirection, &vCollisionDirection);
		vCollisionDirection *= D3DXVec3Length(&vOtherColliderSpeed);
		vOtherColliderSpeed += vCollisionDirection;

		m_pRigidBodyCom->Add_Force(vOtherColliderSpeed * 3.f);

		CGameObject* pParticle = GAMEINSTANCE->Add_GameObject<CBomb_Effect>(CURRENT_LEVEL, TEXT("Explosion"), nullptr, nullptr, false);
		((CBomb_Effect*)pParticle)->Set_Pos(pRockPos);
		((CBomb_Effect*)pParticle)->Get_Component<CTransform>()->Scaling(_float3(25.f, 25.f, 25.f));
		Set_Dead();
		//폭발 이펙트 스케일링 따로 지정해줘야함
	}


}

void CEnemy_Scourge::On_Collision_Stay(CCollider* _Other_Collider)
{
	__super::On_Collision_Stay(_Other_Collider);

}

void CEnemy_Scourge::On_Collision_Exit(CCollider* _Other_Collider)
{
	__super::On_Collision_Exit(_Other_Collider);
}

CEnemy_Scourge* CEnemy_Scourge::Create()
{
	CREATE_PIPELINE(CEnemy_Scourge);
}

CGameObject* CEnemy_Scourge::Clone(void* pArg)
{
	CLONE_PIPELINE(CEnemy_Scourge);
}

void CEnemy_Scourge::Free()
{
	__super::Free();

	delete this;
}

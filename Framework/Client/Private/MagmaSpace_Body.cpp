#include "stdafx.h"
#include "MagmaSpace_Body.h"
#include "GameInstance.h"
#include "Normal_Turret.h"
#include "State_Move.h"
#include <TargetingBox.h>
#include "Math_Utillity.h"
#include <Fire_PSystem.h>
#include <Bomb_Effect.h>
#include <Smoke_PSystem.h>
#include "Move_PSystem.h"

CMagmaSpace_Body::CMagmaSpace_Body(const CMagmaSpace_Body& Prototype)
{
	*this = Prototype;
}

HRESULT CMagmaSpace_Body::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CMagmaSpace_Body::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

#pragma region 초기 위치 설정


	/*m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(rand() % 100, rand() % 20, 300.f + 20.f));
	m_pTransformCom->Update_WorldMatrix();*/

#pragma endregion 초기 위치 설정

	__super::Initialize(pArg);

	return S_OK;
}

void CMagmaSpace_Body::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

}

void CMagmaSpace_Body::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);


	m_fTime -= fTimeDelta;



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

HRESULT CMagmaSpace_Body::Render_Begin(ID3DXEffect** Shader)
{
	m_pTransformCom->Scaling(_float3(0.05f, 0.05f, 0.05f), true);
	m_pTransformCom->Bind_WorldMatrix();

	D3DXHANDLE ColorHandle = (*Shader)->GetParameterByName(0, "Color");

	float floatArray[3];
	floatArray[0] = 0.7f;
	floatArray[1] = 0.0f;
	floatArray[2] = 0.7f;

	(*Shader)->SetFloatArray(ColorHandle, floatArray, 3);


	return S_OK;
}

HRESULT CMagmaSpace_Body::Render()
{
	
	__super::Render();

	m_pMeshCom->Render_Mesh();

	return S_OK;
}



void CMagmaSpace_Body::SetUp_Components_For_Child()
{
	CStatus::STATUS Status;
	Status.fAttack = 2.f;
	Status.fArmor = 10.f;
	Status.fMaxHp = 25.f;
	Status.fHp = Status.fMaxHp;

	m_pStatusCom = Add_Component<CStatus>(&Status);
	m_pStatusCom->Set_WeakPtr(&m_pStatusCom);

	m_pMeshCom = Add_Component<CMesh_Ship3>();
	m_pMeshCom->Set_WeakPtr((void**)&m_pMeshCom);

	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.Set_Preset_MagmaSpace_Body();

	m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);



	m_pStateCom->Link_RigidBody(m_pRigidBodyCom);
	m_pStateCom->Link_AI_Transform(m_pTransformCom);


	COLLISION_TYPE eBulletCollisionType = COLLISION_TYPE::MONSTER_ATTACK;

	CNormal_Turret* Posin = static_cast<CNormal_Turret*>(GAMEINSTANCE->Add_GameObject<CNormal_Turret>(CURRENT_LEVEL, TEXT("Normal_Turret"), m_pTransformCom, &eBulletCollisionType));
	Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(2.f, 1.5f, 0.f));
	m_pPosinList.push_back(Posin);
	Posin->Set_WeakPtr(&m_pPosinList.back());

	Posin = static_cast<CNormal_Turret*>(GAMEINSTANCE->Add_GameObject<CNormal_Turret>(CURRENT_LEVEL, TEXT("Normal_Turret"), m_pTransformCom, &eBulletCollisionType));
	Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(0.f, 1.5f, 0.f));
	m_pPosinList.push_back(Posin);
	Posin->Set_WeakPtr(&m_pPosinList.back());


	m_pAIControllerCom->Link_Object(this);
	m_pAIControllerCom->Set_Enable(false);
	m_pAIControllerCom->Set_UsableStates(m_pAIControllerCom->Get_States_Preset_AI_Default());


	COLLISION_TYPE eCollisionType = COLLISION_TYPE::MONSTER;
	m_pColliderCom = Add_Component<CCollider_Sphere>(&eCollisionType);
	m_pColliderCom->Link_Transform(m_pTransformCom);
	m_pColliderCom->Set_Collider_Size(_float3(4.f, 4.f, 4.f));
	m_pColliderCom->Set_WeakPtr(&m_pColliderCom);
	Set_Controller(CONTROLLER::AI);
}



void CMagmaSpace_Body::On_Change_Controller(const CONTROLLER& _IsAI)
{
	__super::On_Change_Controller(_IsAI);
}


CMagmaSpace_Body* CMagmaSpace_Body::Create()
{
	CREATE_PIPELINE(CMagmaSpace_Body);
}

CGameObject* CMagmaSpace_Body::Clone(void* pArg)
{
	CLONE_PIPELINE(CMagmaSpace_Body);
}

void CMagmaSpace_Body::Free()
{
	__super::Free();

	delete this;
}

void CMagmaSpace_Body::On_Collision_Enter(CCollider* _Other_Collider)
{
	__super::On_Collision_Enter(_Other_Collider);
}

void CMagmaSpace_Body::On_Collision_Stay(CCollider* _Other_Collider)
{
	__super::On_Collision_Stay(_Other_Collider);
}

void CMagmaSpace_Body::On_Collision_Exit(CCollider* _Other_Collider)
{
	__super::On_Collision_Exit(_Other_Collider);
}

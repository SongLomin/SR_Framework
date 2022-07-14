#include "stdafx.h"
#include "BillBoard_Object.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include <Rock_PSystem.h>
#include <Bomb_Effect.h>

CBillboard_Object::CBillboard_Object()
{
}

CBillboard_Object::CBillboard_Object(const CBillboard_Object& Prototype)
{
	*this = Prototype;
}

HRESULT CBillboard_Object::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CBillboard_Object::Initialize(void* pArg)
{
	return S_OK;
}

void CBillboard_Object::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


}

void CBillboard_Object::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRigidBodyCom->Update_Transform(fTimeDelta);

	LookAtCamera();

	if (GAMEINSTANCE->IsIn(&(m_pTransformCom->Get_World_State(CTransform::STATE_POSITION))))
	{
		m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
	}

}

HRESULT CBillboard_Object::Render()
{

	__super::Render();

	return S_OK;
}

HRESULT CBillboard_Object::SetUp_Components()
{

	Add_Component<CTransform>();

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);
	


	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);


	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.m_fOwnerSpeed = 150.f;
	RigidBodyDesc.m_fOwnerAccel = 10.f;
	RigidBodyDesc.m_fOwnerRadSpeed = D3DXToRadian(90.0f);
	RigidBodyDesc.m_fOwnerRadAccel = 0.3f;
	RigidBodyDesc.m_fOwnerJump = 5.f;
	RigidBodyDesc.m_fOwnerJumpScale = 1.f;

	RigidBodyDesc.m_fFrictional = 0.01f;
	RigidBodyDesc.m_fRadFrictional = 0.02f;
	RigidBodyDesc.m_fRadZ = 0.01f;


	RigidBodyDesc.m_fOwnerLiftSpeed = 10.f;
	RigidBodyDesc.m_fOwnerLiftAccel = 0.3f;
	RigidBodyDesc.m_fRadDrag = 1.f;
	RigidBodyDesc.m_fDirDrag = 0.05f;

	m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);
	m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	

	COLLISION_TYPE	eCollisiontype = COLLISION_TYPE::OBJECT;
	m_pColliderCom = Add_Component<CCollider_Sphere>(&eCollisiontype);
	m_pColliderCom->Set_WeakPtr(&m_pColliderCom);
	m_pColliderCom->Link_Transform(m_pTransformCom);


	SetUp_Components_For_Chiled();

	return S_OK;
}

void CBillboard_Object::LookAtCamera()
{
	_float4x4		ViewMatrix;

	DEVICE->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, *(_float3*)&ViewMatrix.m[0][0], true);
	m_pTransformCom->Set_State(CTransform::STATE_UP, *(_float3*)&ViewMatrix.m[1][0], true);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, *(_float3*)&ViewMatrix.m[2][0], true);

}

void CBillboard_Object::On_Collision_Enter(CCollider* _Other_Collider)
{
	__super::On_Collision_Enter(_Other_Collider);

	if (COLLISION_TYPE::PLAYER == _Other_Collider->Get_Collision_Type())
	{
		CGameObject* pOtherCollider = _Other_Collider->Get_Owner();
		_float3		pRockPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION, true);
		_float3 vOtherColliderSpeed = pOtherCollider->Get_Component<CRigid_Body>()->Get_Vector(RIGID_BODY::SPEED);
		_float3 vCollisionDirection = pRockPos - pOtherCollider->Get_Component<CTransform>()->Get_State(CTransform::STATE_POSITION, true);

		D3DXVec3Normalize(&vCollisionDirection, &vCollisionDirection);
		vCollisionDirection *= D3DXVec3Length(&vOtherColliderSpeed);
		vOtherColliderSpeed += vCollisionDirection;

		m_pRigidBodyCom->Add_Force(vOtherColliderSpeed * 3.f);


		((CRock_PSystem*)GAMEINSTANCE->Get_ParticleSystem<CRock_PSystem>(CURRENT_LEVEL, TEXT("Particle_Rock")))->AddParticle(50, m_pTransformCom);
		CGameObject* pParticle = GAMEINSTANCE->Add_GameObject<CBomb_Effect>(CURRENT_LEVEL, TEXT("Explosion"), nullptr, nullptr, false);
		((CBomb_Effect*)pParticle)->Set_Pos(pRockPos);
		((CBomb_Effect*)pParticle)->Get_Component<CTransform>()->Scaling(_float3(25.f, 25.f, 25.f));
		Set_Enable(false);
		//폭발 이펙트 스케일링 따로 지정해줘야함
	}
	
}

void CBillboard_Object::On_Collision_Stay(CCollider* _Other_Collider)
{
	__super::On_Collision_Stay(_Other_Collider);
}

void CBillboard_Object::On_Collision_Exit(CCollider* _Other_Collider)
{
	__super::On_Collision_Exit(_Other_Collider);
}


void CBillboard_Object::Free()
{
	__super::Free();


}

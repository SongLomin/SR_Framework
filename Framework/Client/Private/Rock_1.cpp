#include "stdafx.h"
#include "Rock_1.h"
#include "GameInstance.h"
#include "Rock_PSystem.h"
#include "Bomb_Effect.h"

CRock_1::CRock_1()
{
}

CRock_1::CRock_1(const CRock_1& Prototype)
{
	*this = Prototype;
}

HRESULT CRock_1::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CRock_1::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(rand() % 2000, rand() % 2000, rand() % 2000));


	return S_OK;
}

void CRock_1::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CRock_1::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
}

HRESULT CRock_1::Render()
{
	
	m_pTransformCom->Scaling(_float3(70.f, 70.f, 70.f), true);

	m_pTransformCom->Bind_WorldMatrix();


	m_pRendererCom->Bind_Texture(0);

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 253);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pVIBufferCom->Render();

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pRendererCom->UnBind_Texture();



	return S_OK;
}
	



void CRock_1::On_Collision_Enter(CCollider* _Other_Collider)
{
	__super::On_Collision_Enter(_Other_Collider);
	
	
	
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
		Set_Dead();
		//폭발 이펙트 스케일링 따로 지정해줘야함
	}
	
}

void CRock_1::On_Collision_Stay(CCollider* _Other_Collider)
{
	__super::On_Collision_Enter(_Other_Collider); 
}

void CRock_1::On_Collision_Exit(CCollider* _Other_Collider)
{
	__super::On_Collision_Exit(_Other_Collider);
}

void CRock_1::SetUp_Components_For_Chiled()
{
	m_pRendererCom->Set_Textures_From_Key(TEXT("Rock"), MEMORY_TYPE::MEMORY_STATIC);

	m_pColliderCom->Set_Collider_Size(_float3(70.f, 70.f, 70.f));

}

CRock_1* CRock_1::Create()
{
	CREATE_PIPELINE(CRock_1);
}

CGameObject* CRock_1::Clone(void* pArg)
{
	CLONE_PIPELINE(CRock_1);
}

void CRock_1::Free()
{
	__super::Free();

	RETURN_WEAKPTR(m_pTransformCom);
	RETURN_WEAKPTR(m_pRendererCom);
	RETURN_WEAKPTR(m_pVIBufferCom);
	RETURN_WEAKPTR(m_pColliderCom);
	RETURN_WEAKPTR(m_pRigidBodyCom);

	delete this;
}

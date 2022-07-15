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

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(rand() % 1000, rand() % 150, rand() % 1000));


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
	
	m_pTransformCom->Scaling(_float3(30.f, 30.f, 30.f), true);

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

	m_pColliderCom->Set_Collider_Size(_float3(20.f, 20.f, 20.f));

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

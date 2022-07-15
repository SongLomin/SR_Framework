#include "stdafx.h"
#include "Rock_4.h"
#include "GameInstance.h"

CRock_4::CRock_4()
{
}

CRock_4::CRock_4(const CRock_4& Prototype)
{
	*this = Prototype;
}

HRESULT CRock_4::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CRock_4::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(rand() % 2000, rand() % 2000, rand() % 2000));

	return S_OK;
}

void CRock_4::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CRock_4::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
}

HRESULT CRock_4::Render()
{
	m_pTransformCom->Scaling(_float3(10.f, 10.f, 10.f), true);

	m_pTransformCom->Bind_WorldMatrix();


	m_pRendererCom->Bind_Texture(3);

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 253);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pVIBufferCom->Render();

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pRendererCom->UnBind_Texture();



	return S_OK;
}

void CRock_4::On_Collision_Enter(CCollider* _Other_Collider)
{
	__super::On_Collision_Enter(_Other_Collider);
}

void CRock_4::On_Collision_Stay(CCollider* _Other_Collider)
{
	__super::On_Collision_Stay(_Other_Collider);
}

void CRock_4::On_Collision_Exit(CCollider* _Other_Collider)
{
	__super::On_Collision_Exit(_Other_Collider);
}

void CRock_4::SetUp_Components_For_Chiled()
{
	m_pRendererCom->Set_Textures_From_Key(TEXT("Rock"), MEMORY_TYPE::MEMORY_STATIC);

	m_pColliderCom->Set_Collider_Size(_float3(10.f, 10.f, 10.f));
}

CRock_4* CRock_4::Create()
{
	CREATE_PIPELINE(CRock_4);
}

CGameObject* CRock_4::Clone(void* pArg)
{
	CLONE_PIPELINE(CRock_4);
}

void CRock_4::Free()
{
	__super::Free();

	delete this;
}

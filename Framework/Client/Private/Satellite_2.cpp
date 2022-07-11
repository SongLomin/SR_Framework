#include "stdafx.h"
#include "Satellite_2.h"
#include "GameInstance.h"

CSatellite_2::CSatellite_2()
{
}

CSatellite_2::CSatellite_2(const CSatellite_2& Prototype)
{
	*this = Prototype;
}

HRESULT CSatellite_2::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CSatellite_2::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(rand() % 1000, rand() % 150, rand() % 1000));


	return S_OK;
}

void CSatellite_2::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CSatellite_2::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
}

HRESULT CSatellite_2::Render()
{

	m_pTransformCom->Scaling(_float3(300.f, 200.f, 30.f), true);

	m_pTransformCom->Bind_WorldMatrix();


	m_pRendererCom->Bind_Texture(1);

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 253);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pVIBufferCom->Render();

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pRendererCom->UnBind_Texture();



	return S_OK;
}




void CSatellite_2::On_Collision_Enter(CCollider* _Other_Collider)
{
	__super::On_Collision_Enter(_Other_Collider);
}

void CSatellite_2::On_Collision_Stay(CCollider* _Other_Collider)
{
	__super::On_Collision_Enter(_Other_Collider);
}

void CSatellite_2::On_Collision_Exit(CCollider* _Other_Collider)
{
	__super::On_Collision_Exit(_Other_Collider);
}

void CSatellite_2::SetUp_Components_For_Chiled()
{
	m_pRendererCom->Set_Textures_From_Key(TEXT("Satellite"), MEMORY_TYPE::MEMORY_STATIC);

	m_pColliderCom->Set_Collider_Size(_float3(300.f, 200.f, 30.f));

}

CSatellite_2* CSatellite_2::Create()
{
	CREATE_PIPELINE(CSatellite_2);
}

CGameObject* CSatellite_2::Clone(void* pArg)
{
	CLONE_PIPELINE(CSatellite_2);
}

void CSatellite_2::Free()
{
	__super::Free();

	RETURN_WEAKPTR(m_pTransformCom);
	RETURN_WEAKPTR(m_pRendererCom);
	RETURN_WEAKPTR(m_pVIBufferCom);
	RETURN_WEAKPTR(m_pColliderCom);
	RETURN_WEAKPTR(m_pRigidBodyCom);

	delete this;
}

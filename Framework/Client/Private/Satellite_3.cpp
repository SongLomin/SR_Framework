#include "stdafx.h"
#include "Satellite_3.h"
#include "GameInstance.h"

CSatellite_3::CSatellite_3()
{
}

CSatellite_3::CSatellite_3(const CSatellite_3& Prototype)
{
	*this = Prototype;
}

HRESULT CSatellite_3::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CSatellite_3::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(1500.f,  1200.f, 1700.f));


	return S_OK;
}

void CSatellite_3::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CSatellite_3::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
}

HRESULT CSatellite_3::Render()
{

	m_pTransformCom->Scaling(_float3(500.f, 300.f, 30.f), true);

	m_pTransformCom->Bind_WorldMatrix();

	
	m_pRendererCom->Bind_Texture(2);

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 253);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pVIBufferCom->Render();

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pRendererCom->UnBind_Texture();



	return S_OK;
}




void CSatellite_3::On_Collision_Enter(CCollider* _Other_Collider)
{

}

void CSatellite_3::On_Collision_Stay(CCollider* _Other_Collider)
{
	__super::On_Collision_Enter(_Other_Collider);
}

void CSatellite_3::On_Collision_Exit(CCollider* _Other_Collider)
{
	__super::On_Collision_Exit(_Other_Collider);
}

void CSatellite_3::SetUp_Components_For_Chiled()
{
	m_pRendererCom->Set_Textures_From_Key(TEXT("Satellite"), MEMORY_TYPE::MEMORY_STATIC);

	m_pColliderCom->Set_Collider_Size(_float3(500.f, 300.f, 30.f));

}

CSatellite_3* CSatellite_3::Create()
{
	CREATE_PIPELINE(CSatellite_3);
}

CGameObject* CSatellite_3::Clone(void* pArg)
{
	CLONE_PIPELINE(CSatellite_3);
}

void CSatellite_3::Free()
{
	__super::Free();

	RETURN_WEAKPTR(m_pTransformCom);
	RETURN_WEAKPTR(m_pRendererCom);
	RETURN_WEAKPTR(m_pVIBufferCom);
	RETURN_WEAKPTR(m_pColliderCom);
	RETURN_WEAKPTR(m_pRigidBodyCom);

	delete this;
}

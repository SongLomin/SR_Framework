#include "stdafx.h"
#include "Satellite_1.h"
#include "GameInstance.h"
#include <Friendly_GPS.h>

CSatellite_1::CSatellite_1()
{
}

CSatellite_1::CSatellite_1(const CSatellite_1& Prototype)
{
	*this = Prototype;
}

HRESULT CSatellite_1::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CSatellite_1::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(100.f, 100.f, 1000.f));

	GAMEINSTANCE->Add_GameObject<CFriendly_GPS>(CURRENT_LEVEL, TEXT("GPS_Friendly"), m_pTransformCom);
	return S_OK;
}

void CSatellite_1::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CSatellite_1::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
}

HRESULT CSatellite_1::Render()
{

	m_pTransformCom->Scaling(_float3(100.f, 100.f, 30.f), true);

	m_pTransformCom->Bind_WorldMatrix();


	m_pRendererCom->Bind_Texture(0);

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 200);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pVIBufferCom->Render();

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pRendererCom->UnBind_Texture();



	return S_OK;
}




void CSatellite_1::On_Collision_Enter(CCollider* _Other_Collider)
{
	__super::On_Collision_Enter(_Other_Collider);
}

void CSatellite_1::On_Collision_Stay(CCollider* _Other_Collider)
{
	__super::On_Collision_Enter(_Other_Collider);
}

void CSatellite_1::On_Collision_Exit(CCollider* _Other_Collider)
{
	__super::On_Collision_Exit(_Other_Collider);
}

void CSatellite_1::SetUp_Components_For_Chiled()
{
	m_pRendererCom->Set_Textures_From_Key(TEXT("Satellite"), MEMORY_TYPE::MEMORY_STATIC);

	m_pColliderCom->Set_Collider_Size(_float3(100.f, 100.f, 30.f));

}

CSatellite_1* CSatellite_1::Create()
{
	CREATE_PIPELINE(CSatellite_1);
}

CGameObject* CSatellite_1::Clone(void* pArg)
{
	CLONE_PIPELINE(CSatellite_1);
}

void CSatellite_1::Free()
{
	__super::Free();

	RETURN_WEAKPTR(m_pTransformCom);
	RETURN_WEAKPTR(m_pRendererCom);
	RETURN_WEAKPTR(m_pVIBufferCom);
	RETURN_WEAKPTR(m_pColliderCom);
	RETURN_WEAKPTR(m_pRigidBodyCom);

	delete this;
}

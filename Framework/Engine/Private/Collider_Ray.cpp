#include "Collider_Ray.h"
#include "GameInstance.h"

CCollider_Ray::CCollider_Ray(const CCollider_Ray& Prototype)
{
	*this = Prototype;
}

HRESULT CCollider_Ray::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCollider_Ray::Initialize(void* pArg)
{
	
	m_iID = ++g_iNextID;
	m_eCollision_Type = *(COLLISION_TYPE*)pArg;

	m_eShape = COLLIDER_SHAPE::RAY;

	return S_OK;
}

void CCollider_Ray::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CCollider_Ray::LateTick(_float fTimeDelta)
{
}

HRESULT CCollider_Ray::Debug_Render()
{


	return S_OK;
}

void CCollider_Ray::Set_Collider_Size(const _float3& _Size)
{

}

_float3 CCollider_Ray::Get_Collider_Size()
{
	return _float3();
}

_float3 CCollider_Ray::Get_Collider_Position()
{
	return _float3();
}

RAY CCollider_Ray::Get_ColliderRay()
{
	
	m_rayCollider.Pos = m_pMyTransformCom->Get_State(CTransform::STATE_POSITION, true)+m_vOffSet;
	m_rayCollider.Dir = m_pMyTransformCom->Get_State(CTransform::STATE_LOOK, true);
	m_rayCollider.fLength = 200.f;

	return m_rayCollider;
	
}

CCollider_Ray* CCollider_Ray::Create()
{
	CREATE_PIPELINE(CCollider_Ray);
}

CComponent* CCollider_Ray::Clone(void* pArg)
{
	CLONE_PIPELINE(CCollider_Ray);
}

void CCollider_Ray::Free()
{
	__super::Free();

	delete this;
}

#include "stdafx.h"
#include "Bullet.h"
#include "GameInstance.h"

CBullet::CBullet()
{
}

void CBullet::Tick(_float fTimeDelta)
{
    __super::Tick(fTimeDelta);

	m_fLifeTime -= fTimeDelta;

	if (m_fLifeTime < 0.f)
	{
		Set_Dead();
	}
}

void CBullet::LateTick(_float fTimeDelta)
{
    __super::LateTick(fTimeDelta);

}

HRESULT CBullet::SetUp_Components(COLLISION_TYPE _eCollisionType)
{
	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr((void**)&m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);

	COLLISION_TYPE eCollisionType = _eCollisionType;
	m_pColliderCom = Add_Component<CCollider_Sphere>(&eCollisionType);
	m_pColliderCom->Set_WeakPtr(&m_pColliderCom);
	m_pColliderCom->Link_Transform(m_pTransformCom);

	/*_float3 ColliderSize = m_pTransformCom->Get_Scaled();
	_float3 RenderScale = _float3(0.2f, 0.2f, 0.2f);
	ColliderSize.x *= RenderScale.x;
	ColliderSize.y *= RenderScale.y;
	ColliderSize.z *= RenderScale.z;

	m_pColliderCom->Set_Collider_Size(ColliderSize);*/

	SetUp_Components_For_Child();

    return S_OK;
}

void CBullet::Init_BulletPosition(_float4x4* _pWorldMat)
{
	//총알의 로컬 행렬은 부모가 없기 때문에 월드 행렬이 된다.
	m_pTransformCom->Set_LocalMatrix(*_pWorldMat);
}


void CBullet::Free()
{
    __super::Free();
}

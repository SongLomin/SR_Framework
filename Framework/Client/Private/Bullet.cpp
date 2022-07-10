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
		//Set_Dead();
		Set_Enable(false);
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

void CBullet::OnEnable(void* _Arg)
{
	D3DXMATRIX IdentityMat;
	D3DXMatrixIdentity(&IdentityMat);

	m_fLifeTime = 1.f;
	m_pTransformCom->Set_LocalMatrix(IdentityMat);
	m_pRigidBodyCom->SetUp_Origin_DirVector();
	m_pRigidBodyCom->Reset_Force();

	m_pColliderCom->OnEnable(_Arg);
}

void CBullet::OnDisable()
{
	m_pColliderCom->OnDisable();
}


void CBullet::Free()
{
    __super::Free();
}

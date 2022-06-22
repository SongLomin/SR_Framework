#include "Collider.h"
#include "GameInstance.h"

_uint CCollider::g_iNextID = 0;

CCollider::CCollider(const CCollider& Prototype)
{
}

HRESULT CCollider::Render()
{
    return S_OK;
}

void CCollider::Link_Transform(CTransform* _TransformCom)
{
    m_pMyTransformCom = _TransformCom;
    m_pMyTransformCom->Set_WeakPtr(&m_pMyTransformCom);
}

void CCollider::Set_Collision_Type(COLLISION_TYPE _eType)
{
    m_eCollision_Type = _eType;
}

void CCollider::Free()
{
    __super::Free();

}

#include "Collider.h"
#include "GameInstance.h"

_uint CCollider::g_iNextID = 0;

CCollider::CCollider(const CCollider& Prototype)
{
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

void CCollider::Link_Pre_Collider(CCollider_Pre* _PreCol)
{
    m_pPreCollider = _PreCol;
    WEAK_PTR(m_pPreCollider);
}

CCollider_Pre* CCollider::Get_Pre_Collider() const
{
    return m_pPreCollider;
}

void CCollider::Free()
{
    __super::Free();
    
    if (m_pMesh)
    {
        m_pMesh->Release();

        m_pMesh = nullptr;
    }

    RETURN_WEAKPTR(m_pMyTransformCom);
    RETURN_WEAKPTR(m_pPreCollider);

}

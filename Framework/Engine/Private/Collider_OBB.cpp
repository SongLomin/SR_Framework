#include "Collider_OBB.h"
#include "GameInstance.h"

CCollider_OBB::CCollider_OBB(const CCollider_OBB& Prototype)
{
    *this = Prototype;

}

HRESULT CCollider_OBB::Initialize_Prototype()
{
    m_eShape = COLLIDER_SHAPE::OBB;
    return S_OK;
}

HRESULT CCollider_OBB::Initialize(void* pArg)
{
    m_eCollision_Type = *(COLLISION_TYPE*)pArg;
    m_iID = g_iNextID++;

    GAMEINSTANCE->Add_Collider(this);
    return S_OK;
}



void CCollider_OBB::Set_Collider_Size(const _float3& _Size)
{
    m_OBBInfo.SetSize(_Size);
}

void CCollider_OBB::Tick(_float _TimeDelta)
{
    if (m_pMyTransformCom)
    {
        m_OBBInfo.SetMatrix(&m_pMyTransformCom->Get_WorldMatrix());
    }
}

_float3 CCollider_OBB::Get_Collider_Size()
{
    return m_OBBInfo.ObbSize;
}

_float3 CCollider_OBB::Get_Collider_Position()
{
    return m_OBBInfo.ObbCenterPos;
}


CCollider_OBB* CCollider_OBB::Create()
{
    CREATE_PIPELINE(CCollider_OBB);
}

CComponent* CCollider_OBB::Clone(void* pArg)
{
    CLONE_PIPELINE(CCollider_OBB);
}

void CCollider_OBB::Free()
{
    __super::Free();

    delete this;

}
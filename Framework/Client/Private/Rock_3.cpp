#include "stdafx.h"
#include "Rock_3.h"
#include "GameInstance.h"

CRock_3::CRock_3()
{
}

CRock_3::CRock_3(const CRock_3& Prototype)
{
    *this = Prototype;
}

HRESULT CRock_3::Initialize_Prototype()
{
    return S_OK;
}

HRESULT CRock_3::Initialize(void* pArg)
{
    if (FAILED(SetUp_Components()))
        return E_FAIL;

    m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(rand() % 1000, rand() % 1000, rand() % 1000));

    return S_OK;
}

void CRock_3::Tick(_float fTimeDelta)
{
    __super::Tick(fTimeDelta);
}

void CRock_3::LateTick(_float fTimeDelta)
{
    __super::LateTick(fTimeDelta);
}

HRESULT CRock_3::Render()
{
    m_pTransformCom->Scaling(_float3(30.f, 30.f, 30.f), true);

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

void CRock_3::On_Collision_Enter(CCollider* _Other_Collider)
{
    __super::On_Collision_Enter(_Other_Collider);
}

void CRock_3::On_Collision_Stay(CCollider* _Other_Collider)
{
    __super::On_Collision_Stay(_Other_Collider);
}

void CRock_3::On_Collision_Exit(CCollider* _Other_Collider)
{
    __super::On_Collision_Exit(_Other_Collider);
}

void CRock_3::SetUp_Components_For_Chiled()
{
    m_pRendererCom->Set_Textures_From_Key(TEXT("Rock"), MEMORY_TYPE::MEMORY_STATIC);

    m_pColliderCom->Set_Collider_Size(_float3(30.f, 30.f, 30.f));
}

CRock_3* CRock_3::Create()
{
    CREATE_PIPELINE(CRock_3);
}

CGameObject* CRock_3::Clone(void* pArg)
{
    CLONE_PIPELINE(CRock_3);
}

void CRock_3::Free()
{
    __super::Free();
    delete this;
}

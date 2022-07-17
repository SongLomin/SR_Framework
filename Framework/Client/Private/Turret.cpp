#include "stdafx.h"
#include "Turret.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "Fire_PSystem.h"
#include "SpotLight.h"

CTurret::CTurret()
{
}

HRESULT CTurret::Initialize_Prototype()
{
    return S_OK;
}

void CTurret::Tick(_float fTimeDelta)
{
    __super::Tick(fTimeDelta);

    //부모가 없는 경우: 아이템인 경우
    if (!m_pTransformCom->Get_Parent())
    {
        if (m_fLifeTime < 0.f)
        {
            Set_Enable(false);
        }

        m_pTransformCom->Turn(_float3(0.f, 1.f, 0.f), 1.f, fTimeDelta, true);
        COLLISION_TYPE eCollisionType = COLLISION_TYPE::ITEM;
        m_fLifeTime -= fTimeDelta;
        m_pColliderCom->Set_Enable(true, &eCollisionType);
        return;
    }

    m_fCurTime -= fTimeDelta;

    if (LookAt_Targeting())
        return;
    

    if (Get_Controller() == CONTROLLER::PLAYER)
        LookAt_Aim();
    else if (Get_Controller() == CONTROLLER::AI)
        m_pTransformCom->LookAt(_float3(0.f, 0.f, 1.f));
}

void CTurret::LateTick(_float fTimeDelta)
{
    __super::LateTick(fTimeDelta);

    _float3 vPos = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);

    if (GAMEINSTANCE->IsIn(&vPos))
        m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_DEFERRED, this);
}

HRESULT CTurret::Render_Begin(ID3DXEffect** Shader)
{
    m_pTransformCom->Scaling(m_vScale, true);
    m_pTransformCom->Bind_WorldMatrix(D3D_ALL, D3D_ALL);

    D3DXHANDLE ColorHandle = (*Shader)->GetParameterByName(0, "Color");

   

    (*Shader)->SetFloatArray(ColorHandle, floatArray, 3);


    return S_OK;

}

HRESULT CTurret::Render()
{
    __super::Render();
    m_pMeshCom->Render_Mesh();
    

    return S_OK;
}

HRESULT CTurret::SetUp_Components()
{
    m_pTransformCom = Add_Component<CTransform>();
    WEAK_PTR(m_pTransformCom);

    m_pMeshCom = Add_Component<CMesh_Cube>();
    WEAK_PTR(m_pMeshCom);

    m_pMeshTestCom = Add_Component<CMesh_Test>();
    WEAK_PTR(m_pMeshCom);

    m_pRendererCom = Add_Component<CRenderer>();
    WEAK_PTR(m_pRendererCom);

    COLLISION_TYPE eCollisionType = COLLISION_TYPE::ITEM;
    m_pColliderCom = Add_Component<CCollider_Sphere>(&eCollisionType);
    WEAK_PTR(m_pColliderCom);
    m_pColliderCom->Set_Collider_Size(_float3(40.f, 40.f, 40.f));
    m_pColliderCom->Link_Transform(m_pTransformCom);
    m_pColliderCom->Set_Enable(false);

    m_pLightCom = Add_Component<CSpotLight>();
    m_pLightCom->Set_Preset_ItemLight();
    WEAK_PTR(m_pLightCom);

    SetUp_Components_For_Child();

    return S_OK;
}


void CTurret::SetUp_Variables_For_Child(_float _fMaxTime, _float3  _vScale, _float   _floatArray[3])
{
    m_fMaxTime = _fMaxTime;
    m_vScale = _vScale;
    floatArray[0] = _floatArray[0];
    floatArray[1] = _floatArray[1];
    floatArray[2] = _floatArray[2];
}

void CTurret::On_Change_Controller(const CONTROLLER& _eController)
{
}

void CTurret::On_EventMessage(void* _Arg)
{
    wstring* Message = reinterpret_cast<wstring*>(_Arg);

    //발사 명령
    if (lstrcmpW(Message->c_str(), m_pEventMessage) == 0)
    {
        if (m_fCurTime < 0)
        {
             Command_Fire();
             m_fCurTime = m_fMaxTime;

             if (Get_Controller() == CONTROLLER::AI)
             {
                 m_fCurTime *= 5.f;
             }
        }
    }
}

void CTurret::On_Collision_Enter(CCollider* _Other_Collider)
{
}

void CTurret::On_Collision_Stay(CCollider* _Other_Collider)
{
    if (_Other_Collider->Get_Collision_Type() == COLLISION_TYPE::PLAYER)
    {
        if (!m_pColliderCom->Get_Enable())
            return;

        CTransform* PlayerTransformCom = _Other_Collider->Get_Owner()->Get_Component<CTransform>();

        _float3 PlayerPos = PlayerTransformCom->Get_State(CTransform::STATE_POSITION, true);
        _float3 DirPos = PlayerPos - m_pTransformCom->Get_State(CTransform::STATE_POSITION, true);

        _float fDistance = D3DXVec3Length(&DirPos);
        _float3 NormalDir;
        D3DXVec3Normalize(&NormalDir, &DirPos);

        if (fDistance < 9.f)
        {
            _float4x4 IdentityMat;
            D3DXMatrixIdentity(&IdentityMat);
            m_pTransformCom->Set_LocalMatrix(IdentityMat);

            

            m_pTransformCom->Set_Parent(PlayerTransformCom);
            PlayerTransformCom->Add_Child(m_pTransformCom);
            m_pColliderCom->Set_Enable(false);
            m_pLightCom->Set_Enable(false);

            Set_Controller(PlayerTransformCom->Get_Owner()->Get_Controller());
            
        }

        else
        {
            m_pTransformCom->Add_Position(NormalDir * TIMEDELTA * m_fMagnetic);
            m_fMagnetic += TIMEDELTA * 3.f;
        }
    }

}

void CTurret::On_Collision_Exit(CCollider* _Other_Collider)
{
}

void CTurret::OnEnable(void* _Arg)
{
    if (!m_pTransformCom->Get_Parent())
    {
        _float4x4 IdentityMat;
        D3DXMatrixIdentity(&IdentityMat);


        m_fLifeTime = 30.f;
        m_pTransformCom->Set_LocalMatrix(IdentityMat);
        m_pColliderCom->Set_Enable(false);
        m_pLightCom->Set_Enable(true);
        m_fMagnetic = 3.f;

        
        
    }
}

void CTurret::OnDisable()
{

}

void CTurret::Set_Player_Target(CGameObject* _Target)
{
    if (m_pTarget)
    {
        m_pTarget->Return_WeakPtr(&m_pTarget);
        m_pTarget = nullptr;

    }

    if (m_pBoxObject)
    {
        m_pBoxObject->Set_Enable(false);
        m_pBoxObject->Return_WeakPtr(&m_pBoxObject);
        m_pBoxObject = nullptr;
    }

    if (!_Target)
    {
        m_pTarget = nullptr;
        m_pBoxObject = nullptr;

        return;
    }

    m_pTarget = _Target;
    WEAK_PTR(m_pTarget);


    list<CGameObject*> Targetings = m_pTarget->Get_Children_From_Key(TEXT("Targeting"));
    if (Targetings.empty())
        return;

    m_pBoxObject = Targetings.front();
    WEAK_PTR(m_pBoxObject);

}

void CTurret::Set_AI_Target(CGameObject* _Target)
{
    if (m_pTarget)
    {
        m_pTarget->Return_WeakPtr(&m_pTarget);
        m_pTarget = nullptr;

    }

    if (!_Target)
    {
        m_pTarget = nullptr;

        return;
    }

    m_pTarget = _Target;
    WEAK_PTR(m_pTarget);

}

_bool CTurret::LookAt_Targeting()
{
    if (!m_pTarget)
    {
        return false;
    }

    m_pTransformCom->LookAt(m_pTarget->Get_Component<CTransform>(), true);


    if (m_pBoxObject)
        m_pBoxObject->Set_Enable(true);

    return true;
}

void CTurret::LookAt_Aim()
{
    _float3 MouseEndPos;
    RAY	MouseWorldPos;
    MouseWorldPos = CMath_Utillity::Get_MouseRayInWorldSpace();
    MouseEndPos = MouseWorldPos.Pos + (MouseWorldPos.Dir * 1000.f);

    m_pTransformCom->LookAt(MouseEndPos, true);
}

void CTurret::Free()
{
    __super::Free();
    RETURN_WEAKPTR(m_pTarget);
    RETURN_WEAKPTR(m_pBoxObject);
}

#include "stdafx.h"
#include "Turret.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "Fire_PSystem.h"

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

    m_pRendererCom = Add_Component<CRenderer>();
    WEAK_PTR(m_pRendererCom);

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
    if (lstrcmpW(Message->c_str(), TEXT("Fire")) == 0)
    {
        if (m_fCurTime <= 0)
        {
             Command_Fire();
             m_fCurTime = m_fMaxTime;
        }
    }
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

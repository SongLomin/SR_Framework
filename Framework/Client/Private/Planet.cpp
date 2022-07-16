#include "stdafx.h"
#include "Planet.h"
#include "GameInstance.h"
#include <Math_Utillity.h>
#include "Level_Loading.h"
#include "Dive.h"


CPlanet::CPlanet()
{
}

void CPlanet::Set_ScreenPos()
{
    CMath_Utillity::WorldToScreen(&m_pTransformCom->Get_State(CTransform::STATE_POSITION, true), &m_vScreenPos);

    m_lPontPos.x = (_long)m_vScreenPos.x;
    m_lPontPos.y = (_long)m_vScreenPos.y;
}

void CPlanet::Set_MyWorldPos(_float3 _Pos)
{

    CCamera* pCurrentCam = GAMEINSTANCE->Get_Camera();
    WEAK_PTR(pCurrentCam);

    ISVALID(pCurrentCam, );

    _float3 CamWorldPos = pCurrentCam->Get_Transform()->Get_World_State(CTransform::STATE_POSITION);
   
    m_vMyWorldPos.x = _Pos.x ;
    m_vMyWorldPos.y = _Pos.y ;
    m_vMyWorldPos.z = _Pos.z ;

    RETURN_WEAKPTR(pCurrentCam);

    m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_vMyWorldPos, true);
}


HRESULT CPlanet::Initialize_Prototype()
{
    return S_OK;
}

HRESULT CPlanet::Initialize(void* pArg)
{
    m_pDiveUi = GAMEINSTANCE->Add_GameObject<CDive>(LEVEL_SELECTPLANET, TEXT("Dive"));
    m_pDiveUi->Set_Enable(false);


    return S_OK;
  
}

void CPlanet::Tick(_float fTimeDelta)
{
    __super::Tick(fTimeDelta);

    Set_MyWorldPos(m_vStartPos);

    LookAtCamera();

    m_pTransformCom->Scaling(m_vMyScale, true);

    Update_Ray();

    Set_ScreenPos();


    _float3 PickedPosition;

    // 마우스 움직임 충돌시
    if (true == CMath_Utillity::Picking_VIBuffer(m_pVI_BufferCom, m_pTransformCom, m_MouseWorldRay, &PickedPosition))
    {
        
        m_pDiveUi->Set_Enable(true);
        GAMEINSTANCE->Add_Text(m_lPontPos, m_szPontText, 0);

         // 충돌하고 키 입력시
        if (KEY_INPUT(KEY::F, KEY_STATE::TAP) && !m_bLevelChange)
        {
            GAMEINSTANCE->PlaySoundW(TEXT("Dive.wav"), EFFECT, 2.f);
            GAMEINSTANCE->Get_CurrentLevel()->Change_Level(this, m_eMyLevel);
            m_bLevelChange = true;
            return;
        }
    }

    else
    {
        m_pDiveUi->Set_Enable(false);
    }

}

void CPlanet::LateTick(_float fTimeDelta)
{
    __super::LateTick(fTimeDelta);

    m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);

 
}

HRESULT CPlanet::Render()
{

    m_pTransformCom->Bind_WorldMatrix();


    m_pRendererCom->Bind_Texture(m_iTextueIndex);

    DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
    DEVICE->SetRenderState(D3DRS_ALPHAREF, m_iAlphaValue);
    DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

    __super::Render();

    DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

    m_pRendererCom->UnBind_Texture();


    return S_OK;
}

HRESULT CPlanet::SetUp_Components()
{
    m_pTransformCom = Add_Component<CTransform>();
    WEAK_PTR(m_pTransformCom);

    m_pRendererCom = Add_Component<CRenderer>();
    WEAK_PTR(m_pRendererCom);

    m_pVI_BufferCom = Add_Component<CVIBuffer_Rect>();
    WEAK_PTR(m_pVI_BufferCom);
    m_pRendererCom->Set_Textures_From_Key(TEXT("Planet"), MEMORY_TYPE::MEMORY_STATIC);

    Set_ScreenPos();

    SetUp_Components_For_Child();
    return S_OK;
}

void CPlanet::SetUp_Varialbes_For_Child(_float3 _StartPos, _tchar* FontText, _point PontPos, _uint TextureIndex, LEVEL _Level, _float3 Scale)
{
    m_lPontPos = PontPos;


    m_szPontText = FontText;
    m_iTextueIndex = TextureIndex;

    m_vMyScale = Scale;

    m_vStartPos = _StartPos;
    m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_vStartPos);

    m_eMyLevel = _Level;
}



void CPlanet::LookAtCamera()
{
    _float4x4		ViewMatrix;

    DEVICE->GetTransform(D3DTS_VIEW, &ViewMatrix);
    D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

    m_pTransformCom->Set_State(CTransform::STATE_RIGHT, *(_float3*)&ViewMatrix.m[0][0], true);
    m_pTransformCom->Set_State(CTransform::STATE_UP, *(_float3*)&ViewMatrix.m[1][0], true);
    m_pTransformCom->Set_State(CTransform::STATE_LOOK, *(_float3*)&ViewMatrix.m[2][0], true);
}

void CPlanet::Update_Ray()
{
    m_MouseWorldRay = CMath_Utillity::Get_MouseRayInWorldSpace();
}

void CPlanet::Free()
{
    __super::Free();
}

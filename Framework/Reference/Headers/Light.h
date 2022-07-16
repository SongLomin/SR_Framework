#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CLight abstract :
    public CComponent
{
protected:
    CLight() = default;
    CLight(const CLight & Prototype);
    virtual ~CLight() = default;

public:
    virtual void    Bind_ConstBuffer() PURE;
    virtual void    DrawLight() PURE;
    ID3DXEffect**   Get_Effect();
    //오프셋 포지션 지정
    void            Set_Margin_Position(const _float3& _Position);
    //조명이 해당 방향을 바라본다. (Point 제외)
    void            Set_LooK_Dir(const _float3& _Look);
    //조명의 밝기 0~2 사이의 float 값
    void            Set_LightColorScale(const _float& _ColorScale);
    //조명의 색 RGB 0~1사이의 float 값
    void            Set_LightColor(const D3DXCOLOR& _Color);
    //조명의 범위
    void            Set_LightRange(const _float& _Range);
    //조명 구조체를 매개변수로 새로 설정한다.
    void            Set_D3DLight(const _D3DLIGHT9& _D3DLight);
    void            Set_Light_Variables(D3DXCOLOR _Color,_float _lightambient, _float _lightdiffuse, _float _lightspecular, _float3 _lightmarginposition,
        _float3 _lightdirection, _float _lightrange = 0.f, _float _lightattenuation0 = 0.f, _float _lightattenuation1 = 0.f, _float _lightattenuation2 = 0.f,
        _float _lightfalloff = 0.f, _float _lighttheta = 0.f, _float _lightphi = 0.f);
public:
    void            Set_Preset_PowLight();
    void            Set_Preset_SunLight();
    void            Set_Preset_ItemLight();


protected:
    ID3DXEffect**   m_ppLightEffect = nullptr;
    D3DLIGHT9       m_D3DLight;
    _float3         m_Margin_Position = _float3(0.f, 0.f, 0.f);
    _float          m_fColorScale = 1.f;
    _float          m_fLifeTime = 300.f;
    D3DXCOLOR       m_Color = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);

};

END
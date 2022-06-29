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
    void            Set_Margin_Position(const _float3& _Position);
    void            Set_LooK_Dir(const _float3& _Look);
    void            Set_LightColorScale(const _float& _ColorScale);
    void            Set_LightRange(const _float& _Range);
    void            Set_D3DLight(const _D3DLIGHT9& _D3DLight);
    

protected:
    ID3DXEffect**   m_ppLightEffect = nullptr;
    D3DLIGHT9       m_D3DLight;
    _float3         m_Margin_Position = _float3(0.f, 0.f, 0.f);
    _float           m_fColorScale = 1.f;

};

END
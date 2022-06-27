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
    virtual void Bind_ConstBuffer() PURE;
    virtual void DrawLight() PURE;
    ID3DXEffect** Get_Effect();

protected:
    ID3DXEffect**   m_ppLightEffect = nullptr;
    D3DLIGHT9       m_D3DLight;
};

END
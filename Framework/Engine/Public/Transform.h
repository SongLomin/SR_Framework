#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CTransform final :
    public CComponent
{
private:
    CTransform() = default;
    CTransform(const CTransform& Prototype);
    virtual ~CTransform() = default;

public:
    _float3 Get_State();

public:
    static CTransform* Create();
    virtual CComponent* Clone(void* Arg);

private:
    _float4x4 m_matWorld;
};

END
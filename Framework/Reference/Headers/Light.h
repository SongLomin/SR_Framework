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
    virtual void DrawLight() PURE;
};

END
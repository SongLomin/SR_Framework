#pragma once
#include "Component.h"

BEGIN(Engine)
class CTransform;

class ENGINE_DLL CCamera final :
    public CComponent
{
private:
    CCamera() = default;
    CCamera(const CCamera & Prototype);
    virtual ~CCamera() = default;

public:
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;

public:
    void Set_Transform(CTransform* _pTransform);

private:
    CTransform* m_pTransfrom = nullptr;
public:
    static CCamera* Create();
    virtual CComponent* Clone(void* pArg) override;
    virtual void Free() override;

};

END
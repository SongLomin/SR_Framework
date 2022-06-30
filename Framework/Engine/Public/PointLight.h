#pragma once
#include "Light.h"

BEGIN(Engine)

class ENGINE_DLL CPointLight :
    public CLight
{
private:
    explicit CPointLight() = default;
    CPointLight(const CPointLight& Prototype);
    virtual ~CPointLight() = default;

public:
    virtual HRESULT Initialize_Prototype();
    virtual HRESULT Initialize(void* pArg);

    // CCollider을(를) 통해 상속됨
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;

    // CLight을(를) 통해 상속됨
    virtual void DrawLight() override;
    // CLight을(를) 통해 상속됨
    virtual void Bind_ConstBuffer() override;

public:
    // CLight을(를) 통해 상속됨
    static CPointLight* Create();
    virtual CComponent* Clone(void* pArg) override;
    virtual void Free() override;

private:
    ID3DXMesh* m_pMesh = nullptr;
};

END
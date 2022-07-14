#pragma once
#include "Collider.h"

BEGIN(Engine)

class ENGINE_DLL CCollider_Ray :
    public CCollider
{
protected:
    explicit CCollider_Ray() = default;
    CCollider_Ray(const CCollider_Ray& Prototype);
    virtual ~CCollider_Ray() = default;

public:
    virtual HRESULT Initialize_Prototype();
    virtual HRESULT Initialize(void* pArg);

    // CCollider을(를) 통해 상속됨
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    HRESULT Debug_Render();

public:
    virtual void Set_Collider_Size(const _float3& _Size) override;

    virtual _float3 Get_Collider_Size() override;

    virtual _float3 Get_Collider_Position() override;

public:
    RAY     Get_ColliderRay();
    

private:
    RAY     m_rayCollider;

public:
    static CCollider_Ray* Create();
    virtual	CComponent* Clone(void* pArg) override;
    virtual void Free() override;



};

END

#pragma once
#include "Collider.h"

BEGIN(Engine)

class ENGINE_DLL CCollider_OBB :
    public CCollider
{
protected:
    explicit CCollider_OBB() = default;
    CCollider_OBB(const CCollider_OBB& Prototype);
    virtual ~CCollider_OBB() = default;

public:
    virtual HRESULT Initialize_Prototype();
    virtual HRESULT Initialize(void* pArg);

    // CCollider을(를) 통해 상속됨
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    HRESULT Debug_Render();

public:
    OBBINFO Get_OBBInfo() const { return m_OBBInfo; };
    // CCollider을(를) 통해 상속됨
    virtual void Set_Collider_Size(const _float3& _Size) override;

    virtual _float3 Get_Collider_Size() override;

    virtual _float3 Get_Collider_Position() override;

private:
    OBBINFO m_OBBInfo;
    
private: /* For Debug Mesh */
    _uint			m_iNumVertices = 0;
    _uint			m_iNumPrimitive = 0;
    _ulong			m_dwFVF;
public:
    static CCollider_OBB* Create();
    virtual	CComponent* Clone(void* pArg) override;
    virtual void Free() override;

    

};

END
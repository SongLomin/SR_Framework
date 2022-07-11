#pragma once
#include "Collider.h"

BEGIN(Engine)
class ENGINE_DLL CCollider_Mesh : public CCollider
{
protected:
    explicit CCollider_Mesh() = default;
    CCollider_Mesh(const CCollider_Mesh& Prototype);
    virtual ~CCollider_Mesh() = default;

public:
    virtual HRESULT Initialize_Prototype();
    virtual HRESULT Initialize(void* pArg);//전달할 때 메쉬 컴포넌트를 전달

    // CCollider을(를) 통해 상속됨
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    HRESULT Debug_Render();

public:
    virtual void Set_Collider_Size(const _float3& _Size) override;

    virtual _float3 Get_Collider_Size() override;

    virtual _float3 Get_Collider_Position() override;

public:
    ID3DXMesh* Get_Collider_Mesh();

private:
    _float3 m_vSize;
    _float3 m_vColliderPosition;

private: /* For Debug Mesh */
    ID3DXMesh* m_pMesh = nullptr;
    _ulong			m_dwFVF;


public:
    static CCollider_Mesh* Create();
    virtual	CComponent* Clone(void* pArg) override;
    virtual void Free() override;

};
END

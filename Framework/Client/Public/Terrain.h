#pragma once
#include "GameObject.h"
#include "Client_Defines.h"

BEGIN(Engine)
class CRenderer;
class CVIBuffer_Terrain;
class CMesh_Terrain;
class CTransform;
END

BEGIN(Client)
class CTerrain final :
    public CGameObject
{
private:
    explicit CTerrain() = default;
    CTerrain(const CTerrain& Prototype);
    virtual ~CTerrain() = default;

public:
    // CGameObject을(를) 통해 상속됨
    virtual HRESULT Initialize_Prototype() override;

    virtual HRESULT Initialize(void* pArg) override;

    virtual void Tick(_float fTimeDelta) override;

    virtual void LateTick(_float fTimeDelta) override;

    virtual HRESULT Render() override;

private:
    CTransform* m_pTransformCom = nullptr;
    CRenderer* m_pRendererCom = nullptr;
    CVIBuffer_Terrain* m_pVIBufferCom = nullptr;
    CMesh_Terrain* m_pMeshCom = nullptr;

public:
    static CTerrain* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;

};

END
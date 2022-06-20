#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CMesh_Cube;
class CRigid_Body;
END

BEGIN(Client)

class CBullet final : public CGameObject
{
private:
    explicit CBullet();
    explicit CBullet(const CBullet& Prototype);
    virtual ~CBullet() = default;

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
    CMesh_Cube* m_pMeshCom = nullptr;
    CRigid_Body* m_pRigidBodyCom = nullptr;

    CTransform* m_pPosinTransformCom = nullptr;

public:
    void Link_PosinTransform(CTransform* pTransform);

private:
    HRESULT SetUp_Components();


public:
    static CBullet* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;
};

END

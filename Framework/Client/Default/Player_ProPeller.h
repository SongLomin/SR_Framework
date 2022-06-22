#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CMesh_Cube;
class CTransform;
class CRigid_Body;
END

BEGIN(Client)

class CPlayer_ProPeller final : public CGameObject
{
private:
    explicit CPlayer_ProPeller();
    explicit CPlayer_ProPeller(const CPlayer_ProPeller& Prototype);
    virtual ~CPlayer_ProPeller() = default;

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

private:
    HRESULT SetUp_Components();

public:
    static CPlayer_ProPeller* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;
};

END


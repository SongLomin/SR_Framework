#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CMesh_Cube;
class CRigid_Body;
class CCollider_OBB;
class CCollider_Pre;
class CSpotLight;
class CMesh_Test;
END

BEGIN(Client)

class CLazer_Bullet final : public CGameObject
{
private:
    explicit CLazer_Bullet();
    explicit CLazer_Bullet(const CLazer_Bullet& Prototype);
    virtual ~CLazer_Bullet() = default;

public:
    // CGameObject을(를) 통해 상속됨
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) override;
    virtual HRESULT Render() override;

private:
    CTransform* m_pTransformCom = nullptr;
    CRenderer* m_pRendererCom = nullptr;
    //CMesh_Cube* m_pMeshCom = nullptr;
    CRigid_Body* m_pRigidBodyCom = nullptr;
    CCollider_OBB* m_pColliderCom = nullptr;
    CCollider_Pre* m_pPreColliderCom = nullptr;
    CSpotLight* m_pLight = nullptr;
    CTransform* m_pPosinTransformCom = nullptr;
    CMesh_Test* m_pMeshCom = nullptr;

private:
    _float  m_fLifeTime = 1.f;

public:
    void Link_PosinTransform(CTransform* _pTransform);

public: /* For Event Function */
    virtual void On_Collision_Enter(CCollider* _Other_Collider) override;
    virtual void On_Collision_Stay(CCollider* _Other_Collider) override;
    virtual void On_Collision_Exit(CCollider* _Other_Collider) override;

private:
    HRESULT SetUp_Components();


public:
    static CLazer_Bullet* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;
};

END

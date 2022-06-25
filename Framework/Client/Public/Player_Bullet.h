#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CMesh_Cube;
class CRigid_Body;
class CCollider_OBB;
END

BEGIN(Client)

class CPlayer_Bullet final : public CGameObject
{
private:
    explicit CPlayer_Bullet();
    explicit CPlayer_Bullet(const CPlayer_Bullet& Prototype);
    virtual ~CPlayer_Bullet() = default;

public:
    // CGameObject��(��) ���� ��ӵ�
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
    CCollider_OBB* m_pColliderCom = nullptr;

    CTransform* m_pPosinTransformCom = nullptr;

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
    static CPlayer_Bullet* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;
};

END

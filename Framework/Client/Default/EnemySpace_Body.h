#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CMesh_Cube;
class CTransform;
class CRigid_Body;
class CState_Move;
class CTargeting;
class CStatus;
class CCollider_OBB;
class CCollider_Pre;
class CTargeting;
class CStatus;
class CCollider_OBB;
END


BEGIN(Client)
class CEnemySpace_Posin;
class CEnemySpace_Body final : public CGameObject
{
private:
    CEnemySpace_Body() = default;
    CEnemySpace_Body(const CEnemySpace_Body& Prototype);
    virtual ~CEnemySpace_Body() = default;

public:
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg)override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render() override;

private:
    CTransform* m_pTransformCom = nullptr;
    CRenderer* m_pRendererCom = nullptr;
    CMesh_Cube* m_pMeshCom = nullptr;
    CTransform* m_pPlayerTransformCom = nullptr;
    CRigid_Body* m_pRigidBodyCom = nullptr;
    CState_Move* m_pStateCom = nullptr;
    CTargeting* m_pTargetingCom = nullptr;
    CStatus* m_pStatusCom = nullptr;
    CCollider_OBB* m_pColliderCom = nullptr;
    CGameObject* m_pTargetObject = nullptr;
    CCollider_Pre* m_pColliderPreCom = nullptr;

private:
    list<CEnemySpace_Posin*> m_pPosinList;
    _float m_fTime = 1.f;

private:
    HRESULT SetUp_Components();
    void Update_Target();


public: /* For Event Function */
    virtual void On_Collision_Enter(CCollider* _Other_Collider) override;
    virtual void On_Collision_Stay(CCollider* _Other_Collider) override;
    virtual void On_Collision_Exit(CCollider* _Other_Collider) override;

public:
    static CEnemySpace_Body* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;

};

END



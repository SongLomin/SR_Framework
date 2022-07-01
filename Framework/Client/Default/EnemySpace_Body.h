#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CMesh_EnemySpace;
class CTransform;
class CRigid_Body;
class CState_Move;
class CTargeting;
class CStatus;
class CCollider_OBB;
class CCollider_Pre;
class CTargeting;
class CAI_Controller;
class CMesh_ShinShip;
END


BEGIN(Client)
class CNormal_Turret;
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
    virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) override;
    virtual HRESULT Render() override;

private: /* For My Component*/
    CTransform* m_pTransformCom = nullptr;
    CRenderer* m_pRendererCom = nullptr;
    CMesh_EnemySpace* m_pMeshCom = nullptr;
    CMesh_ShinShip* m_pMeshCom = nullptr;
    //CMesh_Cube* m_pMeshCom = nullptr;
    CRigid_Body* m_pRigidBodyCom = nullptr;
    CState_Move* m_pStateCom = nullptr;
    CTargeting* m_pTargetingCom = nullptr;
    CStatus* m_pStatusCom = nullptr;
    CCollider_OBB* m_pColliderCom = nullptr;
    CCollider_Pre* m_pColliderPreCom = nullptr;
    CAI_Controller* m_pAIControllerCom = nullptr;
private:
    list<CNormal_Turret*> m_pPosinList;
    _float m_fTime = 1.f;

private:
    HRESULT SetUp_Components();
    void Update_Target();

public:
    virtual void On_Change_Controller(const CONTROLLER& _IsAI);

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



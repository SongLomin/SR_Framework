#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CRigid_Body;
class CState_Move;
class CTargeting;
class CStatus;
class CTargeting;
class CAI_Controller;
class CCollider_Sphere;
END

BEGIN(Client)
class CNormal_Turret;
class CMonster abstract : public CGameObject
{
protected:
    CMonster() = default;
    virtual ~CMonster() = default;

public:
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg)override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) override;
    virtual HRESULT Render() override;

protected: /* For My Component*/
    CTransform* m_pTransformCom = nullptr;
    CRenderer* m_pRendererCom = nullptr;
    CRigid_Body* m_pRigidBodyCom = nullptr;
    CState_Move* m_pStateCom = nullptr;
    CTargeting* m_pTargetingCom = nullptr;
    CStatus* m_pStatusCom = nullptr;
    CCollider_Sphere* m_pColliderCom = nullptr;
    CAI_Controller* m_pAIControllerCom = nullptr;

protected:
    list<CNormal_Turret*> m_pPosinList;
    _float m_fTime = 1.f;

public:
    virtual void On_Change_Controller(const CONTROLLER& _IsAI);

protected:
    HRESULT SetUp_Components();
    virtual void SetUp_Components_For_Child() PURE;

protected
: /* For Event Function */
    virtual void On_Collision_Enter(CCollider* _Other_Collider) override;
    virtual void On_Collision_Stay(CCollider* _Other_Collider) override;
    virtual void On_Collision_Exit(CCollider* _Other_Collider) override;


public:
    virtual void Free() override;

};

END
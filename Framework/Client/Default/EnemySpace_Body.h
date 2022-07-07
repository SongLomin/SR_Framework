#pragma once

#include "Client_Defines.h"
#include "GameObject.h"
#include "Monster.h"

BEGIN(Engine)
class CMesh_EnemySpace;
END


BEGIN(Client)
class CNormal_Turret;
class CEnemySpace_Body final : public CMonster
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
    CMesh_EnemySpace* m_pMeshCom = nullptr;

private:
    HRESULT SetUp_Components();
    virtual void SetUp_Components_For_Child();
    void Update_Target(CGameObject* _Target);

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



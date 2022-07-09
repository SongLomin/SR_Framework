#pragma once

#include "Client_Defines.h"
#include "GameObject.h"
#include "Monster.h"

BEGIN(Engine)
class CMesh_Ship2;
END


BEGIN(Client)
class CNormal_Turret;
class CScouge final : public CMonster
{
private:
    CScouge() = default;
    CScouge(const CScouge& Prototype);
    virtual ~CScouge() = default;

public:
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg)override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) override;
    virtual HRESULT Render() override;

private: /* For My Component*/
    CMesh_Ship2* m_pMeshCom = nullptr;

private:
    void Update_Target(CGameObject* _Target);

protected:
    virtual void SetUp_Components_For_Child();

public:
    virtual void On_Change_Controller(const CONTROLLER& _IsAI);

public: /* For Event Function */
    virtual void On_Collision_Enter(CCollider* _Other_Collider) override;
    virtual void On_Collision_Stay(CCollider* _Other_Collider) override;
    virtual void On_Collision_Exit(CCollider* _Other_Collider) override;

public:
    static CScouge* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;

};

END


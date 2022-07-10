#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
#include "Monster.h"

BEGIN(Engine)
class CVIBuffer_Rect;
END


BEGIN(Client)
class CTaget final : public CMonster
{
private:
    CTaget() = default;
    CTaget(const CTaget& Prototype);
    virtual ~CTaget() = default;

public:
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg)override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) override;
    virtual HRESULT Render() override;

private: /* For My Component*/
    CVIBuffer_Rect* m_pVIBufferCom = nullptr;

private:
    void LookAt_Camera();

protected:
    virtual void SetUp_Components_For_Child();


public:
    virtual void On_Change_Controller(const CONTROLLER& _IsAI);

public: /* For Event Function */
    virtual void On_Collision_Enter(CCollider* _Other_Collider) override;
    virtual void On_Collision_Stay(CCollider* _Other_Collider) override;
    virtual void On_Collision_Exit(CCollider* _Other_Collider) override;

public:
    static CTaget* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;

};

END




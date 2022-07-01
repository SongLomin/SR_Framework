#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CMesh_Cube;
END

BEGIN(Client)

class CNormal_Turret final :public CGameObject
{
private:
    CNormal_Turret() = default;
    CNormal_Turret(const CNormal_Turret& Prototype);
    virtual ~CNormal_Turret() = default;

public:
    // CGameObject을(를) 통해 상속됨
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) override;
    virtual HRESULT Render() override;


public:
    void     Set_Target(CGameObject* _Target);
    _bool    LookAt_Targeting();
    void     LookAt_Aim();

private:
    CTransform* m_pTransformCom = nullptr;
    CRenderer* m_pRendererCom = nullptr;
    CMesh_Cube* m_pMeshCom = nullptr;
    CTransform* m_pPlayerTransformCom = nullptr;

private:
    CGameObject* m_pBoxObject = nullptr;
    CGameObject* m_pTarget = nullptr;

    CGameObject* m_pTargetObject = nullptr;

private:
    _float	 m_fCurTime = 0.f;
    _float	 m_fMaxTime = 1.f;

private:
    HRESULT SetUp_Components();

protected: /* For Event Function */
    virtual void On_Change_Controller(const CONTROLLER& _eController) override;

public:
    // CGameObject을(를) 통해 상속됨
    static CNormal_Turret* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;
};

END

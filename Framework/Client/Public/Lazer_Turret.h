#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CMesh_Cube;
END

BEGIN(Client)

class CLazer_Turret final :public CGameObject
{
private:
    CLazer_Turret() = default;
    CLazer_Turret(const CLazer_Turret& Prototype);
    virtual ~CLazer_Turret() = default;

public:
    // CGameObject을(를) 통해 상속됨
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
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
    _float	 m_fMaxTime = 10.f;

private:
    HRESULT SetUp_Components();

public:
    // CGameObject을(를) 통해 상속됨
    static CLazer_Turret* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;
};

END


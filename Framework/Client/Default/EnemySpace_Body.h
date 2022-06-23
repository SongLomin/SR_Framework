#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CMesh_Cube;
class CTransform;
class CRigid_Body;
class CState;
END


BEGIN(Client)

class CEnemySpace_Body final : public CGameObject
{
private:
    enum STATE { MOVEMENT, MOVEMENT_1, MOVEMENT_2, MOVEMENT_3, MOVEMENT_4, MOVEMENT_5, MOVEMENT_END };
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
    CState*      m_pStateCom = nullptr;

private:
    _float	 m_fCountTime = 0.f;
    STATE    m_ePreMovement = MOVEMENT_END;
    STATE    m_eCurMovement = MOVEMENT_END;
    bool     m_bMoveMentCheck = false;

private:
    HRESULT SetUp_Components();

private:
    void    MoveMent(_float fTimeDelta);
    void    MoveMent1(_float fTimeDelta);
    void    MoveMent2(_float fTimeDelta);
    void    MoveMent3(_float fTimeDelta);
    void    MoveMent4(_float fTimeDelta);
    void    MoveMent5(_float fTimeDelta);
    void    MoveMentChange(_float fTimeDelta);

public:
    static CEnemySpace_Body* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;

};

END



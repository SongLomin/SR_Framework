#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CMesh_Cube;
class CTransform;
class CRigid_Body;
class CState_Move;
END


BEGIN(Client)

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
    Engine::CState_Move* m_pStateCom = nullptr;



private:
    HRESULT SetUp_Components();

public:
    static CEnemySpace_Body* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;

};

END



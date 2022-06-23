#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CMesh_Cube;
END

BEGIN(Client)

class CEnemySpace_Posin final :public CGameObject
{
private:
    CEnemySpace_Posin() = default;
    CEnemySpace_Posin(const CEnemySpace_Posin& Prototype);
    virtual ~CEnemySpace_Posin() = default;

public:
    // CGameObject을(를) 통해 상속됨
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render() override;

private:
    CTransform* m_pTransformCom = nullptr;
    CRenderer* m_pRendererCom = nullptr;
    CMesh_Cube* m_pMeshCom = nullptr;
    CTransform* m_pPlayerTransformCom = nullptr;

private:
    HRESULT SetUp_Components();
    void LookAt_Player();

public:
    // CGameObject을(를) 통해 상속됨
    static CEnemySpace_Posin* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;
};

END

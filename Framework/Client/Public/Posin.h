#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CMesh_Cube;
class CTransform;
class CTargetting;
END

BEGIN(Client)

class CPosin final : public CGameObject
{
private:
    explicit CPosin();
    explicit CPosin(const CPosin& Prototype);
    virtual ~CPosin() = default;

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
    CTargetting* m_pTargettingCom = nullptr;

private:
    HRESULT SetUp_Components();
    void    LookAt_Targetting();

public:
    static CPosin* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;
};

END



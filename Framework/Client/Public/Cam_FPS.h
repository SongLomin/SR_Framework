#pragma once

#include "GameObject.h"
#include "Client_Defines.h"

BEGIN(Engine)
class CTransform;
class CCamera;
class CRigid_Body;
END

BEGIN(Client)

class CCam_FPS final : public CGameObject
{
private:
    explicit CCam_FPS() = default;
    CCam_FPS(const CCam_FPS& Prototype);
    virtual ~CCam_FPS() = default;

public:
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render() override;


private:
    CTransform* m_pTransformCom = nullptr;
    CCamera* m_pCameraCom = nullptr;
    CRigid_Body* m_pRigidBodyCom = nullptr;


public:
    static CCam_FPS* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;
};

END
#pragma once
#include "GameObject.h"
#include "Client_Defines.h"

BEGIN(Engine)
class CTransform;
class CCamera;
END

BEGIN(Client)
class CCam_Free :
    public CGameObject
{
private:
    explicit CCam_Free() = default;
    CCam_Free(const CCam_Free& Prototype);
    virtual ~CCam_Free() = default;

public:
    // CGameObject을(를) 통해 상속됨
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render() override;

private:
    CTransform* m_pTransformCom = nullptr;
    CCamera* m_pCameraCom = nullptr;

public:
    static CCam_Free* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;

};

END

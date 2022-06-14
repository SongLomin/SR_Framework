#pragma once
#include "GameObject.h"
#include "Client_Defines.h"

BEGIN(Engine)
class CTransform;
class CCamera;
END

BEGIN(Client)
class CCameraObject :
    public CGameObject
{
private:
    explicit CCameraObject() = default;
    CCameraObject(const CCameraObject& Prototype);
    virtual ~CCameraObject() = default;

public:
    // CGameObject을(를) 통해 상속됨
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render() override;
    virtual CGameObject* Clone(void* pArg) override;

private:
    CTransform* m_pTransformCom = nullptr;
    CCamera* m_pCameraCom = nullptr;

public:
    static CCameraObject* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;

};

END

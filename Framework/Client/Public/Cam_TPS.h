#pragma once
#include "GameObject.h"
#include "Client_Defines.h"

BEGIN(Engine)
class CTransform;
class CCamera;
END

BEGIN(Client)
class CCam_TPS :
    public CGameObject
{
private:
    explicit CCam_TPS() = default;
    CCam_TPS(const CCam_TPS& Prototype);
    virtual ~CCam_TPS() = default;

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

    _float3 m_CurCursorPosition;
    _float3 m_PreCursorPosition;
    _float3 m_MouseRealPosition;

public:
    static CCam_TPS* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;

};
END

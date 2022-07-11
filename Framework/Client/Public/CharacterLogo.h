#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CCharacterLogo final : public CGameObject
{
private:
    explicit CCharacterLogo() = default;
    explicit CCharacterLogo(const CCharacterLogo& Prototype);
    virtual ~CCharacterLogo() = default;

public:
    // CGameObject을(를) 통해 상속됨
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render() override;

private:
    _float					m_fX, m_fY, m_fSizeX, m_fSizeY;
    _point					m_ptMouse;
    _float4x4				m_ProjMatrix;
    RECT					m_rcRect;


private:
    CTransform* m_pTransformCom = nullptr;
    CRenderer* m_pRendererCom = nullptr;
    CVIBuffer_Rect* m_pVIBufferCom = nullptr;

private:
    HRESULT SetUp_Components();

public:
    static CCharacterLogo* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;
};


END


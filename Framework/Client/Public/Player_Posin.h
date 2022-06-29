#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CMesh_Cube;
class CTransform;
END

BEGIN(Client)

class CPlayer_Posin final : public CGameObject
{
private:
    explicit CPlayer_Posin();
    explicit CPlayer_Posin(const CPlayer_Posin& Prototype);
    virtual ~CPlayer_Posin() = default;

public:
    // CGameObject을(를) 통해 상속됨
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render() override;
    virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) override;

public:
    void    Set_Target(CGameObject* _Target);

private:
    CTransform* m_pTransformCom = nullptr;
    CRenderer* m_pRendererCom = nullptr;
    CMesh_Cube* m_pMeshCom = nullptr;

    _float m_fTime = 0.f;

private:
    CGameObject* m_pBoxObject = nullptr;
    CGameObject* m_pTarget = nullptr;

private:
    HRESULT SetUp_Components();
    _bool    LookAt_Targeting();
    void    LookAt_Aim();

public:
    static CPlayer_Posin* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;
};

END



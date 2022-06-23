#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CMesh_Cube;
END

BEGIN(Client)

class CPlayer_RightBody final :
    public CGameObject
{
private:
    CPlayer_RightBody() = default;
    CPlayer_RightBody(const CPlayer_RightBody& Prototype);
    virtual ~CPlayer_RightBody() = default;

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

public:
    // CGameObject을(를) 통해 상속됨
    static CPlayer_RightBody* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;
};

END
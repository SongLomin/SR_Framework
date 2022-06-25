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
    // CGameObject��(��) ���� ��ӵ�
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render() override;

private:
    CTransform* m_pTransformCom = nullptr;
    CRenderer* m_pRendererCom = nullptr;
    CMesh_Cube* m_pMeshCom = nullptr;

    _float m_fTime = 0.f;

private:
    CGameObject* m_pBoxObject = nullptr;

private:
    HRESULT SetUp_Components();
    void    LookAt_Targeting();

public:
    static CPlayer_Posin* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;
};

END



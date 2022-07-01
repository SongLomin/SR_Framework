#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
BEGIN(Engine)
class CRenderer;
class CTransform;
class CMesh_Cube;
class CRigid_Body;
class CCollider_Shpere;
class CSpotLight;
class CPointLight;
END

BEGIN(Client)

class CBullet final : public CGameObject
{
private:
    explicit CBullet();
    explicit CBullet(const CBullet& Prototype);
    virtual ~CBullet() = default;

public:
    // CGameObject을(를) 통해 상속됨
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) override;
    virtual HRESULT Render() override;

private:
    CTransform* m_pTransformCom = nullptr;
    CRenderer* m_pRendererCom = nullptr;
    CMesh_Cube* m_pMeshCom = nullptr;
    CRigid_Body* m_pRigidBodyCom = nullptr;
    CCollider_Shpere* m_pColliderCom = nullptr;
    CPointLight* m_pLight = nullptr;

    CTransform* m_pPosinTransformCom = nullptr;

private:
    _float  m_fLifeTime = 1.f;

public:
    void Link_PosinTransform(CTransform* _pTransform);

public:
    virtual void Free() override;
};

END

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

class CBullet abstract : public CGameObject
{
protected:
    explicit CBullet();
    virtual ~CBullet() = default;

public:
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;

protected:
    CTransform* m_pTransformCom = nullptr;
    CRenderer* m_pRendererCom = nullptr;
    CRigid_Body* m_pRigidBodyCom = nullptr;
    CCollider_Shpere* m_pColliderCom = nullptr;

protected:
    _float  m_fLifeTime = 1.f;

protected:
    HRESULT SetUp_Components(COLLISION_TYPE _eCollisionType);
    virtual HRESULT SetUp_Components_For_Child() PURE;

public:
    void Init_BulletPosition(_float4x4* _pWorldMat);

public:
    virtual void Free() override;
};

END

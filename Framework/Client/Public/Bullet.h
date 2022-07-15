#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
BEGIN(Engine)
class CRenderer;
class CTransform;
class CMesh_Cube;
class CRigid_Body;
class CCollider_Sphere;
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
   

protected:
    _float  m_fLifeTime = 1.f;
    _float  m_fMaxTime = 1.f;
    _float  m_fDamage = 1.f;

protected:
    HRESULT SetUp_Components(COLLISION_TYPE _eCollisionType);
    virtual HRESULT SetUp_Components_For_Child(COLLISION_TYPE _eCollisionType) PURE;

public:
    virtual void Init_BulletPosition(_float4x4* _pWorldMat);

    _float Get_Damage() { return m_fDamage; }

public:
    //객체의 상태가 활성화 상태로 변경될 때, 호출되는 이벤트입니다.
    virtual void OnEnable(void* _Arg = nullptr) override;

    //객체의 상태가 비활성화 상태로 변경될 때, 호출되는 이벤트입니다.
    virtual void OnDisable() override;

public:
    virtual void Free() override;
};

END

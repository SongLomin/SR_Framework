#pragma once

#include "Client_Defines.h"
#include "Bullet.h"

BEGIN(Engine)
class CMesh_Cube;
class CSpotLight;
class CPointLight;
END

BEGIN(Client)

class CNormal_Bullet final : public CBullet
{
private:
    explicit CNormal_Bullet();
    explicit CNormal_Bullet(const CNormal_Bullet& Prototype);
    virtual ~CNormal_Bullet() = default;

public:
    // CGameObject을(를) 통해 상속됨
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) override;
    virtual HRESULT Render() override;

    virtual void Init_BulletPosition(_float4x4* _pWorldMat) override;

private:
    CMesh_Cube* m_pMeshCom = nullptr;
    CPointLight* m_pLight = nullptr;

private:
    _bool       m_bFirst = true;

public:
    //void Link_PosinTransform(CTransform* _pTransform);

public: /* For Event Function */
    virtual void On_Collision_Enter(CCollider* _Other_Collider) override;
    virtual void On_Collision_Stay(CCollider* _Other_Collider) override;
    virtual void On_Collision_Exit(CCollider* _Other_Collider) override;

public:
    //객체의 상태가 활성화 상태로 변경될 때, 호출되는 이벤트입니다.
    virtual void OnEnable(void* _Arg = nullptr) override;

    //객체의 상태가 비활성화 상태로 변경될 때, 호출되는 이벤트입니다.
    virtual void OnDisable() override;

protected:
    // CBullet을(를) 통해 상속됨
    virtual HRESULT SetUp_Components_For_Child() override;

public:
    static CNormal_Bullet* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;

    
};

END

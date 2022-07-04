#pragma once

#include "Client_Defines.h"
#include "Bullet.h"

BEGIN(Engine)
class CMesh_Cube;
class CSpotLight;
class CMesh_Test;
END

BEGIN(Client)

class CRoket_Bullet final : public CBullet
{
private:
    explicit CRoket_Bullet();
    explicit CRoket_Bullet(const CRoket_Bullet& Prototype);
    virtual ~CRoket_Bullet() = default;

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
    CSpotLight* m_pLight = nullptr;
    CMesh_Test* m_pMeshCom = nullptr;



public: /* For Event Function */
    virtual void On_Collision_Enter(CCollider* _Other_Collider) override;
    virtual void On_Collision_Stay(CCollider* _Other_Collider) override;
    virtual void On_Collision_Exit(CCollider* _Other_Collider) override;

protected:
    // CBullet을(를) 통해 상속됨
    virtual HRESULT SetUp_Components_For_Child() override;


public:
    static CRoket_Bullet* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;

    
};

END

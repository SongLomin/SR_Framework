#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CMesh_Cube;
class CTransform;
class CCollider_OBB;
END

BEGIN(Client)

class CMonster final :
    public CGameObject
{
private:
    CMonster() = default;
    CMonster(const CMonster& Prototype);
    virtual ~CMonster() = default;

public:
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg)override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render() override;

private:
    CTransform* m_pTransformCom = nullptr;
    CRenderer* m_pRendererCom = nullptr;
    CMesh_Cube* m_pMeshCom = nullptr;
    CCollider_OBB* m_pCColliderCom = nullptr;

private:
    CTransform* m_pPlayerTransformCom = nullptr;

private: /* ���� ��ü���� �ʿ��� ������Ʈ�� �����ؿ´�. */
    HRESULT SetUp_Components();

public: /* For Event Function */
    virtual void On_Collision_Enter(CCollider* _Other_Collider) override;
    virtual void On_Collision_Stay(CCollider* _Other_Collider) override;
    virtual void On_Collision_Exit(CCollider* _Other_Collider) override;


public:
    static CMonster* Create();
    
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;

    // CGameObject��(��) ���� ��ӵ�
    
    //virtual CGameObject* Clone(void* pArg) override;
};

END
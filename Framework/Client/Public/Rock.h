#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
class CRigid_Body;
class CCollider_Sphere;
END

BEGIN(Client)

class CRock final : public CGameObject
{
private:
	CRock();
	CRock(const CRock& Prototype);
	virtual ~CRock() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	CRenderer* m_pRendererCom = nullptr;
	CTransform* m_pTransformCom = nullptr;
	CVIBuffer_Rect* m_pVIBufferCom = nullptr;
	CRigid_Body* m_pRigidBodyCom = nullptr;
	CCollider_Sphere* m_pColliderCom = nullptr;
private:
	HRESULT SetUp_Components();
	void LookAtCamera();

public: /* For Event Function */
	virtual void On_Collision_Enter(CCollider* _Other_Collider);
	virtual void On_Collision_Stay(CCollider* _Other_Collider);
	virtual void On_Collision_Exit(CCollider* _Other_Collider);

public:
	static CRock* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END

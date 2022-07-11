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

class CRock abstract : public CGameObject
{
protected:
	CRock();
	CRock(const CRock& Prototype);
	virtual ~CRock() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

protected:
	CRenderer* m_pRendererCom = nullptr;
	CTransform* m_pTransformCom = nullptr;
	CVIBuffer_Rect* m_pVIBufferCom = nullptr;
	CRigid_Body* m_pRigidBodyCom = nullptr;
	CCollider_Sphere* m_pColliderCom = nullptr;

protected:
	HRESULT SetUp_Components();
	virtual void SetUp_Components_For_Chiled() = 0;
	void LookAtCamera();

protected: /* For Event Function */
	virtual void On_Collision_Enter(CCollider* _Other_Collider) override;
	virtual void On_Collision_Stay(CCollider* _Other_Collider) override;
	virtual void On_Collision_Exit(CCollider* _Other_Collider) override;

public:
	virtual void Free() override;
};

END

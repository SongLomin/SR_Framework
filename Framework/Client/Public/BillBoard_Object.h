#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
class CRigid_Body;
class CCollider_Sphere;
class CAI_Controller;
END

BEGIN(Client)

class CBillboard_Object abstract : public CGameObject
{
protected:
	CBillboard_Object();
	CBillboard_Object(const CBillboard_Object& Prototype);
	virtual ~CBillboard_Object() = default;

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
	CAI_Controller* m_pAIControllerCom = nullptr;
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

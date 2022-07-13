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

class CSatellite_3 final : public CGameObject
{
private:
	CSatellite_3();
	CSatellite_3(const CSatellite_3& Prototype);
	virtual ~CSatellite_3() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;


public: /* For Event Function */
	virtual void On_Collision_Enter(CCollider* _Other_Collider) override;
	virtual void On_Collision_Stay(CCollider* _Other_Collider) override;
	virtual void On_Collision_Exit(CCollider* _Other_Collider) override;

private:
	CRenderer* m_pRendererCom = nullptr;
	CTransform* m_pTransformCom = nullptr;
	CVIBuffer_Rect* m_pVIBufferCom = nullptr;
	CRigid_Body* m_pRigidBodyCom = nullptr;
	CCollider_Sphere* m_pColliderCom = nullptr;

private:
	HRESULT SetUp_Components();
	void LookAt_Camera();

public:
	static CSatellite_3* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END
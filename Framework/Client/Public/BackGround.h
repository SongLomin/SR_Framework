#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CVIBuffer_Rect;
class CTransform;
class CStatus;
class CMesh_Cube;
class CRigid_Body;
class CCollider_OBB;
class CTargeting;
END

BEGIN(Client)
class CCameraPosin;
class CPlayer_Body final : public CGameObject
{
private:
	CPlayer_Body();
	CPlayer_Body(const CPlayer_Body& Prototype);
	virtual ~CPlayer_Body() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg)override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	void Set_Targetting();

private:
	CTransform*				m_pTransformCom = nullptr;
	CRenderer*				m_pRendererCom = nullptr;
	CMesh_Cube*				m_pMeshCubeCom = nullptr;
	CStatus*				m_pStatusCom = nullptr;
	CRigid_Body*			m_pRigidBodyCom = nullptr;
	CTargeting*			m_pTargetingCom = nullptr;

private:
	CCameraPosin*           m_pCameraPosin = nullptr;
	static const _tchar*	m_pTag;

	_uint					m_iCurrentCam = 0;

protected: /* For Event Function */
	virtual void On_Change_Controller(const CONTROLLER& _IsAI) override;

public: /* For Event Function */
	virtual void On_Collision_Enter(CCollider* _Other_Collider) override;
	virtual void On_Collision_Stay(CCollider* _Other_Collider) override;
	virtual void On_Collision_Exit(CCollider* _Other_Collider) override;

private: /* 현재 객체에게 필요한 컴포넌트를 복제해온다. */
	HRESULT SetUp_Components();

public:
	static CPlayer_Body* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END
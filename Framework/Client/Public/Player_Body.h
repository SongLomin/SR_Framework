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
class CTargeting;
class CMesh_SongShip;
class CCollider_OBB;
class CCollider_Pre;
END

BEGIN(Client)

class CPlayer_Posin;
class CHpBar;

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
	virtual HRESULT Render_Begin() override;
	virtual HRESULT Render() override;

private:
	CTransform*				m_pTransformCom = nullptr;
	CRenderer*				m_pRendererCom = nullptr;
	CMesh_SongShip*			m_pMeshCubeCom = nullptr;
	CStatus*				m_pStatusCom = nullptr;
	CRigid_Body*			m_pRigidBodyCom = nullptr;
	CCollider_OBB*			m_pColliderCom = nullptr;
	CTargeting*				m_pTargetingCom = nullptr;
	CCollider_Pre*			m_pPreColliderCom = nullptr;

private:
	list<CPlayer_Posin*>	m_pMyPosinList;
	CHpBar*                 m_pHpBar;

private:

	_uint					m_iCurrentCam = 0;
	_bool					m_bMouse = false;
	_float					m_fTime = 1.f;

	_bool					m_bTargetMode = false;

protected: /* For Event Function */
	virtual void On_Change_Controller(const CONTROLLER& _IsAI) override;

public: /* For Event Function */
	virtual void On_Collision_Enter(CCollider* _Other_Collider) override;
	virtual void On_Collision_Stay(CCollider* _Other_Collider) override;
	virtual void On_Collision_Exit(CCollider* _Other_Collider) override;

private: /* 현재 객체에게 필요한 컴포넌트를 복제해온다. */
	HRESULT SetUp_Components();
	void Update_PosinTarget();

public:
	static CPlayer_Body* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END
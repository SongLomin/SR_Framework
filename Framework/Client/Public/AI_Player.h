#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
BEGIN(Engine)
class CRenderer;
class CTransform;
class CCollider_OBB;
class CRigid_Body;
class CTargeting;
class CStatus;
class CMesh_Cube;
class CCollider_Pre;
class CState_Move;
END

BEGIN(Client)
class CEnemySpace_Posin;

class CAI_Player final : public CGameObject
{
private:
	CAI_Player();
	CAI_Player(const CAI_Player& Prototype);
	virtual ~CAI_Player() = default;


public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render_Begin() override;
	virtual HRESULT Render() override;



private:
	CRenderer* m_pRendererCom = nullptr;
	CTransform* m_pTransformCom = nullptr;
	CCollider_OBB* m_pColliderCom = nullptr;
	CRigid_Body* m_pRigidBodyCom = nullptr;
	CTargeting* m_pTargetingCom = nullptr;
	CStatus* m_pStatusCom = nullptr;
	CMesh_Cube* m_pMeshCom = nullptr;
	CCollider_Pre* m_pPreColliderCom = nullptr;
	CState_Move* m_pStateCom = nullptr;



private:
	list<CEnemySpace_Posin*>	m_pMyPosinList;
	_bool					m_bTargetMode = false;
	_float					m_fTime = 1.f;


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
	static CAI_Player* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END
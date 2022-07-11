#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
BEGIN(Engine)
class CRenderer;
class CTransform;
class CCollider_Sphere;
class CRigid_Body;
class CTargeting;
class CStatus;
class CMesh_Cube;
class CState_Move;
class CAI_Controller;
class CPlayer_Controller;
class CMesh_ShinShip;
class CMesh_KangShip;
END

BEGIN(Client)
class CNormal_Turret;

class CAI_Friendly final : public CGameObject
{
private:
	CAI_Friendly();
	CAI_Friendly(const CAI_Friendly& Prototype);
	virtual ~CAI_Friendly() = default;


public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) override;
	virtual HRESULT Render() override;



private:
	CRenderer* m_pRendererCom = nullptr;
	CTransform* m_pTransformCom = nullptr;
	CCollider_Sphere* m_pColliderCom = nullptr;
	CRigid_Body* m_pRigidBodyCom = nullptr;
	CTargeting* m_pTargetingCom = nullptr;
	CStatus* m_pStatusCom = nullptr;
	CMesh_KangShip* m_pMeshCom = nullptr;
	CState_Move* m_pStateCom = nullptr;
	CAI_Controller* m_pAIControllerCom = nullptr;
	CPlayer_Controller* m_pPlayerController = nullptr;


private:
	list<CNormal_Turret*>	m_pMyPosinList;
	_bool					m_bTargetMode = false;
	_float					m_fTime = 1.f;


protected: /* For Event Function */
	virtual void On_Change_Controller(const CONTROLLER& _IsAI) override;

public: /* For Event Function */
	virtual void On_Collision_Enter(CCollider* _Other_Collider) override;
	virtual void On_Collision_Stay(CCollider* _Other_Collider) override;
	virtual void On_Collision_Exit(CCollider* _Other_Collider) override;

	//객체의 상태가 활성화 상태로 변경될 때, 호출되는 이벤트입니다.
	virtual void OnEnable(void* _Arg = nullptr) override;
	//객체의 상태가 비활성화 상태로 변경될 때, 호출되는 이벤트입니다.
	virtual void OnDisable() override;


private: /* 현재 객체에게 필요한 컴포넌트를 복제해온다. */
	HRESULT SetUp_Components();
	void Update_PosinTarget(CGameObject* _Target);




public:
	static CAI_Friendly* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END
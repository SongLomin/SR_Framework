#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
BEGIN(Engine)
class CRenderer;
class CTransform;
class CAI_Controller;
class CPlayer_Controller;
class CRigid_Body;
class CTargeting;
class CStatus;
class CState_Move;
class CCollider_Sphere;
class CDirectionalLight;
END

BEGIN(Client)

class CTurret;
class CCameraPosin;
class CPlayer_Posin;

class CPlayer abstract : public CGameObject
{
protected:
	CPlayer();
	virtual ~CPlayer() = default;


public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg)override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) override;
	virtual HRESULT Render() override;


protected:
	CRenderer* m_pRendererCom = nullptr;
	CTransform* m_pTransformCom = nullptr;
	CAI_Controller* m_pAI_ControllerCom = nullptr;
	CPlayer_Controller* m_pPlayer_ControllerCom = nullptr;
	CRigid_Body* m_pRigid_BodyCom = nullptr;
	CTargeting* m_pTargetingCom = nullptr;
	CStatus* m_pStatusCom = nullptr;
	CState_Move* m_pStateCom = nullptr;
	CCollider_Sphere* m_pColliderCom = nullptr;

protected:
	list<CTurret*>	m_pMyPosinList;
	_bool					m_bTargetMode = false;
	_float					m_fTime = 1.f;
	_bool					m_bMouse = false;

protected: /* For Event Function */
	virtual void On_Change_Controller(const CONTROLLER& _IsAI) override;

public: /* For Event Function */
	virtual void On_Collision_Enter(CCollider* _Other_Collider) override;
	virtual void On_Collision_Stay(CCollider* _Other_Collider) override;
	virtual void On_Collision_Exit(CCollider* _Other_Collider) override;

protected:
	HRESULT SetUp_Components();
	virtual void SetUp_Components_For_Child() PURE;
	virtual void Update_PosinTarget(TARGETMODE _TargetMode);

public:
	virtual void Free() override;
};

END
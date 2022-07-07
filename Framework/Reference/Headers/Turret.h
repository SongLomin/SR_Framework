#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CTransform;
class CRenderer;
class CMesh_Cube;

END


BEGIN(Client)
class CTurret : public CGameObject
{
protected:
	CTurret() = default;
	virtual ~CTurret() = default;

protected:
	virtual HRESULT Initialize_Prototype() final;
	virtual HRESULT Initialize(void* pArg) PURE;
	virtual void	Tick(_float fTimeDelta) final;
	virtual void	LateTick(_float fTiemDelta) final;
	virtual HRESULT	Render() final;

private:
    /*SetUp_Component*/
    CTransform* m_pTransformCom = nullptr;
    CRenderer* m_pRendererCom = nullptr;

    CMesh_Cube* m_pMeshCom = nullptr;
    CTransform* m_pPlayerTransformCom = nullptr;

private:
    CGameObject* m_pBoxObject = nullptr;
    CGameObject* m_pTarget = nullptr;//Rocket bullet을 만들 때 넘겨주기

    COLLISION_TYPE m_eBulletCollisionType = COLLISION_TYPE::PLAYER_ATTACK;

private:
    _float	 m_fCurTime = 0.f;
    _float	 m_fMaxTime = 0.1f;

protected:
    HRESULT SetUp_Components();
    virtual void SetUp_Component_For_Child()PURE;
    void    SetUp_Variables_For_Child();

protected:
    virtual void On_Change_Controller(const CONTROLLER& _eController) override;
    virtual void On_EventMessage(void* _Arg) override;

public:
    virtual void Free() override;

};

END
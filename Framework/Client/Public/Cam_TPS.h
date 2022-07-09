#pragma once
#include "GameObject.h"
#include "Client_Defines.h"

BEGIN(Engine)
class CTransform;
class CCamera;
class CRigid_Body;
END

BEGIN(Client)
class CCam_TPS :
    public CGameObject
{
private:
    explicit CCam_TPS() = default;
    CCam_TPS(const CCam_TPS& Prototype);
    virtual ~CCam_TPS() = default;

public:
    // CGameObject을(를) 통해 상속됨
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render() override;

private:
    CTransform* m_pTransformCom = nullptr;
    CCamera* m_pCameraCom = nullptr;
	CRigid_Body*	m_pRigidBodyCom = nullptr;

	_float3		m_vCurPos;
	POINT		m_ptPrePos{};

	_float		m_fSpeedX =0.f;
	_float		m_fSpeedY = 0.f;

	_float		m_fAccelX=0.f;
	_float		m_fAccelY=0.f;

private:
    _float      m_fMovement=0.f;
    _float      m_fCurTime = -1.f;
    _float      m_fLerpTime = 0.016;

public:
    static CCam_TPS* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;

};
END

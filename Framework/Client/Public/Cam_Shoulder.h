#pragma once
#include "GameObject.h"
#include "Client_Defines.h"

BEGIN(Engine)
class CTransform;
class CCamera;
class CRigid_Body;
END

BEGIN(Client)

class CCam_Shoulder final : public CGameObject
{
private:
	explicit CCam_Shoulder() = default;
	CCam_Shoulder(const CCam_Shoulder& Prototype);
	virtual ~CCam_Shoulder() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	CTransform* m_pTransformCom = nullptr;
	CCamera* m_pCameraCom = nullptr;
	CRigid_Body* m_pRogidBodyCom = nullptr;

	_float m_fAngle = 65.f;

public:
	static CCam_Shoulder* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END
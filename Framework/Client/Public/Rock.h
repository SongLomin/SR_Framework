#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
class CRigid_Body;
END

BEGIN(Client)

class CRock final : public CGameObject
{
private:
	CRock();
	CRock(const CRock& Prototype);
	virtual ~CRock() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	CRenderer* m_pRendererCom = nullptr;
	CTransform* m_pTransformCom = nullptr;
	CVIBuffer_Rect* m_pVIBufferCom = nullptr;
	CRigid_Body* m_pRigidBodyCom = nullptr;

private:
	HRESULT SetUp_Components();
	void LookAtCamera();

public:
	static CRock* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END

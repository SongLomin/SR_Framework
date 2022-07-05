#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
class CPointLight;
class CSpotLight;
class CDirectionalLight;
END

BEGIN(Client)

class CLight_Moon final : public CGameObject
{
public:
	CLight_Moon();
	CLight_Moon(const CLight_Moon& Prototype);
	virtual ~CLight_Moon() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	CRenderer* m_pRendererCom = nullptr;
	CTransform* m_pTransformCom = nullptr;
	CVIBuffer_Rect* m_pVIBufferCom = nullptr;
	CDirectionalLight* m_pDirectionalLightCom = nullptr;



private:
	HRESULT SetUp_Components();
	void LookAtCamera();

public:
	static CLight_Moon* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END



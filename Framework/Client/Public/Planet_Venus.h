#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
class CDirectionalLight;
class CPointLight;
class CSpotLight;
END

BEGIN(Client)

class CPlanet_Venus final : public CGameObject
{
public:
	CPlanet_Venus();
	CPlanet_Venus(const CPlanet_Venus& Prototype);
	virtual ~CPlanet_Venus() = default;

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
	CPointLight* m_pPointLightCom = nullptr;
	


private:
	HRESULT SetUp_Components();
	void LookAtCamera();

private:
	_bool m_bLevelChange = false;

public:
	static CPlanet_Venus* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END

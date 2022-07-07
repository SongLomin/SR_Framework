#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CPlanet_Red final : public CGameObject
{
public:
	CPlanet_Red();
	CPlanet_Red(const CPlanet_Red& Prototype);
	virtual ~CPlanet_Red() = default;

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

private:
	HRESULT SetUp_Components();
	void LookAtCamera();
	void Enter_Planet();

private:
	_bool m_bLevelChange = false;

public:
	static CPlanet_Red* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END

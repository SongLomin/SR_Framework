#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CPlanet_Sun final : public CGameObject
{
public:
	CPlanet_Sun();
	CPlanet_Sun(const CPlanet_Sun& Prototype);
	virtual ~CPlanet_Sun() = default;

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

public:
	static CPlanet_Sun* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END


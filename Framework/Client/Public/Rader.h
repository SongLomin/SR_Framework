#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CRader final : public CGameObject
{
private:
	CRader();
	CRader(const CRader& Prototype);
	virtual ~CRader() = default;

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

	CTransform* m_pCameraTransform = nullptr;


private:
	_float					m_fX, m_fY, m_fSizeX, m_fSizeY;
	_float4x4				m_ProjMatrix;
	RECT					m_rcRader;

	_float	m_fComputeTime = 2.f;

private:
	HRESULT SetUp_Components();

private:
	void Compute_Distance();


public:
	static CRader* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END
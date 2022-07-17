#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
END


BEGIN(Client)

class CHealth_UI final : public CGameObject
{
public:
	CHealth_UI() = default;
	CHealth_UI(const CHealth_UI& Prototype);
	virtual ~CHealth_UI() = default;

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

	_int					m_iIndex = 0;

private:
	_float					m_fX, m_fY, m_fSizeX, m_fSizeY;
	_point					m_ptMouse;
	_float4x4				m_ProjMatrix;
	RECT					m_rcRect;
	_bool                   m_bSwitchTaget = false;

private:
	HRESULT SetUp_Components();

public:
	static CHealth_UI* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END
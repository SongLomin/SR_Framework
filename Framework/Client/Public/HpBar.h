#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
class CStatus
END


BEGIN(Client)

class CHpBar final : public CGameObject
{
public:
	CHpBar() = default;
	CHpBar(const CHpBar& Prototype);
	virtual ~CHpBar() = default;

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
	CStatus* m_pStatusCom = nullptr;

private:
	_float					m_fX, m_fY, m_fSizeX, m_fSizeY;
	_point					m_ptMouse;
	_float4x4				m_ProjMatrix;
	RECT					m_rcRect;

public:
	void UpdateHpBar(_float _beforeHp, _float _afterHp);

private:
	HRESULT SetUp_Components();

public:
	static CHpBar* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END


#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
END


BEGIN(Client)

class CBulletCountUI final : public CGameObject
{
public:
	CBulletCountUI() = default;
	CBulletCountUI(const CBulletCountUI& Prototype);
	virtual ~CBulletCountUI() = default;

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

private:
	_float					m_fX, m_fY, m_fSizeX, m_fSizeY;
	_point					m_ptMouse;
	_float4x4				m_ProjMatrix;
	RECT					m_rcRect;

private:
	HRESULT SetUp_Components();

public:
	static CBulletCountUI* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END

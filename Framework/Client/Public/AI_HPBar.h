#pragma once
#include "GameObject.h"
#include "Client_Defines.h"
BEGIN(Engine)
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
class CStatus;
END


BEGIN(Client)

class CAI_HPBar final : public CGameObject
{
public:
	CAI_HPBar() = default;
	CAI_HPBar(const CAI_HPBar& Prototype);
	virtual ~CAI_HPBar() = default;

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

protected:
	_float					m_fX, m_fY, m_fSizeX, m_fSizeY;
	_point					m_ptMouse;
	_float4x4				m_ProjMatrix;
	RECT					m_rcRect;

public:
	void Update_Hp_Bar(CStatus* pStatus);


private:
	HRESULT SetUp_Components();

public:
	static CAI_HPBar* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END
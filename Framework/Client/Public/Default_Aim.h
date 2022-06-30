#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CDefault_Aim final : public CGameObject
{
private:
	CDefault_Aim();
	CDefault_Aim(const CDefault_Aim& Prototype);
	virtual ~CDefault_Aim() = default;


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
	_float4x4				m_ProjMatrix;
	_point					m_ptMouse;
	RECT					m_rcAim;


private:
	HRESULT SetUp_Components();

public:
	static CDefault_Aim* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END
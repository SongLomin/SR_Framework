#pragma once
#include "UI.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
END


BEGIN(Client)

class CTextureDrawUI final : public CGameObject
{
private:
	CTextureDrawUI() = default;
	CTextureDrawUI(const CTextureDrawUI& Prototype);
	virtual ~CTextureDrawUI() = default;

protected:
	virtual HRESULT Initialize_Prototype() final;
	virtual HRESULT Initialize(void* pArg) override;

	virtual void Tick(_float fTimeDelta) final;
	virtual void LateTick(_float fTimeDelta) final;
	virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) final;
	virtual HRESULT Render() final;

public:
	void Set_Option(_float2 _UI_Position, _float2 _UI_Size, RENDERGROUP _eRenderGroup);

private:
	virtual void SetUp_Components();

private:
	CRenderer* m_pRendererCom = nullptr;
	CTransform* m_pTransformCom = nullptr;
	CVIBuffer_Rect* m_pVIBufferCom = nullptr;

private:
	_float	m_fX, m_fY, m_fSizeX, m_fSizeY;
	_float4x4 m_ProjMatrix;
	RENDERGROUP m_eRenderGroup = RENDERGROUP::RENDER_SPECULAR;

public:
	static CTextureDrawUI* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END

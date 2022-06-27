#pragma once

#include "Base.h"

BEGIN(Engine)


class CGraphic_Device final : public CBase
{
	DECLARE_SINGLETON(CGraphic_Device)

private:
	CGraphic_Device();
	virtual ~CGraphic_Device() = default;
	// com 객체 : 언어와의 통신 규약을 갖고 하드웨어를 통제하여 각종 기능을 제공하는 객체

public:
	LPDIRECT3DDEVICE9*			Get_Device(void) { return &m_pDevice; }
public:
	HRESULT		InitDevice(const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut);	
	void		Render_Begin(void);
	void		Render_End(HWND hWnd = NULL);

public:
	HRESULT		Add_Text(TEXTINFO Info, float CountTime);
	D3DLIGHT9	InitLight(D3DLIGHTTYPE type);
	bool SetupEffect(const _tchar* shaderFilename, ID3DXEffect** effect);
	bool SetupTexture(IDirect3DTexture9** texture, IDirect3DSurface9** surface);

public:


private:
	LPDIRECT3D9				m_p3D;
	LPDIRECT3DDEVICE9		m_pDevice;

	LPD3DXFONT				m_pFont = nullptr;

	list<class CFont*>			m_Text;

	ID3DXSprite*			m_pSprite = nullptr;

	GRAPHICDESC				m_GraphicDesc;

private: /* For Light */
	
	
public: /* For Defferred Rendering */
	IDirect3DSurface9* originRenderTarget = 0;

	IDirect3DTexture9* normalTex = 0;
	IDirect3DSurface9* normalSurface = 0;

	IDirect3DTexture9* depthTex = 0;
	IDirect3DSurface9* depthSurface = 0;

	IDirect3DTexture9* diffuseTex = 0;
	IDirect3DSurface9* diffuseSurface = 0;

	IDirect3DTexture9* specularTex = 0;
	IDirect3DSurface9* specularSurface = 0;


private:
	void		SetParameters(const GRAPHICDESC& GraphicDesc, D3DPRESENT_PARAMETERS& d3dpp);

public:
	virtual void Free();
};

END
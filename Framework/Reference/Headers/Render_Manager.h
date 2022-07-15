#pragma once
#include "Base.h"


BEGIN(Engine)

class CRender_Manager final : public CBase
{
	DECLARE_SINGLETON(CRender_Manager)
public:

	CRender_Manager();
	virtual ~CRender_Manager() = default;

public:
	HRESULT Initialize();

	HRESULT Add_RenderGroup(RENDERGROUP	eGroup, class CGameObject* pGameObject);
	HRESULT Add_Light(class CLight* pLight);
	
	HRESULT Draw_RenderGroup();

	void	Add_BlurWidth()
	{
		
		fBlurWidth += 0.001f;
		if(fBlurWidth > 0.1f)
			fBlurWidth = 0.1f;
	}

	void	Reset_BlurWidth()
	{
		fBlurWidth = 0.f;
	}

private:
	list<class CGameObject*>				m_RenderObjects[(_uint)RENDERGROUP::RENDER_END];
	typedef list<class CGameObject*>		RENDEROBJECTS;

	list<class CLight*>						m_LightComs;

private:
	void Priority_Pipeline();
	void Deferred_Pipeline();
	void Foward_Pipeline();

	void Bloom_Pipeline();

	bool SetupTexture(IDirect3DTexture9** texture, IDirect3DSurface9** surface);
	void SetMRT();
	void ResumeOriginRender();
	void DrawScreenQuad();
	void Draw_Divide_ViewPort(RENDERGROUP _eRenderGroup, IDirect3DTexture9* _Tex);
	void Apply_Blur(RENDERGROUP _eRenderGroup, IDirect3DTexture9* _Tex);
	void Apply_Bloom(RENDERGROUP _eRenderGroup);
	void Apply_BoosterBlur(RENDERGROUP _eRenderGroup, IDirect3DTexture9* _Tex);
	void Set_OnlyRenderTarget(IDirect3DSurface9** _ppSurface);

private: /* For Defferred Rendering */
	IDirect3DSurface9* originRenderTarget = nullptr;
	IDirect3DTexture9* originTex = nullptr;

	IDirect3DSurface9* TemporaryRenderTarget = nullptr;

	IDirect3DTexture9* normalTex = nullptr;
	IDirect3DSurface9* normalSurface = nullptr;

	IDirect3DTexture9* depthTex = nullptr;
	IDirect3DSurface9* depthSurface = nullptr;

	IDirect3DTexture9* diffuseTex = nullptr;
	IDirect3DSurface9* diffuseSurface = nullptr;

	IDirect3DTexture9* specularTex = nullptr;
	IDirect3DSurface9* specularSurface = nullptr;

	IDirect3DTexture9* stashTex = nullptr;
	IDirect3DSurface9* stashSurface = nullptr;

	IDirect3DTexture9* ExtractBloomTex = nullptr;
	IDirect3DSurface9* ExtractBloomSurface = nullptr;

	IDirect3DTexture9* BloomTex = nullptr;
	IDirect3DSurface9* BloomSurface = nullptr;

	IDirect3DVertexBuffer9* vb = nullptr;

private:
	_float	fBlurWidth = 0.f;
	GRAPHICDESC m_GraphicDesc;

public:
	virtual void Free() override;
};

END

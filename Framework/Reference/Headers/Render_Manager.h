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

private:
	list<class CGameObject*>				m_RenderObjects[(_uint)RENDERGROUP::RENDER_END];
	typedef list<class CGameObject*>		RENDEROBJECTS;

	list<class CLight*>						m_LightComs;

private:
	void Priority_Pipeline();
	void Deferred_Pipeline();
	void Foward_Pipeline();
	void Apply_BoosterBlur();

	bool SetupTexture(IDirect3DTexture9** texture, IDirect3DSurface9** surface);
	void SetMRT();
	void ResumeOriginRender();
	void DrawScreenQuad();

	void SetUpScreenRect();


private: /* For Defferred Rendering */
	IDirect3DSurface9* originRenderTarget = nullptr;
	IDirect3DTexture9* originTex = nullptr;

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

	IDirect3DVertexBuffer9* vb = nullptr;

private:


public:
	virtual void Free() override;
};

END

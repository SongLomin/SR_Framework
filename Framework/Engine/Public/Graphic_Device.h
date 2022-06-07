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

private:
	LPDIRECT3D9				m_p3D;
	LPDIRECT3DDEVICE9		m_pDevice;

private:
	void		SetParameters(const GRAPHICDESC& GraphicDesc, D3DPRESENT_PARAMETERS& d3dpp);

public:
	virtual void Free();
};

END
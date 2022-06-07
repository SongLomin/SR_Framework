#pragma once

namespace Engine
{
	typedef struct tagVertex_Texture
	{
		D3DXVECTOR3		vPosition;
		D3DXVECTOR2		vTexUV;
	}VTXTEX;


	typedef struct tagGraphicDesc
	{
		unsigned int iWinCX, iWinCY; 
		HWND	hWnd;
		bool	isWindowMode;
	}GRAPHICDESC;

	enum class RENDERGROUP { RENDER_PRIORITY = 0, RENDER_NONALPHABLEND, RENDER_ALPHABLEND, RENDER_UI, RENDER_END };
}

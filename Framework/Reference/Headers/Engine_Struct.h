#pragma once

namespace Engine
{
	typedef struct tagLineIndices32 //4바이트
	{
		unsigned long _1, _2;
	}LINEINDICES32;

	typedef struct tagLineIndices16 //2바이트
	{
		unsigned short _1, _2;
	}LINEINDICES16;

	typedef struct tagFaceIndices32 //4바이트
	{
		unsigned long _1, _2, _3;
	}FACEINDICES32;

	typedef struct tagFaceIndices16 //2바이트
	{
		unsigned short _1, _2, _3;
	}FACEINDICES16;

	/*
	인덱스들은 참조할 버텍스의 인덱스 크기에 따라서 2바이트를 쓸지 4바이트를 쓸지가 다르다.
	예를 들어 참조할 버텍스 번호가 크다면 short보다 long이 적합할 것이다.
	*/

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
	enum class TEXTURE_TYPE { TYPE_DEFAULT = 0, TYPE_CUBE, TYPE_END };
	enum class MEMORY_TYPE { MEMORY_STATIC = 0, MEMORY_DYNAMIC, MEMORY_END };

}

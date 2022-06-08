#pragma once

namespace Engine
{
	typedef struct tagLineIndices32 //4����Ʈ
	{
		unsigned long _1, _2;
	}LINEINDICES32;

	typedef struct tagLineIndices16 //2����Ʈ
	{
		unsigned short _1, _2;
	}LINEINDICES16;

	typedef struct tagFaceIndices32 //4����Ʈ
	{
		unsigned long _1, _2, _3;
	}FACEINDICES32;

	typedef struct tagFaceIndices16 //2����Ʈ
	{
		unsigned short _1, _2, _3;
	}FACEINDICES16;

	/*
	�ε������� ������ ���ؽ��� �ε��� ũ�⿡ ���� 2����Ʈ�� ���� 4����Ʈ�� ������ �ٸ���.
	���� ��� ������ ���ؽ� ��ȣ�� ũ�ٸ� short���� long�� ������ ���̴�.
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

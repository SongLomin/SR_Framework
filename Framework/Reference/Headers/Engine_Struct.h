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

		tagVertex_Texture(const D3DXVECTOR3& _Pos, const D3DXVECTOR2& _Tex)
		{
			vPosition = _Pos;
			vTexUV = _Tex;
		}

		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
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
	enum class KEY_STATE {
		TAP, // �� ���� ����
		HOLD,// �� ������ ����
		AWAY,// �� �� ����
		NONE,// �� �ȴ��� ����
	};
	enum class KEY
	{
		LEFT = 0,
		RIGHT,
		UP,
		DOWN,
		NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9, NUM0,
		F1, F2, F3, F4,
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		ALT,
		LSHIFT,
		SPACE,
		CTRL,
		ENTER,
		ESC,
		TAB,
		LBUTTON,
		RBUTTON,
		BACKSPACE,
		DELETEKEY,
		LAST,
	};

	enum class MOUSEBUTTON { MBS_LBUTTON = 0, MBS_RBUTTON, MBS_WHEEL, MBS_X, MBS_END };
	enum class MOUSEMOVE { MMS_X = 0, MMS_Y, MMS_WHEEL, MMS_END };

}

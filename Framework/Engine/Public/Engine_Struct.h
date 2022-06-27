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

	typedef struct tagVertex_CubeTexture
	{
		D3DXVECTOR3		vPosition;
		D3DXVECTOR3		vTexUV;

		tagVertex_CubeTexture(const D3DXVECTOR3& _Pos, const D3DXVECTOR3& _Tex)
		{
			vPosition = _Pos;
			vTexUV = _Tex;
		}

		static const DWORD SKY = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);
	}VTXCUBETEX;

	typedef struct tagVertex_Color
	{
		D3DXVECTOR3		vPosition;
		D3DXVECTOR3		vNorm;
		D3DCOLOR		DColor;

		tagVertex_Color(const D3DXVECTOR3& _Pos, const D3DXVECTOR3& _Norm, const D3DCOLOR& _Color)
		{
			vPosition = _Pos;
			vNorm = _Norm;
			DColor = _Color;
		}

		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE;
	}VTXCOLOR;


	typedef struct tagGraphicDesc
	{
		unsigned int iWinCX, iWinCY;
		HWND	hWnd;
		bool	isWindowMode;
	}GRAPHICDESC;

	typedef struct tagTextInfo
	{
		RECT rcTemp;
		_tchar szBuff[MAX_PATH] = L"";
		D3DXCOLOR color;
	}TEXTINFO;

	typedef struct tagRay
	{
		D3DXVECTOR3 Dir;
		D3DXVECTOR3 Pos;
		float		fLength;

	}RAY;

	typedef struct tagOBBBoxInfo
	{
		//OBB�ڽ��� ����(������Ʈ�� �� ����� �Ǿ�� ��)
		D3DXVECTOR3 ObbCenterPos;

		// �� ��� ������ ���ؽ��� ����
		D3DXVECTOR3 ObbSize;

		// �� ���ؽ����� ������� ��ǥ
		D3DXVECTOR3 tVertex[8];

		//���� ��
		D3DXVECTOR3 LocalAxis[3];

		//�������� ��ĺ�ȯ�� ���� ���� ��������� �� = 6���� ���� ��ġ�� �ʴ� 3�鿡 ���� ��������
		D3DXVECTOR3 WorldAxis[3];

		tagOBBBoxInfo()
		{
			ObbCenterPos = { 0, 0, 0 };
			ObbSize = { 0, 0, 0 };
			LocalAxis[0] = { 1, 0, 0 };
			LocalAxis[1] = { 0, 1, 0 };
			LocalAxis[2] = { 0, 0, 1 };
		}

		tagOBBBoxInfo(D3DXVECTOR3& size)
		{
			ObbSize = size;
			LocalAxis[0] = { 1, 0, 0 };
			LocalAxis[1] = { 0, 1, 0 };
			LocalAxis[2] = { 0, 0, 1 };
		}

		void SetSize(const D3DXVECTOR3& size)
		{
			ObbSize = size;


			tVertex[0] = { 0 - (ObbSize.x), 0 + (ObbSize.y), 0 - (ObbSize.z) };
			tVertex[1] = { 0 + (ObbSize.x), 0 + (ObbSize.y), 0 - (ObbSize.z) };
			tVertex[2] = { 0 + (ObbSize.x), 0 - (ObbSize.y), 0 - (ObbSize.z) };
			tVertex[3] = { 0 - (ObbSize.x), 0 - (ObbSize.y), 0 - (ObbSize.z) };

			//4-7 -> z < 0, �ð�(�� ������ �ݽð�)
			tVertex[4] = { 0 - (ObbSize.x), 0 + (ObbSize.y), 0 + (ObbSize.z) };
			tVertex[5] = { 0 + (ObbSize.x), 0 + (ObbSize.y), 0 + (ObbSize.z) };
			tVertex[6] = { 0 + (ObbSize.x), 0 - (ObbSize.y), 0 + (ObbSize.z) };
			tVertex[7] = { 0 - (ObbSize.x), 0 - (ObbSize.y), 0 + (ObbSize.z) };
		}

		void SetMatrix(D3DXMATRIX* pmatWorld)
		{
			ObbCenterPos.x = pmatWorld->_41;
			ObbCenterPos.y = pmatWorld->_42;
			ObbCenterPos.z = pmatWorld->_43;

			for (int i = 0; i < 3; ++i)
			{
				WorldAxis[i] = LocalAxis[i];
				D3DXVec3TransformNormal(&WorldAxis[i], &WorldAxis[i], pmatWorld);
			}

			tVertex[0] = { 0 - (ObbSize.x), 0 + (ObbSize.y), 0 - (ObbSize.z) };
			tVertex[1] = { 0 + (ObbSize.x), 0 + (ObbSize.y), 0 - (ObbSize.z) };
			tVertex[2] = { 0 + (ObbSize.x), 0 - (ObbSize.y), 0 - (ObbSize.z) };
			tVertex[3] = { 0 - (ObbSize.x), 0 - (ObbSize.y), 0 - (ObbSize.z) };

			//4-7 -> z < 0, �ð�(�� ������ �ݽð�)
			tVertex[4] = { 0 - (ObbSize.x), 0 + (ObbSize.y), 0 + (ObbSize.z) };
			tVertex[5] = { 0 + (ObbSize.x), 0 + (ObbSize.y), 0 + (ObbSize.z) };
			tVertex[6] = { 0 + (ObbSize.x), 0 - (ObbSize.y), 0 + (ObbSize.z) };
			tVertex[7] = { 0 - (ObbSize.x), 0 - (ObbSize.y), 0 + (ObbSize.z) };

			//���� ���� 8�� ����ȭ
			for (int i = 0; i < 8; ++i)
			{
				D3DXVec3TransformCoord(&tVertex[i], &tVertex[i], pmatWorld);
			}
		}

	}OBBINFO;

	union COLLIDER_ID
	{
		struct
		{
			UINT Left_id;
			UINT Right_id;
		};
		ULONGLONG ID;

	};


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

	enum class CONTROLLER { PLAYER = 0, AI, CONTROLLER_END };

	enum class MATRIX_STATE { RIGHT, UP, LOOK, POSITION, STATE_END };

	enum class COLLISION_TYPE
	{
		DEFAULT = 0,
		PLAYER,
		PLAYER_ATTACK,
		MONSTER,
		MONSTER_ATTACK,
		EFFECTS,
		SIGHT,
		RANGE,
		CAMERA,
		MOUSE,
		TYPE_END
	};

	enum class COLLIDER_SHAPE
	{
		SPHERE = 0,
		OBB,
		SHAPE_END
	};

	enum class STATE_MOVE 
	{ 
		MOVE_UPPER_LEFT, 
		MOVE_DOWN_FRONT, 
		MOVE_LIFT_FRONT, 
		MOVE_LIFT_BACK, 
		MOVE_JUMP_FRONT, 
		MOVE_UPPER_RIGHT,
		STATE_END
	};


	enum class STATE_MOVETARGET
	{
		MOVETARGET_CHASE,
		MOVETARGET_RSPIN,
		MOVETARGET_LSPIN,
		MOVETARGET_BACK,
		MOVETARGET_END
	};


	enum class STATE
	{
		STATE_MOVE,
		STATE_ATTACK,
		STATE_DEAD,
		STATE_END
	};

}



	














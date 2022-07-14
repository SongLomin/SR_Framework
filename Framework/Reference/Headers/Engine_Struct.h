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
	typedef struct tagVertex_XYZ
	{
		float		x, y, z;

		tagVertex_XYZ(const D3DXVECTOR3& _Pos)
		{
			x = _Pos.x;
			y = _Pos.y;
			z = _Pos.z;
		}

		tagVertex_XYZ(const float& _x, const float& _y, const float& _z)
		{
			x = _x;
			y = _y;
			z = _z;
		}

		static const DWORD FVF = D3DFVF_XYZ;
	}VTX;


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

	typedef struct tagVertex_OnlyColor
	{
		D3DXVECTOR3		vPosition;
		D3DCOLOR		DColor;

		tagVertex_OnlyColor(const D3DXVECTOR3& _Pos, const D3DCOLOR& _Color)
		{
			vPosition = _Pos;
			DColor = _Color;
		}

		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	}VTXONLYCOLOR;

	typedef struct tagVertex_Default
	{
		D3DXVECTOR3		vPosition;
		D3DXVECTOR3		vNorm;
		D3DXVECTOR2		vUV;

		tagVertex_Default(const D3DXVECTOR3& _Pos, const D3DXVECTOR3& _Norm, const D3DXVECTOR2& _vUV)
		{
			vPosition = _Pos;
			vNorm = _Norm;
			vUV = _vUV;
		}

		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
	}VTXDEFAULT;

	typedef struct tagVertex_Sub
	{
		D3DXVECTOR3		vPosition;
		D3DXVECTOR3		vNorm;

		tagVertex_Sub(const D3DXVECTOR3& _Pos, const D3DXVECTOR3& _Norm)
		{
			vPosition = _Pos;
			vNorm = _Norm;
		}

		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL ;
	}VTXSUB;

	typedef struct tagVertex_Normal
	{
		D3DXVECTOR3		vPosition;
		D3DXVECTOR3		vNorm;


		tagVertex_Normal(const D3DXVECTOR3& _Pos, const D3DXVECTOR3& _Norm)
		{
			vPosition = _Pos;
			vNorm = _Norm;

		}

		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL;
	}VTXNORMAL;

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
		//OBB박스의 중점(오브젝트의 정 가운데가 되어야 함)
		D3DXVECTOR3 ObbCenterPos;

		// 각 축과 평행한 버텍스의 길이
		D3DXVECTOR3 ObbSize;

		// 각 버텍스들의 월드상의 좌표
		D3DXVECTOR3 tVertex[8];

		//로컬 축
		D3DXVECTOR3 LocalAxis[3];

		//로컬축을 행렬변환에 맞춰 만든 월드기준의 축 = 6개의 면중 겹치지 않는 3면에 대한 법선벡터
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

			//4-7 -> z < 0, 시계(축 반전시 반시계)
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

			//4-7 -> z < 0, 시계(축 반전시 반시계)
			tVertex[4] = { 0 - (ObbSize.x), 0 + (ObbSize.y), 0 + (ObbSize.z) };
			tVertex[5] = { 0 + (ObbSize.x), 0 + (ObbSize.y), 0 + (ObbSize.z) };
			tVertex[6] = { 0 + (ObbSize.x), 0 - (ObbSize.y), 0 + (ObbSize.z) };
			tVertex[7] = { 0 - (ObbSize.x), 0 - (ObbSize.y), 0 + (ObbSize.z) };

			//로컬 정점 8개 월드화
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
			unsigned long Left_id;
			unsigned long Right_id;
		};
		unsigned long long  ID;

	};

	/*struct COLLIDER_ID
	{
		unsigned long Left_id;
		unsigned long Right_id;
		unsigned long long  ID;
	};*/


	enum class RENDERGROUP 
	{ 
		RENDER_PRIORITY = 0, 
		RENDER_DEFERRED, 
		RENDER_NONALPHABLEND, 
		RENDER_ALPHABLEND, 
		RENDER_UNDER_UI, 
		RENDER_UI, 
		RENDER_NORMAL, 
		RENDER_DEPTH,
		RENDER_DIFFUSE,
		RENDER_SPECULAR,
		RENDER_POSTPROCCESSING,
		RENDER_END 
	};

	enum class TEXTURE_TYPE { TYPE_DEFAULT = 0, TYPE_CUBE, TYPE_END };
	enum class MEMORY_TYPE { MEMORY_STATIC = 0, MEMORY_DYNAMIC, MEMORY_END };

	enum class RIGID_BODY { ACCEL=0, SPEED};

	enum class KEY_STATE {
		TAP, // 막 누른 시점
		HOLD,// 꾹 누르고 있음
		AWAY,// 막 뗀 시점
		NONE,// 걍 안눌린 상태
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

	enum class CONTROLLER { PLAYER = 0, AI, LOCK, CONTROLLER_END };
	enum class TARGETMODE { TARGET_SINGLE, TARGET_MULTIRAY, TARGET_MULTIWIDE, TARGET_END};

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
		OBJECT,
		TYPE_END
	};

	enum class COLLIDER_SHAPE
	{
		SPHERE = 0,
		OBB,
		MESH,
		SHAPE_END
	};


	// 각 행동 종류 분류는 100단위다. 즉, 행동 종류마다 최대 100개까지 정의할 수 있다.
	// 최대 행동 종류는 900번대까지 쓸 수 있다. (컨트롤러에서 늘릴 수 있음)
	enum class STATE
	{ 
		STATE_NONE = 0,
		MOVE_UPPER_LEFT, 
		MOVE_DOWN_FRONT, 
		MOVE_LIFT_FRONT, 
		MOVE_LIFT_BACK, 
		MOVE_JUMP_FRONT, 
		MOVE_UPPER_RIGHT,
		MOVE_FORWARD,
		MOVETARGET_CHASE = 100,
		MOVETAGET_CHASE_PLAYER,
		MOVETARGET_RSPIN,
		MOVETARGET_LSPIN,
		MOVETARGET_BACK,
		ATTACK_TAP = 200, //Fire를 한 번만 호출하고, 정해진 시간동안 대기
		ATTACK_HOLD, //정해진 시간동안 계속 Fire를 호출
		STATE_END
	};
	enum class MOVE_UI_DIR
	{
		MOVE_UI_RIGHT = 0,
		MOVE_UI_LEFT,
		MOVE_UI_UP,
		MOVE_UI_DOWN,
		MOVE_UI_END
	};

	enum class GPS_TYPE
	{
		GPS_FRIENDLY = 0,
		GPS_ENEMY,
		GPS_END
	};
}



	














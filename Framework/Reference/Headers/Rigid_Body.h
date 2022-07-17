#pragma once

#include "Component.h"

BEGIN(Engine)

class CTransform;

class ENGINE_DLL CRigid_Body final : public CComponent
{
public:
	enum Func { LEFT,RIGHT,FRONT,BACK,LIFT,DOWN,SPIN,BOOSTER};
	enum State{ STATE_RIGHT,STATE_UP, STATE_LOOK,STATE_POSITION	};


	typedef struct tagRigidbodyDesc
	{
		_float		m_fOwnerSpeed; // 앞뒤 움직임 속도
		_float		m_fOwnerAccel; // 앞뒤 움직임 가속도
		_float		m_fOwnerRadSpeed;
		_float		m_fOwnerRadAccel;

		_float		m_fOwnerLiftSpeed;
		_float		m_fOwnerLiftAccel;

		_float		m_fOwnerJump;
		_float		m_fOwnerJumpScale;

		_float		m_fFrictional;
		_float		m_fRadFrictional;

		_float		m_fRadZ;

		_float		m_fRadDrag;
		_float		m_fDirDrag;


		_float		m_fBoosterSpeed; // 앞뒤 움직임 속도
		_float		m_fBoosterAccel; // 앞뒤 움직임 가속도

		void Set_Preset_EnemySpace_Body()
		{
			m_fOwnerSpeed = 30.f;
			m_fOwnerAccel = 0.5f;
			m_fOwnerRadSpeed = D3DXToRadian(90.0f);
			m_fOwnerRadAccel = 0.3f;
			m_fOwnerJump = 5.f;
			m_fOwnerJumpScale = 1.f;

			m_fFrictional = 0.05f;
			m_fRadFrictional = 0.02f;
			m_fRadZ = 0.01f;


			m_fOwnerLiftSpeed = 10.f;
			m_fOwnerLiftAccel = 0.3f;
			m_fRadDrag = 1.f;
			m_fDirDrag = 0.05f;
			m_fOwnerAccel = 0.1f;
		}

		void Set_Preset_MagmaSpace_Body()
		{
			m_fOwnerSpeed = 10.f;
			m_fOwnerAccel = 0.3f;
			m_fOwnerRadSpeed = D3DXToRadian(90.0f);
			m_fOwnerRadAccel = 0.3f;
			m_fOwnerJump = 5.f;
			m_fOwnerJumpScale = 1.f;

			m_fFrictional = 0.05f;
			m_fRadFrictional = 0.02f;
			m_fRadZ = 0.01f;


			m_fOwnerLiftSpeed = 10.f;
			m_fOwnerLiftAccel = 0.3f;
			m_fRadDrag = 1.f;
			m_fDirDrag = 0.05f;
		}

		void Set_Preset_StagBeetle()
		{
			m_fOwnerSpeed = 50.f;
			m_fOwnerAccel = 30.f;
			m_fOwnerRadSpeed = D3DXToRadian(90.0f);
			m_fOwnerRadAccel = 0.3f;
			m_fOwnerJump = 5.f;
			m_fOwnerJumpScale = 1.f;

			m_fFrictional = 0.05f;
			m_fRadFrictional = 0.02f;
			m_fRadZ = 0.01f;


			m_fOwnerLiftSpeed = 10.f;
			m_fOwnerLiftAccel = 0.3f;
			m_fRadDrag = 1.f;
			m_fDirDrag = 0.05f;
		}

		void Set_Preset_Boss_Body()
		{
			m_fOwnerSpeed = 0.f;
			m_fOwnerAccel = 0.f;
			m_fOwnerRadSpeed = D3DXToRadian(90.0f);
			m_fOwnerRadAccel = 0.f;
			m_fOwnerJump = 0.f;
			m_fOwnerJumpScale = 0.f;

			m_fFrictional = 0.0f;
			m_fRadFrictional = 0.0f;
			m_fRadZ = 0.0f;


			m_fOwnerLiftSpeed = 0.f;
			m_fOwnerLiftAccel = 0.f;
			m_fRadDrag = 0.f;
			m_fDirDrag = 0.0f;
		}

		void Set_Preset_Scourge()
		{
			m_fOwnerSpeed = 50.f;
			m_fOwnerAccel = 10.f;
			m_fOwnerRadSpeed = D3DXToRadian(90.0f);
			m_fOwnerRadAccel = 0.3f;
			m_fOwnerJump = 5.f;
			m_fOwnerJumpScale = 1.f;

			m_fFrictional = 0.05f;
			m_fRadFrictional = 0.02f;
			m_fRadZ = 0.01f;

			m_fOwnerLiftSpeed = 100.f;
			m_fOwnerLiftAccel = 10.f;
			m_fRadDrag = 1.f;
			m_fDirDrag = 0.05f;
			m_fBoosterSpeed = 100.f;
			m_fBoosterAccel = 1.f;
		}

		void Set_Preset_Kang_Ship()
		{
			m_fOwnerSpeed = 30.f;
			m_fOwnerAccel = 0.5f;
			m_fOwnerRadSpeed = D3DXToRadian(90.0f);
			m_fOwnerRadAccel = 0.3f;
			m_fOwnerJump = 5.f;
			m_fOwnerJumpScale = 1.f;

			m_fFrictional = 0.1f;
			m_fRadFrictional = 0.02f;
			m_fRadZ = 0.01f;


			m_fOwnerLiftSpeed = 20.f;
			m_fOwnerLiftAccel = 0.3f;
			m_fRadDrag = 1.f;
			m_fDirDrag = 0.05f;

			m_fBoosterSpeed = 60.f;
			m_fBoosterAccel = 6.f;
		}

	}RIGIDBODYDESC;

private:
	CRigid_Body();
	CRigid_Body(const CRigid_Body& Prototype);
	virtual ~CRigid_Body() = default;

	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	virtual HRESULT		Initialize_Prototype();
	virtual HRESULT		Initialize(void* pArg);
	void	Link_TransformCom(CTransform* _pTransform);

public:


	void		Set_Camera(_bool _bCamera)
	{
		m_bCamera = _bCamera;
	}

	void		Set_Mouse(_bool _bMouse)
	{
		m_bMouse = _bMouse;
	}

	void		Set_Booster(_bool _bBooster)
	{
		m_bBooster = _bBooster;
	}

	void		Add_Dir(Func Dir, _float fDir =0.f);
	void		Add_Camera(Func Dir, _float fDir = 0.f);
	void		Add_Force(_float3 fDir);
	
	void		Update_Transform(_float fTimeDelta);
	void		SetUp_Origin_DirVector();
	void		Set_DirVector();

	void		Reset_Force();

	_float3		Get_Vector(RIGID_BODY	eType);
	RIGIDBODYDESC Get_RigidDesc()
	{
		return m_RigidbodyDesc;
	}

private:

	void		Compute_Force(_float fTimeDelta);
	void		Compute_Camera();

	void		Compute_Dir(_float fTimeDelta);
	void		Compute_Rotation();

	void		Compute_RotDirection();//비행기 회전용
	void		Compute_Lift();

	void		Friction(_float fTimeDelta);//마찰력

	void		Compute_Ground();

	

	void		Move(_float fTimeDelta);
	void		Turn(_float fTimeDelta);
	void		SubTurn();
		
public:
	void Set_Direction(State eState, _float3 _Vec3)
	{
		switch (eState)
		{
		case STATE_RIGHT:
			m_vRight = _Vec3;
			break;
		case STATE_UP:
			m_vUp = _Vec3;
			break;

		case STATE_LOOK:
			m_vLook = _Vec3;
			break;

		case STATE_POSITION:
			m_vPos = _Vec3;
			break;

		}
	}
	_float3 Get_Direction(State eState)
	{
		switch (eState)
		{
		case STATE_RIGHT:
			return m_vRight;
			
		case STATE_UP:
			return m_vUp ;
			
		case STATE_LOOK:
			return m_vLook;
			
		case STATE_POSITION:
			return m_vPos;
			
		}

		return _float3(0.f, 0.f, 0.f);
	}

	_bool Get_Booster()
	{
		return m_bBooster;
	}
	
private:
	CTransform*		m_pTransform;
	_bool			m_bFirst = true;

	_bool		m_bBooster = false;

	_bool		m_bLift = true;
	_bool		m_bMouse = false;
	_bool		m_bCamera = false;

private:
	RIGIDBODYDESC	m_RigidbodyDesc;

	_float3		m_vLook;
	_float3		m_vUp;
	_float3		m_vRight;
	_float3		m_vScale;

	_float3		m_vPos;

	_float3		m_vSubLook;
	_float3		m_vSubUp;
	_float3		m_vSubRight;

	_float3		m_vSpeed;
	_float3		m_vAccel;
	_float		m_fJump;//점프할 때 이용

	_float		m_fRadAccelY = 0;//Y축 기준, <-이동 회전에 이용될 애
	_float		m_fRadSpeedY = 0;

	_float		m_fRadAccelX = 0;//X와 Z는 연출용에만 이용
	_float		m_fRadSpeedX = 0;

	_float		m_fRadAccelZ = 0;
	_float		m_fRadSpeedZ = 0;

	_float		m_fLiftAccel = 0;
	_float		m_fLiftSpeed = 0;

	_float		m_fTimeCount = 2.f;



public:
	static CRigid_Body*		Create();
	virtual CComponent*		Clone(void* pArg) override;
	virtual void Free() override;
};

END
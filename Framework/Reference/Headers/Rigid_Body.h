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
	//이동용 실질적인 이동용

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
	//실질적인건 아닌데 연출용
	
	void		Update_Transform(_float fTimeDelta);
	void		Set_DirVector();
private:
	void		Compute_Force();
	void		Compute_Camera();

	void		Compute_Dir();
	void		Compute_Rotation();

	void		Compute_RotDirection();//비행기 회전용
	void		Compute_Lift();

	void		Friction();//마찰력

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
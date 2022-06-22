#pragma once

#include "Component.h"

BEGIN(Engine)

class CTransform;

class ENGINE_DLL CRigid_Body final : public CComponent
{
public:
	enum Func { LEFT,RIGHT,FRONT,BACK,JUMP,LIFT };

	typedef struct tagRigidbodyDesc
	{
		_float		m_fOwnerSpeed;
		_float		m_fOwnerAccel;
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
	}RIGIDBODYDESC;

private:
	CRigid_Body();
	CRigid_Body(const CRigid_Body& Prototype);
	virtual ~CRigid_Body() = default;

public:
	virtual HRESULT		Initialize_Prototype();
	virtual HRESULT		Initialize(void* pArg);
	void	Link_TransformCom(CTransform* _pTransform);

public:
	void		Add_Dir(Func Dir, _float fDir =0.f);

	void		Update_Transform(_float fTimeDelta);

private:
	void		Compute_Force();

	void		Compute_Dir();
	void		Compute_Rotation();

	void		Compute_RotDirection();//비행기 회전용
	void		Compute_Lift();

	void		Compute_Jump();
	void		Friction();//마찰력

	void		Compute_Ground();

	

	void		Move(_float fTimeDelta);
	void		Turn(_float fTimeDelta);
	void		SubTurn();
		

	
private:
	CTransform*		m_pTransform;

private:
	RIGIDBODYDESC	m_RigidbodyDesc;

	_float3		m_vLook;
	_float3		m_vUp;
	_float3		m_vRight;

	_float3		m_vPos;

	_float3		m_vSubLook;
	_float3		m_vSubUp;
	_float3		m_vSubRight;

	_float3		m_vSpeed;
	_float3		m_vAccel;
	_float		m_fJump;//점프할 때 이용

	_float		m_fRadAccelY = 0;//Y축 기준, 
	_float		m_fRadSpeedY = 0;

	_float		m_fRadAccelX = 0;
	_float		m_fRadSpeedX = 0;

	_float		m_fRadAccelZ = 0;
	_float		m_fRadSpeedZ = 0;

	_bool		m_bJump = false;
	_bool		m_bLift = false;



	_float		m_fLiftAccel = 0;
	_float		m_fLiftSpeed = 0;


public:
	static CRigid_Body*		Create();
	virtual CComponent*		Clone(void* pArg) override;
	virtual void Free() override;
};

END
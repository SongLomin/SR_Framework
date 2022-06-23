#pragma once

#include "Component.h"

BEGIN(Engine)

class CTransform;

class ENGINE_DLL CRigidBody final : public CComponent
{
public:
	enum Func{ LEFT,RIGHT,FRONT,BACK,JUMP,LIFT};

	typedef struct tagRigidbodyDesc
	{
		_float		m_fOwnerSpeed;
		_float		m_fOwnerAccel;
		_float		m_fOwnerRadSpeed;
		_float		m_fOwnerLiftSpeed;

		_float		m_fFrictional;
		_float		m_fRadFrictional;

		_float		m_fRadZ;

		_float		m_fRadDrag;
		_float		m_fDirDrag;
	}RIGIDBODYDESC;

private:
	CRigidBody();
	CRigidBody(const CRigidBody& Prototype);
	virtual ~CRigidBody() = default;

public:
	virtual HRESULT		Initialize_Prototype();
	virtual HRESULT		Initialize(void* pArg);
	void	Link_TransformCom(CTransform* _pTransform);

public:
	void		Add_Dir(Func Dir);

private:
	void		Compute_Force();

	void		Compute_Dir();
	void		Compute_Rotation();
	void		Compute_RotDirection();//비행기 회전용
	void		Compute_Jump();
	void		Compute_Lift();

	void		Friction();//마찰력

	void		Move();


	void		Update_Transform(_float fTimeDelta);

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
	_float3		m_vJump;//점프할 때 이용
	
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
	static CRigidBody*		Create();
	virtual CComponent*		Clone(void* pArg) override;
	virtual void Free() override;
};

END
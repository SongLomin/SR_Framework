#pragma once

#include "Component.h"

BEGIN(Engine)

class CTransform;

class ENGINE_DLL CRigid_Body final: public CComponent
{
private:
	CRigid_Body();
	CRigid_Body(const CRigid_Body& Prototype);
	virtual ~CRigid_Body() = default;

public:
	virtual HRESULT		Initialize_Prototype();
	virtual HRESULT		Initialize(void* pArg);
	void	Link_TransformCom(CTransform* _pTransform);

public:
	void		Add_DirZ(_float vAccel);
	void		Add_DirY(_float vAccel);
	void		Add_DirX(_float vAccel);

	void		Add_RotationY(_float fRadAccel);
	void		Add_RotationX(_float fRadAccel);

	void		Add_Jump();
	void		Update_Transform(_float fTimeDelta);

private:
	void		Compute_Force();

	void		Compute_Dir();
	void		Compute_Rotation();
	void		Compute_Jump();


private:
	CTransform*		m_pTransform;

private:
	_float		m_fOwnerSpeed=0;
	_float		m_fOwnerRadSpeed = 0;

	_float		m_fSpeedZ=0;
	_float		m_fAccelZ=0;

	_float		m_fSpeedY= 0;
	_float		m_fAccelY= 0;

	_float		m_fSpeedX = 0;
	_float		m_fAccelX = 0;

	_float		m_fRadAccelY=0;//Y√‡ ±‚¡ÿ
	_float		m_fRadSpeedY=0;

	_float		m_fRadAccelX= 0;
	_float		m_fRadSpeedX= 0;

	_float		m_fJump = 0;
	bool		m_bJump = 0;
	
public:
	static CRigid_Body*		Create();
	virtual CComponent*		Clone(void* pArg) override;
	virtual void Free() override;

};

END
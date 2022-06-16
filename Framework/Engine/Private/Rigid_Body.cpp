#include "Rigid_Body.h"
#include "GameInstance.h"


CRigid_Body::CRigid_Body()
{
}

CRigid_Body::CRigid_Body(const CRigid_Body & Prototype)
{
	*this = Prototype;
}

HRESULT CRigid_Body::Initialize_Prototype()
{
	
	return S_OK;
}

HRESULT CRigid_Body::Initialize(void * pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	if (nullptr != pArg)
		memcpy(&m_RigidbodyDesc, pArg, sizeof(RIGIDBODYDESC));

	return S_OK;
}

void CRigid_Body::Link_TransformCom(CTransform * _pTransform)
{
	m_pTransform = _pTransform;
	m_pTransform->Set_WeakPtr(&m_pTransform);

}


void CRigid_Body::Add_DirZ(_float vAccel)
{
	m_fAccelZ = vAccel;
}

void CRigid_Body::Add_DirY(_float vAccel)
{
	m_fAccelY = vAccel;
}

void CRigid_Body::Add_DirX(_float vAccel)
{
	m_fAccelX = vAccel;
}

void CRigid_Body::Add_RotationY(_float fRadAccel)
{

	m_fRadAccelY = fRadAccel;
}

void CRigid_Body::Add_RotationX(_float fRadAccel)
{
	m_fRadAccelX = fRadAccel;
}

void CRigid_Body::Add_RotationZ(_float fRadAccel)
{
	m_fRadAccelZ = fRadAccel;
}

void CRigid_Body::Add_Jump()
{
	m_fJump = 5.f;
	m_bJump = true;
}

void CRigid_Body::Compute_Force()
{
	
	Compute_Dir();
	Compute_Rotation();
	Compute_Jump();

}

void CRigid_Body::Compute_Dir()
{

	/*앞뒤 움직임*/
	if (m_RigidbodyDesc.m_fOwnerSpeed > fabs(m_fSpeedZ))
	{
		m_fSpeedZ += m_fAccelZ;
	}

	if (DBL_EPSILON < fabs(m_fSpeedZ))
	{

		if (0.f < m_fSpeedZ)
			m_fSpeedZ -= m_RigidbodyDesc.m_fFrictional;
		else if (0.f > m_fSpeedZ)
			m_fSpeedZ += m_RigidbodyDesc.m_fFrictional;
	}
	if (m_RigidbodyDesc.m_fFrictional > fabs(m_fSpeedZ))
		m_fSpeedZ = 0.f;

	

	/*Y방향*/
	if (m_RigidbodyDesc.m_fOwnerSpeed > fabs(m_fSpeedY))
	{
		m_fSpeedY += m_fAccelY;
	}

	if (DBL_EPSILON < fabs(m_fSpeedY))
	{

		if (0.f < m_fSpeedY)
			m_fSpeedY -= m_RigidbodyDesc.m_fFrictional;
		else if (0.f > m_fSpeedY)
			m_fSpeedY += m_RigidbodyDesc.m_fFrictional;
	}
	if (m_RigidbodyDesc.m_fFrictional > fabs(m_fSpeedY))
		m_fSpeedY = 0.f;

	/*X*/
	if (m_RigidbodyDesc.m_fOwnerSpeed > fabs(m_fSpeedX))
	{
		m_fSpeedX += m_fAccelX;
	}
	
	if (DBL_EPSILON < fabs(m_fSpeedX))
	{
		if (0.f < m_fSpeedX)
			m_fSpeedX -= m_RigidbodyDesc.m_fFrictional;
		else if (0.f > m_fSpeedX)
			m_fSpeedX += m_RigidbodyDesc.m_fFrictional;
	
	}
	if (m_RigidbodyDesc.m_fFrictional > fabs(m_fSpeedX))
		m_fSpeedX = 0.f;

}
//일단 좌우 회전
void CRigid_Body::Compute_Rotation()
{
	/*각속도(Y축회전)*/
	if (m_RigidbodyDesc.m_fOwnerRadSpeed > fabs(m_fRadSpeedY))
	{
		m_fRadSpeedY += m_fRadAccelY;
	}

	if (DBL_EPSILON < fabs(m_fRadSpeedY))
	{
		float _fAccel;
		if (DBL_EPSILON < fabs(m_fSpeedZ))
			_fAccel = m_RigidbodyDesc.m_fRadFrictional*2.f;
		else
			_fAccel = m_RigidbodyDesc.m_fRadFrictional;

		if (0.f < m_fRadSpeedY)
			m_fRadSpeedY -= _fAccel;
		else if (0.f > m_fRadSpeedY)
			m_fRadSpeedY += _fAccel;
	}
	if (m_RigidbodyDesc.m_fRadFrictional > fabs(m_fRadSpeedY))
		m_fRadSpeedY = 0.f;

	/*각속도(X축회전)*/
	if (m_RigidbodyDesc.m_fOwnerRadSpeed > fabs(m_fRadSpeedX))
	{
		m_fRadSpeedX += m_fRadAccelX;
	}

	if (DBL_EPSILON < fabs(m_fRadSpeedX))
	{
		float _fAccel;
		if (DBL_EPSILON < fabs(m_fSpeedZ))
			_fAccel = m_RigidbodyDesc.m_fRadFrictional*2.f;
		else
			_fAccel = m_RigidbodyDesc.m_fRadFrictional;

		if (0.f < m_fRadSpeedX)
			m_fRadSpeedX -= _fAccel;
		else if (0.f > m_fRadSpeedX)
			m_fRadSpeedX += _fAccel;
	}
	if (m_RigidbodyDesc.m_fRadFrictional > fabs(m_fRadSpeedX))
		m_fRadSpeedX = 0.f;

	/*각속도(Z축회전)*/
	if (m_RigidbodyDesc.m_fOwnerRadSpeed > fabs(m_fRadSpeedZ))
	{
		m_fRadSpeedZ += m_fRadAccelZ;
	}

	if (DBL_EPSILON < fabs(m_fRadSpeedZ))
	{
		float _fAccel;
		if (DBL_EPSILON < fabs(m_fSpeedZ))
			_fAccel = m_RigidbodyDesc.m_fRadFrictional*2.f;
		else
			_fAccel = m_RigidbodyDesc.m_fRadFrictional;

		if (0.f < m_fRadSpeedZ)
			m_fRadSpeedZ -= _fAccel;
		else if (0.f > m_fRadSpeedZ)
			m_fRadSpeedZ += _fAccel;
	}
	if (m_RigidbodyDesc.m_fRadFrictional > fabs(m_fRadSpeedZ))
		m_fRadSpeedZ = 0.f;


}

void CRigid_Body::Compute_Jump()
{
	/*점프*/
	_float3 fOwnerPos = m_pTransform->Get_State(CTransform::STATE_POSITION);
	if (1.f > fOwnerPos.y)
	{
		m_bJump = false;
		fOwnerPos.y += 1.f - fOwnerPos.y;//(지형의 높이 넣어줌)
		m_pTransform->Set_State(CTransform::STATE_POSITION, fOwnerPos);
	}

	if (m_bJump)
	{
		m_fJump -=0.098f;
	}
}


void CRigid_Body::Update_Transform(_float fTimeDelta)
{
	Compute_Force();
	if (m_bJump)
		m_pTransform->Go_UpAndDown(m_fJump, fTimeDelta);

	if (DBL_EPSILON < fabs(m_fSpeedZ))
		m_pTransform->Go_BackAndForth(m_fSpeedZ, fTimeDelta);
	if (DBL_EPSILON < fabs(m_fSpeedY))
		m_pTransform->Go_UpAndDown(m_fSpeedY, fTimeDelta);
	if (DBL_EPSILON < fabs(m_fSpeedX))
		m_pTransform->Go_SideToSide(m_fSpeedX, fTimeDelta);


	if (DBL_EPSILON < fabs(m_fRadSpeedY))
		m_pTransform->Turn(m_pTransform->Get_State(CTransform::STATE_UP), m_fRadSpeedY, fTimeDelta);
	if (DBL_EPSILON < fabs(m_fRadSpeedX))
		m_pTransform->Turn(m_pTransform->Get_State(CTransform::STATE_RIGHT), m_fRadSpeedX, fTimeDelta);
	if (DBL_EPSILON < fabs(m_fRadSpeedZ))
		m_pTransform->Turn(m_pTransform->Get_State(CTransform::STATE_LOOK), m_fRadSpeedZ, fTimeDelta);

}

CRigid_Body * CRigid_Body::Create()
{
	CREATE_PIPELINE(CRigid_Body);
}

CComponent * CRigid_Body::Clone(void * pArg)
{
	CLONE_PIPELINE(CRigid_Body);
}

void CRigid_Body::Free()
{
	__super::Free();

	delete this;
}


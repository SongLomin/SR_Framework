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
	return S_OK;
}

void CRigid_Body::Link_TransformCom(CTransform * _pTransform)
{
	m_pTransform = _pTransform;
	m_pTransform->Set_WeakPtr(&m_pTransform);

	m_fOwnerRadSpeed = m_pTransform->Get_RotationSpeed();
	m_fOwnerSpeed = m_pTransform->Get_Speed();
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
	if (m_fOwnerSpeed > fabs(m_fSpeedZ))
	{
		m_fSpeedZ += m_fAccelZ;
	}

	if (DBL_EPSILON < fabs(m_fSpeedZ))
	{

		if (0.f < m_fSpeedZ)
			m_fSpeedZ -= 0.05f;
		else if (0.f > m_fSpeedZ)
			m_fSpeedZ += 0.05f;
	}
	if (0.01f > fabs(m_fSpeedZ))
		m_fSpeedZ = 0.f;

	

	/*Y방향*/
	if (m_fOwnerSpeed > fabs(m_fSpeedY))
	{
		m_fSpeedY += m_fAccelY;
	}

	if (DBL_EPSILON < fabs(m_fSpeedY))
	{

		if (0.f < m_fSpeedY)
			m_fSpeedY -= 0.05f;
		else if (0.f > m_fSpeedY)
			m_fSpeedY += 0.05f;
	}
	if (0.01f > fabs(m_fSpeedY))
		m_fSpeedY = 0.f;

	/*X*/
	if (m_fOwnerSpeed > fabs(m_fSpeedX))
	{
		m_fSpeedX += m_fAccelX;
	}
	
	if (DBL_EPSILON < fabs(m_fSpeedX))
	{
		if (0.f < m_fSpeedX)
			m_fSpeedX -= 0.05f;
		else if (0.f > m_fSpeedX)
			m_fSpeedX += 0.05f;
	
	}
	if (0.01f > fabs(m_fSpeedX))
		m_fSpeedX = 0.f;

}
//일단 좌우 회전
void CRigid_Body::Compute_Rotation()
{
	/*각속도(Y축회전)*/
	if (m_fOwnerRadSpeed > fabs(m_fRadSpeedY))
	{
		m_fRadSpeedY += m_fRadAccelY;
	}

	if (DBL_EPSILON < fabs(m_fRadSpeedY))
	{
		float _fAccel;
		if (DBL_EPSILON < fabs(m_fSpeedX))
			_fAccel = 0.2f;
		else
			_fAccel = 0.03f;

		if (0.f < m_fRadSpeedY)
			m_fRadSpeedY -= _fAccel;
		else if (0.f > m_fRadSpeedY)
			m_fRadSpeedY += _fAccel;
	}
	if (0.01f > fabs(m_fRadSpeedY))
		m_fRadSpeedY = 0.f;


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
	if(DBL_EPSILON < fabs(m_fSpeedZ))
		m_pTransform->Go_BackAndForth(m_fSpeedZ, fTimeDelta);
	if (DBL_EPSILON < fabs(m_fSpeedY))
		m_pTransform->Go_UpAndDown(m_fSpeedY, fTimeDelta);
	
	if (DBL_EPSILON < fabs(m_fSpeedX))
		m_pTransform->Go_SideToSide(m_fSpeedX, fTimeDelta);
	if(DBL_EPSILON < fabs(m_fRadSpeedY))
		m_pTransform->Turn(m_pTransform->Get_State(CTransform::STATE_UP), m_fRadSpeedY, fTimeDelta);
	
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


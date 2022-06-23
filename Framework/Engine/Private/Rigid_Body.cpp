#include "Rigid_Body.h"
#include "GameInstance.h"


CRigid_Body::CRigid_Body()
{
}

CRigid_Body::CRigid_Body(const CRigid_Body & Prototype)
{
	*this = Prototype;
}

void CRigid_Body::Tick(_float fTimeDelta)
{
	Update_Transform(fTimeDelta);
}

void CRigid_Body::LateTick(_float fTimeDelta)
{

}

HRESULT CRigid_Body::Render()
{


	return S_OK;
}

HRESULT CRigid_Body::Initialize_Prototype()
{
	ZeroMemory(&m_vSpeed, sizeof(_float3));
	ZeroMemory(&m_vAccel, sizeof(_float3));
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

	m_vLook = m_vSubLook = m_pTransform->Get_State(CTransform::STATE_LOOK);
	m_vRight = m_vSubRight = m_pTransform->Get_State(CTransform::STATE_RIGHT);
	m_vUp = m_vSubUp = _float3(0.f, 1.f, 0.f);
	m_vPos  = m_pTransform->Get_State(CTransform::STATE_POSITION);

}

void CRigid_Body::Add_Dir(Func Dir, _float fDir )
{
	switch (Dir)
	{
	case LEFT:
		//m_vAccel -= m_vRight;
		m_fRadAccelY = -1.f*m_RigidbodyDesc.m_fOwnerRadAccel;
		if (m_bLift)
		{
			m_fRadAccelZ = 0.01f;
		}
		break;

	case RIGHT:
		//m_vAccel += m_vRight;
		m_fRadAccelY = m_RigidbodyDesc.m_fOwnerRadAccel;
		if (m_bLift)
		{
			m_fRadAccelZ = -0.01f;
		}
		break;

	case FRONT:
		m_vAccel += m_vLook;
		break;

	case BACK:
		m_vAccel -= m_vLook;
		m_fRadAccelY *= -1.f;
		break;

	case JUMP:
		m_fJump = m_RigidbodyDesc.m_fOwnerJump*m_RigidbodyDesc.m_fOwnerJumpScale;
		m_bJump = true;
		break;

	case LIFT:
		if (m_RigidbodyDesc.m_fOwnerSpeed*0.7 < fabs(D3DXVec3Length(&m_vSpeed)))
		{
			m_fLiftAccel = m_RigidbodyDesc.m_fOwnerLiftAccel;
			m_fRadAccelX = -0.005f;
			m_bLift = true;
		}
		break;


	}
}

void CRigid_Body::Add_Rotation(Func Dir, _float fRad)
{
	switch (Dir)
	{
	case LEFT:
		//m_vAccel -= m_vRight;
		m_fRadAccelZ = -1.f*fRad;
		break;

	case RIGHT:
		//m_vAccel += m_vRight;
		m_fRadAccelZ = fRad;
		break;

	case FRONT:
		m_fRadAccelX = -1.f*fRad;
		break;

	case BACK:
		m_fRadAccelX = fRad;
		break;
	}
}



void CRigid_Body::Compute_Force()
{

	Compute_Dir();
	Compute_Rotation();
	if (m_bLift)
	{
		Compute_Lift();
		Compute_RotDirection();
	}
	else
	{
		if (m_bJump)
			Compute_Jump();
		Friction();
	}
	//Compute_Ground();
}

void CRigid_Body::Compute_Dir()
{
	D3DXVec3Normalize(&m_vAccel, &m_vAccel);
	m_vSpeed += m_vAccel*m_RigidbodyDesc.m_fOwnerAccel;

	if (m_RigidbodyDesc.m_fOwnerSpeed < fabs(D3DXVec3Length(&m_vSpeed)))
	{
		D3DXVec3Normalize(&m_vSpeed, &m_vSpeed);
		m_vSpeed *= m_RigidbodyDesc.m_fOwnerSpeed;
	}

}

void CRigid_Body::Friction()
{

	if (DBL_EPSILON < fabs(D3DXVec3Length(&m_vSpeed)))
	{
		_float3 vFriction;
		D3DXVec3Normalize(&vFriction, &m_vSpeed);
	

		m_vSpeed -= vFriction * m_RigidbodyDesc.m_fFrictional;

		if (m_RigidbodyDesc.m_fFrictional > fabs(D3DXVec3Length(&m_vSpeed)))
			m_vSpeed = _float3(0.f, 0.f, 0.f);
	}
	

}

void CRigid_Body::Move(_float fTimeDelta)
{
	m_vPos += m_vSpeed*fTimeDelta;
	if (m_bJump)
		m_vPos += m_vUp*m_fJump*fTimeDelta;
	else if (m_bLift)
		m_vPos += m_vUp*m_fLiftSpeed*fTimeDelta;
}

void CRigid_Body::Turn(_float fTimeDelta)
{
	D3DXMATRIX	matRotation;
	D3DXMatrixRotationAxis(&matRotation, &_float3(0.f,1.f,0.f), m_fRadSpeedY * fTimeDelta);

	D3DXVec3TransformNormal(&m_vLook, &m_vLook, &matRotation);

	D3DXVec3Cross(&m_vRight, &_float3(0.f, 1.f, 0.f), &m_vLook);
	D3DXVec3Cross(&m_vUp, &m_vLook, &m_vRight);

	D3DXVec3TransformCoord(&m_vSpeed, &m_vSpeed, &matRotation);


	m_vSubLook = m_vLook;
	m_vSubUp = m_vUp;
	m_vSubRight = m_vRight;
}

void CRigid_Body::SubTurn()
{
	D3DXMATRIX	matRotation;
	
	D3DXMatrixRotationAxis(&matRotation, &m_vSubLook, m_fRadSpeedZ);

	D3DXVec3TransformNormal(&m_vSubUp, &m_vSubUp, &matRotation);
	D3DXVec3Cross(&m_vSubRight, &m_vSubUp, &m_vSubLook);

	D3DXMatrixRotationAxis(&matRotation, &m_vSubRight, m_fRadSpeedX);

	D3DXVec3TransformNormal(&m_vSubLook, &m_vSubLook, &matRotation);
	D3DXVec3Cross(&m_vSubUp, &m_vSubLook, &m_vSubRight);
}


//일반 좌우 회전
void CRigid_Body::Compute_Rotation()
{
	/*각속도(Y축회전)*/
	if (m_RigidbodyDesc.m_fOwnerRadSpeed - (m_bLift ? m_RigidbodyDesc.m_fRadDrag : 0) > fabs(m_fRadSpeedY))
	{
		m_fRadSpeedY += m_fRadAccelY;
	}

	if (DBL_EPSILON < fabs(m_fRadSpeedY))
	{
		float _fAccel;
		if (DBL_EPSILON < fabs(D3DXVec3Length(&m_vSpeed)))
			_fAccel = m_RigidbodyDesc.m_fRadFrictional*2.f;
		else
			_fAccel = m_RigidbodyDesc.m_fRadFrictional;

		if (0.f < m_fRadSpeedY)
			m_fRadSpeedY -= _fAccel;

		else if (0.f > m_fRadSpeedY)
			m_fRadSpeedY += _fAccel;



		if (m_RigidbodyDesc.m_fRadFrictional > fabs(m_fRadSpeedY))
			m_fRadSpeedY = 0.f;
	}
}

void CRigid_Body::Compute_RotDirection()
{
	if (D3DXToRadian(30.f) > fabs(m_fRadSpeedZ))
	{
		m_fRadSpeedZ += m_fRadAccelZ;
	}

	if (!(DBL_EPSILON < fabs(m_fRadAccelZ)))
		if (DBL_EPSILON < fabs(m_fRadSpeedZ))
		{
			float _fAccel;
			_fAccel = m_RigidbodyDesc.m_fRadZ;


			if (0.f < m_fRadSpeedZ)
				m_fRadSpeedZ -= _fAccel;
			else if (0.f > m_fRadSpeedZ)
				m_fRadSpeedZ += _fAccel;

			if (m_RigidbodyDesc.m_fRadZ> fabs(m_fRadSpeedZ))
				m_fRadSpeedZ = 0.f;
		}

	if (D3DXToRadian(20.f) > fabs(m_fRadSpeedX))
	{
		m_fRadSpeedX += m_fRadAccelX;
	}

	if (!(DBL_EPSILON < fabs(m_fRadAccelX)))
		if (DBL_EPSILON < fabs(m_fRadSpeedX))
		{
			float _fAccel;
			_fAccel = m_RigidbodyDesc.m_fRadZ;


			if (0.f < m_fRadSpeedX)
				m_fRadSpeedX -= _fAccel;
			else if (0.f > m_fRadSpeedX)
				m_fRadSpeedX += _fAccel;

			if (m_RigidbodyDesc.m_fRadZ> fabs(m_fRadSpeedX))
				m_fRadSpeedX = 0.f;
		}
}

void CRigid_Body::Compute_Jump()
{
	/*점프*/
	m_fJump -= 0.098f;
	
}

void CRigid_Body::Compute_Lift()//수직방향
{
	if (!m_bLift) return;

	if (m_RigidbodyDesc.m_fOwnerLiftSpeed > m_fLiftSpeed)
	{
		m_fLiftSpeed += m_fLiftAccel;
	}

	if (DBL_EPSILON < m_fLiftSpeed)
	{
		m_fLiftSpeed -= 0.098f;//중력을 받음

		if (0.098f > fabs(m_fLiftSpeed))
			m_fLiftSpeed = 0.f;
	}
	else if (DBL_EPSILON < fabs(D3DXVec3Length(&m_vAccel)))
	{
		if (0.f> m_fLiftSpeed)
			m_fLiftSpeed += 0.01f;

		if (0.01f > fabs(m_fLiftSpeed))
			m_fLiftSpeed = 0.f;
	}
	else
	{
		if (-2.f < m_fLiftSpeed)
			m_fLiftSpeed -= 0.098f;
	}
}

void CRigid_Body::Compute_Ground()
{
	if (1.f > m_vPos.y)
	{
		m_fLiftSpeed = 0.f;
		m_fJump = 0.f;
		m_bJump = false;
		m_bLift = false;
		m_vPos.y += 1.f - m_vPos.y;//(지형의 높이 넣어줌)
	}
}


void CRigid_Body::Update_Transform(_float fTimeDelta)
{
	Compute_Force();
	Move(fTimeDelta);
	Turn(fTimeDelta);
	SubTurn();

	m_pTransform->Set_State(CTransform::STATE_LOOK, m_vSubLook);
	m_pTransform->Set_State(CTransform::STATE_UP, m_vSubUp);
	m_pTransform->Set_State(CTransform::STATE_RIGHT, m_vSubRight);
	m_pTransform->Set_State(CTransform::STATE_POSITION, m_vPos);

	m_vAccel = _float3(0.f, 0.f, 0.f);
	m_fRadAccelX = m_fRadAccelY = m_fRadAccelZ = 0.f;
	m_fLiftAccel = 0;

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


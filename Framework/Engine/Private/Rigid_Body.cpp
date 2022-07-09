#include "Rigid_Body.h"
#include "GameInstance.h"


CRigid_Body::CRigid_Body()
{
}

CRigid_Body::CRigid_Body(const CRigid_Body& Prototype)
{
	*this = Prototype;
}

void CRigid_Body::Tick(_float fTimeDelta)
{
	
	
}

void CRigid_Body::LateTick(_float fTimeDelta)
{
	Set_DirVector();
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

HRESULT CRigid_Body::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	if (nullptr != pArg)
		memcpy(&m_RigidbodyDesc, pArg, sizeof(RIGIDBODYDESC));

	return S_OK;
}

void CRigid_Body::Link_TransformCom(CTransform* _pTransform)
{
	m_pTransform = _pTransform;
	m_pTransform->Set_WeakPtr(&m_pTransform);

}

void CRigid_Body::Add_Dir(Func Dir, _float fDir)//fDir에 마우스 이동량을 전달
{
	if (m_bMouse)
	{
		switch (Dir)
		{
		case SPIN://좌우 회전
			m_fRadSpeedY = fDir * 0.1f;
			m_fRadSpeedZ = fDir * -0.01f;
			break;

		case DOWN://위아래 회전
		//	m_fLiftSpeed = fDir*-1.f;
			m_fRadSpeedX = fDir * 0.01f;
			break;

		case FRONT:
			m_vAccel += m_vLook;
			break;

		case BACK:
			m_vAccel -= m_vLook;
			break;

		case LEFT:
			m_vAccel -= m_vRight;
			break;

		case RIGHT:
			m_vAccel += m_vRight;
			break;

		}


	}
	else
	{
		switch (Dir)
		{
		case LEFT:
			//m_vAccel -= m_vRight;
			m_fRadAccelY = -1.f * (fDir ? fDir : m_RigidbodyDesc.m_fOwnerRadAccel);
			if (m_bLift)
			{
				m_fRadAccelZ = 0.01f;
			}
			break;

		case RIGHT:
			//m_vAccel += m_vRight;
			m_fRadAccelY = fDir ? fDir : m_RigidbodyDesc.m_fOwnerRadAccel;
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


		case LIFT:
			if (m_RigidbodyDesc.m_fOwnerSpeed * 0.7 < fabs(D3DXVec3Length(&m_vSpeed)))
			{
				m_fLiftAccel = m_RigidbodyDesc.m_fOwnerLiftAccel;
				m_fRadAccelX = -0.005f;
				m_bLift = true;
			}
			break;

		case DOWN:
			if (m_bLift)
			{
				m_fLiftAccel = -1.f * m_RigidbodyDesc.m_fOwnerLiftAccel;
				m_fRadAccelX = 0.005f;
			}
			break;
		}
	}
}

void CRigid_Body::Add_Camera(Func Dir, _float fDir)
{

	switch (Dir)
	{
	case RIGHT://좌우 회전
		m_fRadSpeedZ = fDir * 0.01f;
		m_vSpeed += m_vRight * fDir * 0.01f;
		break;

	case DOWN://위아래 회전

		m_vSpeed += m_vUp * fDir * -0.01f;
		break;

	}
}

void CRigid_Body::Add_Force(_float3 fDir)
{
	m_vSpeed += fDir;
}



void CRigid_Body::Compute_Force(_float fTimeDelta)
{
	if (m_bCamera)
	{
		Compute_Camera();
		Compute_RotDirection();
	}
	else
	{
		Compute_Dir(fTimeDelta);
		Compute_Rotation();
		if (m_bLift)
		{
			Compute_Lift();
			Compute_RotDirection();
		}

		Friction(fTimeDelta);
		//Compute_Ground();
	}
}

void CRigid_Body::Compute_Camera()
{
	m_vSubLook = m_vLook;
	m_vSubUp = m_vUp;
	m_vSubRight = m_vRight;

	m_vPos += m_vSpeed;
	m_vSpeed = _float3(0.f, 0.f, 0.f);
}

void CRigid_Body::Compute_Dir(_float fTimeDelta)
{
	D3DXVec3Normalize(&m_vAccel, &m_vAccel);

	if (m_bBooster)
	{
		m_vSpeed += m_vAccel * m_RigidbodyDesc.m_fBoosterAccel;
		if (m_RigidbodyDesc.m_fBoosterSpeed < fabs(D3DXVec3Length(&m_vSpeed)))
		{
			D3DXVec3Normalize(&m_vSpeed, &m_vSpeed);
			m_vSpeed *= m_RigidbodyDesc.m_fBoosterSpeed;

		}

	}
	else
	{
		
		if (!m_bBooster && fabs(D3DXVec3Length(&m_vSpeed) < m_RigidbodyDesc.m_fOwnerSpeed))
		{
			m_vSpeed += m_vAccel * m_RigidbodyDesc.m_fOwnerAccel;
			if (m_RigidbodyDesc.m_fOwnerSpeed < fabs(D3DXVec3Length(&m_vSpeed)))
			{
				D3DXVec3Normalize(&m_vSpeed, &m_vSpeed);
				m_vSpeed *= m_RigidbodyDesc.m_fOwnerSpeed;
			}
		}
	}
	

}

void CRigid_Body::Friction(_float fTimeDelta)
{

	if (DBL_EPSILON < fabs(D3DXVec3Length(&m_vSpeed)))
	{
		_float3 vFriction;
		D3DXVec3Normalize(&vFriction, &m_vSpeed);


		m_vSpeed -= vFriction * m_RigidbodyDesc.m_fFrictional ;
		_float fLength = D3DXVec3Length(&m_vSpeed);
		if (m_RigidbodyDesc.m_fFrictional > fabs(fLength))
			m_vSpeed = _float3(0.f, 0.f, 0.f);
	}

	if (!m_bBooster)
	{
		if (m_RigidbodyDesc.m_fOwnerSpeed < fabs(D3DXVec3Length(&m_vSpeed)))
		{
			_float3 vFriction;
			D3DXVec3Normalize(&vFriction, &m_vSpeed);


			m_vSpeed -= vFriction * (m_RigidbodyDesc.m_fBoosterAccel * 0.3f) ;

			if (m_RigidbodyDesc.m_fOwnerSpeed > fabs(D3DXVec3Length(&m_vSpeed)))
			{
				m_vSpeed = (*D3DXVec3Normalize(&m_vSpeed, &m_vSpeed) * m_RigidbodyDesc.m_fOwnerSpeed);
			}
		}
	}


}

void CRigid_Body::Move(_float fTimeDelta)
{
	m_vPos += m_vSpeed * fTimeDelta ;
	if (m_bLift)
		m_vPos += m_vUp * m_fLiftSpeed * fTimeDelta;
}

void CRigid_Body::Turn(_float fTimeDelta)
{
	D3DXMATRIX	matRotation;
	D3DXMatrixRotationAxis(&matRotation, &m_vUp, m_fRadSpeedY * fTimeDelta);

	D3DXVec3TransformNormal(&m_vLook, &m_vLook, &matRotation);

	D3DXVec3Cross(&m_vRight, &m_vUp, &m_vLook);
	D3DXVec3Cross(&m_vUp, &m_vLook, &m_vRight);

	D3DXVec3TransformCoord(&m_vSpeed, &m_vSpeed, &matRotation);

	D3DXMatrixRotationAxis(&matRotation, &m_vRight, m_fRadSpeedX * fTimeDelta);

	D3DXVec3TransformNormal(&m_vLook, &m_vLook, &matRotation);

	D3DXVec3Cross(&m_vUp, &m_vLook, &m_vRight);
	D3DXVec3Cross(&m_vRight, &m_vUp, &m_vLook);

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
	if (m_bMouse)
	{
		if (m_RigidbodyDesc.m_fOwnerRadSpeed < fabs(m_fRadSpeedY))
		{
			if (0.f < m_fRadSpeedY)
			{
				m_fRadSpeedY = m_RigidbodyDesc.m_fOwnerRadSpeed;
			}
			else if (0.f > m_fRadSpeedY)
			{
				m_fRadSpeedY = -1.f * m_RigidbodyDesc.m_fOwnerRadSpeed;
			}

		}

	}
	else
	{
		if (m_RigidbodyDesc.m_fOwnerRadSpeed - (m_bLift ? m_RigidbodyDesc.m_fRadDrag : 0) > fabs(m_fRadSpeedY))
		{
			m_fRadSpeedY += m_fRadAccelY;
		}

		if (DBL_EPSILON < fabs(m_fRadSpeedY))
		{
			float _fAccel;
			if (DBL_EPSILON < fabs(D3DXVec3Length(&m_vSpeed)))
				_fAccel = m_RigidbodyDesc.m_fRadFrictional * 2.f;
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
}

void CRigid_Body::Compute_RotDirection()
{
	if (m_bMouse)
	{
		if (D3DXToRadian(30.f) < fabs(m_fRadSpeedZ))
		{
			if (0.f > m_fRadSpeedZ)
			{
				m_fRadSpeedZ = -1.f * D3DXToRadian(30.f);
			}
			else if (0.f < m_fRadSpeedZ)
			{
				m_fRadSpeedZ = D3DXToRadian(30.f);
			}
		}

		if (D3DXToRadian(40.f) < fabs(m_fRadSpeedX))
		{
			if (0.f > m_fRadSpeedX)
			{
				m_fRadSpeedX = -1.f * D3DXToRadian(40.f);
			}

			else if (0.f < m_fRadSpeedX)
			{
				m_fRadSpeedX = D3DXToRadian(40.f);
			}
		}

	}
	else
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

				if (m_RigidbodyDesc.m_fRadZ > fabs(m_fRadSpeedZ))
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

				if (m_RigidbodyDesc.m_fRadZ > fabs(m_fRadSpeedX))
					m_fRadSpeedX = 0.f;
			}
	}
}


void CRigid_Body::Compute_Lift()//수직방향
{
	if (!m_bLift) return;

	if (m_RigidbodyDesc.m_fOwnerLiftSpeed > fabs(m_fLiftSpeed))
	{
		m_fLiftSpeed += m_fLiftAccel;
	}

	if (DBL_EPSILON < fabs(m_fLiftSpeed))
	{
		if (0.f < m_fLiftSpeed)
			m_fLiftSpeed -= 0.098f;//중력을 받음
		else if (0.f > m_fLiftSpeed)
			m_fLiftSpeed += 0.098f;

		if (0.098f > fabs(m_fLiftSpeed))
			m_fLiftSpeed = 0.f;
	}

}

void CRigid_Body::Compute_Ground()
{
	if (1.f > m_vPos.y)
	{
		m_fLiftSpeed = 0.f;
		m_bLift = false;
		m_vPos.y += 1.f - m_vPos.y;//(지형의 높이 넣어줌)
	}
}


void CRigid_Body::Update_Transform(_float fTimeDelta)
{
	Compute_Force(fTimeDelta);
	if (m_bCamera)
	{
		SubTurn();
		D3DXVec3Normalize(&m_vSubLook, &m_vSubLook);
		D3DXVec3Normalize(&m_vSubUp, &m_vSubUp);
		D3DXVec3Normalize(&m_vSubRight, &m_vSubRight);

		m_vSubLook *= m_vScale.z;
		m_vSubUp *= m_vScale.y;
		m_vSubRight *= m_vScale.x;

		m_pTransform->Set_State(CTransform::STATE_LOOK, m_vSubLook, true);
		m_pTransform->Set_State(CTransform::STATE_UP, m_vSubUp, true);
		m_pTransform->Set_State(CTransform::STATE_RIGHT, m_vSubRight, true);
		m_pTransform->Set_State(CTransform::STATE_POSITION, m_vPos, true);
	}
	else
	{
		Move(fTimeDelta);
		Turn(fTimeDelta);
		SubTurn();


		D3DXVec3Normalize(&m_vLook, &m_vLook);
		D3DXVec3Normalize(&m_vUp, &m_vUp);
		D3DXVec3Normalize(&m_vRight, &m_vRight);

		m_vLook *= m_vScale.z;
		m_vUp *= m_vScale.y;
		m_vRight *= m_vScale.x;

		m_pTransform->Set_State(CTransform::STATE_LOOK, m_vLook);
		m_pTransform->Set_State(CTransform::STATE_UP, m_vUp);
		m_pTransform->Set_State(CTransform::STATE_RIGHT, m_vRight);
		m_pTransform->Set_State(CTransform::STATE_POSITION, m_vPos);
	}
	m_vAccel = _float3(0.f, 0.f, 0.f);
	m_fRadAccelX = m_fRadAccelY = m_fRadAccelZ = 0.f;
	m_fLiftAccel = 0;

}

void CRigid_Body::Set_DirVector()
{
	if (m_bFirst)
	{
		m_vLook = m_vSubLook = m_pTransform->Get_State(CTransform::STATE_LOOK);
		m_vRight = m_vSubRight = m_pTransform->Get_State(CTransform::STATE_RIGHT);
		m_vUp = m_vSubUp = _float3(0.f, 1.f, 0.f);

		m_bFirst = false;
	}

	m_vLook = m_pTransform->Get_State(CTransform::STATE_LOOK);
	m_vRight = m_pTransform->Get_State(CTransform::STATE_RIGHT);
	m_vUp = m_pTransform->Get_State(CTransform::STATE_UP);
	m_vPos = m_pTransform->Get_State(CTransform::STATE_POSITION);
	m_vScale = m_pTransform->Get_Scaled();
}

_float3 CRigid_Body::Get_Vector(RIGID_BODY eType)
{
	switch (eType)
	{
	case RIGID_BODY::ACCEL:
		return m_vAccel;
	
	case RIGID_BODY::SPEED:
		return m_vSpeed;
		//받아오고 싶은 물리량 알아서 추가
	}

	return _float3(0.f, 0.f, 0.f);
}

CRigid_Body* CRigid_Body::Create()
{
	CREATE_PIPELINE(CRigid_Body);
}

CComponent* CRigid_Body::Clone(void* pArg)
{
	CLONE_PIPELINE(CRigid_Body);
}

void CRigid_Body::Free()
{
	__super::Free();

	delete this;
}


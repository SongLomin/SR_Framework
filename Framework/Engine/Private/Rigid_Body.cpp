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
	if (m_bLift)
	{
		if (0.f > fRadAccel)
			Add_RotationZ(0.05f);
		else if(0.f < fRadAccel)
			Add_RotationZ(-0.05f);
	}
	
}

void CRigid_Body::Add_RotationX(_float fRadAccel)
{
	m_fRadAccelX = fRadAccel;
}

void CRigid_Body::Add_RotationZ(_float fRadAccel)
{
	m_fRadAccelZ = fRadAccel;
}

void CRigid_Body::Add_Lift(_float fLiftAccel)
{
	if (m_RigidbodyDesc.m_fOwnerSpeed * 0.7f < m_fSpeedZ || m_bLift)
	{
		m_fLiftAccel = fLiftAccel;
		m_bLift = true;
	}
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
	if (m_bLift)
	{
		Compute_Lift();
		Compute_RotDirection();
	}Compute_Jump();

}

void CRigid_Body::Compute_Dir()
{

	/*�յ� ������*/
	if (m_RigidbodyDesc.m_fOwnerSpeed > fabs(m_fSpeedZ))
	{
		m_fSpeedZ += m_fAccelZ;
	}

	if (DBL_EPSILON < fabs(m_fSpeedZ))
	{

		if (0.f < m_fSpeedZ)
			m_fSpeedZ = m_fSpeedZ - m_RigidbodyDesc.m_fFrictional + (m_bLift ? m_RigidbodyDesc.m_fDirDrag : 0);
		else if (0.f > m_fSpeedZ)
			m_fSpeedZ += m_RigidbodyDesc.m_fFrictional;
	
		if (m_RigidbodyDesc.m_fFrictional > fabs(m_fSpeedZ))
			m_fSpeedZ = 0.f;
	}

	

	/*Y����*/
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
	
		if (m_RigidbodyDesc.m_fFrictional > fabs(m_fSpeedY))
		m_fSpeedY = 0.f;

	}
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
	
		if (m_RigidbodyDesc.m_fFrictional > fabs(m_fSpeedX))
			m_fSpeedX = 0.f;
	}
	

}
//�ϴ� �¿� ȸ��
void CRigid_Body::Compute_Rotation()
{
	/*���ӵ�(Y��ȸ��)*/
	if (m_RigidbodyDesc.m_fOwnerRadSpeed - (m_bLift? m_RigidbodyDesc.m_fRadDrag : 0) > fabs(m_fRadSpeedY))
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



		if (m_RigidbodyDesc.m_fRadFrictional > fabs(m_fRadSpeedY))
			m_fRadSpeedY = 0.f;
	}
	

	/*���ӵ�(X��ȸ��)*/
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
	
		if (m_RigidbodyDesc.m_fRadFrictional > fabs(m_fRadSpeedX))
			m_fRadSpeedX = 0.f;
	}
	

	///*���ӵ�(Z��ȸ��)*/
	//if (m_RigidbodyDesc.m_fOwnerRadSpeed > fabs(m_fRadSpeedZ))
	//{
	//	m_fRadSpeedZ += m_fRadAccelZ;
	//}

	//if (DBL_EPSILON < fabs(m_fRadSpeedZ))
	//{
	//	float _fAccel;
	//	if (DBL_EPSILON < fabs(m_fSpeedZ))
	//		_fAccel = m_RigidbodyDesc.m_fRadFrictional*2.f;
	//	else
	//		_fAccel = m_RigidbodyDesc.m_fRadFrictional;

	//	if (0.f < m_fRadSpeedZ)
	//		m_fRadSpeedZ -= _fAccel;
	//	else if (0.f > m_fRadSpeedZ)
	//		m_fRadSpeedZ += _fAccel;
	//
	//	if (m_RigidbodyDesc.m_fRadFrictional > fabs(m_fRadSpeedZ))
	//		m_fRadSpeedZ = 0.f;
	//}



}

void CRigid_Body::Compute_RotDirection()
{
	if (D3DXToRadian(30.f) > fabs(m_fRadSpeedZ))
	{
		m_fRadSpeedZ += m_fRadAccelZ;
	}

	if(!(DBL_EPSILON < fabs(m_fRadAccelZ)))
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
}

void CRigid_Body::Compute_Jump()
{
	/*����*/
	_float3 fOwnerPos = m_pTransform->Get_State(CTransform::STATE_POSITION);
	if (1.f > fOwnerPos.y)
	{
		m_fLiftSpeed = 0.f;
		m_bJump = false;
		m_bLift = false;
		fOwnerPos.y += 1.f - fOwnerPos.y;//(������ ���� �־���)
		m_pTransform->Set_State(CTransform::STATE_POSITION, fOwnerPos);
	}

	if (m_bJump)
	{
		m_fJump -=0.098f;
	}
}

void CRigid_Body::Compute_Lift()//��������
{
	if (!m_bLift) return;

	if (m_RigidbodyDesc.m_fOwnerLiftSpeed > m_fLiftSpeed)
	{
		m_fLiftSpeed += m_fLiftAccel;
	}

	if (DBL_EPSILON < m_fLiftSpeed)
	{
		m_fLiftSpeed -= 0.098f;//�߷��� ����
	
		if (0.098f > fabs(m_fLiftSpeed))
			m_fLiftSpeed = 0.f;
	}
	else if (DBL_EPSILON < m_fAccelZ)
	{
		if(0.f> m_fLiftSpeed)
			m_fLiftSpeed += 0.01f;

		if (0.01f > fabs(m_fLiftSpeed))
			m_fLiftSpeed = 0.f;
	}
	else
	{
		if(-2.f < m_fLiftSpeed)
			m_fLiftSpeed -= 0.098f;
	}
	


}


void CRigid_Body::Update_Transform(_float fTimeDelta)
{
	Compute_Force();

	if (m_bJump)
		m_pTransform->Go_UpAndDown(m_fJump, fTimeDelta);
	if (DBL_EPSILON < fabs(m_fLiftSpeed))
		m_pTransform->Go_UpAndDown(m_fLiftSpeed, fTimeDelta);

	if (m_bLift)
	{
		if (DBL_EPSILON < fabs(m_fSpeedZ))
			m_pTransform->Go_BackAndForth(m_fSpeedZ, fTimeDelta);

		if (DBL_EPSILON < fabs(m_fRadSpeedY))
			m_pTransform->Turn_AxisY(m_fRadSpeedY, fTimeDelta);

		if (DBL_EPSILON < fabs(m_fRadSpeedZ))
			m_pTransform->Turn_AxisZ(m_fRadSpeedZ, fTimeDelta);
	}
	else
	{
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
	/*if (DBL_EPSILON < fabs(m_fRadSpeedZ))
		m_pTransform->Turn(m_pTransform->Get_State(CTransform::STATE_LOOK), m_fRadSpeedZ, fTimeDelta);
*/
	}

	

	m_fAccelX = m_fAccelY = m_fAccelZ = 0.f;
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


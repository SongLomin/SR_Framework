#include "stdafx.h"
#include "Cam_TPS.h"
#include "GameInstance.h"

CCam_TPS::CCam_TPS(const CCam_TPS& Prototype)
{
	*this = Prototype;
	Add_Component<CTransform>();
}

HRESULT CCam_TPS::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCam_TPS::Initialize(void* pArg)
{
	
	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom); 

	m_pCameraCom = Add_Component<CCamera>();
	m_pCameraCom->Set_WeakPtr(&m_pCameraCom);

	m_pCameraCom->Link_TransformCom(m_pTransformCom);

	m_vCurPos = _float3(0.f, 0.f, 0.f);

	return S_OK;
}

void CCam_TPS::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	_float3 vLook = m_pCameraCom->Get_Target()->Get_State(CTransform::STATE_LOOK, true);
	_float3 vPos = m_pCameraCom->Get_Target()->Get_State(CTransform::STATE_POSITION, true);
	_float3 vUp = m_pCameraCom->Get_Target()->Get_State(CTransform::STATE_UP, true);

	_float3 vRight;
	_float  fRatio = 0.f;
	CRigid_Body* pTargetRigidBody = m_pCameraCom->Get_Target()->Get_Owner()->Get_Component<CRigid_Body>();
	if (pTargetRigidBody)
	{
		_float3 vTargetSpeed = pTargetRigidBody->Get_Vector(RIGID_BODY::SPEED);
		if (0.f > D3DXVec3Dot(&vLook, &vTargetSpeed))
			fRatio = 0.f;
		else
		{
			fRatio = D3DXVec3Length(&vTargetSpeed) / 50.f;
			if (1.f < fRatio)
				fRatio = 1.f;
		}

	}
	

	vPos -= vLook*(15.f + 10.f*fRatio);
	vPos += vUp*3.f;

	D3DXVec3Cross(&vRight, &vUp, &vLook);
	D3DXVec3Cross(&vUp, &vLook, &vRight);

	



	if (GAMEINSTANCE->Get_Camera(CURRENT_CAMERA) == m_pCameraCom)
	{

		POINT pt{};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		
		m_fSpeedX += m_fAccelX;
		m_fSpeedY += m_fAccelY;
		
		
		
		_float fDirX = (pt.x-g_iWinCX*0.5f) - m_vCurPos.x;
		_float fDirY = (pt.y-g_iWinCY*0.5f) - m_vCurPos.y;
		if (DBL_EPSILON < fabs(fDirX))
		{
			m_fAccelX = fDirX / (72.f * 150.f);
			m_fSpeedX = fDirX / 72.f;
		}
		else
		{
			m_fAccelX = m_fSpeedX = 0.f;
		}
		if (DBL_EPSILON < fabs(fDirY))
		{
			m_fAccelY = fDirY / (72.f * 150.f);
			m_fSpeedY = fDirY / 72.f;
		}
		else
		{
			m_fAccelY = m_fSpeedY = 0.f;
		}
		
		


		if (g_iWinCX*0.5f > fabs(m_vCurPos.x + m_fSpeedX) && DBL_EPSILON < fabs(m_vCurPos.x + m_fSpeedX) &&
			g_iWinCY*0.5f > fabs(m_vCurPos.y + m_fSpeedY) && DBL_EPSILON < fabs(m_vCurPos.y + m_fSpeedY))
		{
			m_vCurPos.x += m_fSpeedX;
			m_vCurPos.y += m_fSpeedY;
		}

		vPos += vRight*m_vCurPos.x*0.01f;
		vPos -= vUp*m_vCurPos.y*0.01f;

		D3DXMATRIX	matRotation;
		_float fRadian = m_vCurPos.x * 0.001f;
		if (D3DXToRadian(30.f) < fabs(fRadian))
		{
			if (0.f < fRadian)
				fRadian = D3DXToRadian(30.f);
			else if( 0.f > fRadian)
				fRadian = -1.f*D3DXToRadian(30.f);
		}
		//비행체 기울어짐 연출 위해서
		D3DXMatrixRotationAxis(&matRotation, &vLook, fRadian);

		D3DXVec3TransformNormal(&vUp, &vUp, &matRotation);
		D3DXVec3Cross(&vRight, &vUp, &vLook);

		
		m_ptPrePos = pt;

	}
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, vLook);
	m_pTransformCom->Set_State(CTransform::STATE_UP, vUp);
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, vRight);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPos);
	m_pTransformCom->Update_WorldMatrix();
}

void CCam_TPS::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
	
}

HRESULT CCam_TPS::Render()
{
	__super::Render();

	return S_OK;
}

CCam_TPS* CCam_TPS::Create()
{
	CREATE_PIPELINE(CCam_TPS);
}

CGameObject* CCam_TPS::Clone(void* pArg)
{
	CLONE_PIPELINE(CCam_TPS);
}

void CCam_TPS::Free()
{
	__super::Free();

	delete this;
}

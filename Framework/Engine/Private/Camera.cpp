#include "Camera.h"
#include "GameInstance.h"
#include "Engine_Macro.h"
#include "Math_Utillity.h"

CCamera::CCamera(const CCamera& Prototype)
{
	*this = Prototype;
}

HRESULT CCamera::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCamera::Initialize(void* pArg)
{
	return S_OK;
}

void CCamera::Set_Param(_float _fFovy, _float _fAspect, _float _fNear, _float _fFar)
{
	m_CamDesc.fFovy = _fFovy;
	m_CamDesc.fAspect = _fAspect;
	m_CamDesc.fNear = _fNear;
	m_CamDesc.fFar = _fFar;
}

_float4x4 CCamera::Get_CameraWorldMat()
{		
	return m_pTransform->Get_WorldMatrix();
}

void CCamera::Link_TransformCom(CTransform* _pTransform)
{
	m_pTransform = _pTransform;
	m_pTransform->Set_WeakPtr(&m_pTransform);
}

void CCamera::Set_Target(CTransform* _pTransform)
{
	m_pTarget_Transform = _pTransform;

	if(m_pTarget_Transform)
		m_pTarget_Transform->Set_WeakPtr(&m_pTarget_Transform);
}

HRESULT CCamera::Bind_PipeLine()
{
	ISVALID(m_pTransform, E_FAIL);

	
	_float4x4		WorldMatrix = Get_CameraWorldMat();
	_float4x4		ViewMatrix;

	if (m_fOffset)
	{
		Shake();
		*(_float3*)&WorldMatrix.m[3] += m_vOffSetDir;
	}

	D3DXMatrixInverse(&ViewMatrix, nullptr, &WorldMatrix);
	DEVICE->SetTransform(D3DTS_VIEW, &ViewMatrix);

	_float4x4		ProjMatrix;

	D3DXMatrixPerspectiveFovLH(&ProjMatrix, m_CamDesc.fFovy, m_CamDesc.fAspect, m_CamDesc.fNear, m_CamDesc.fFar);
	DEVICE->SetTransform(D3DTS_PROJECTION, &ProjMatrix);

	return S_OK;
}

void CCamera::Add_Shaking(_float _fOffset, _float _fInclination)
{
	if (_fOffset * _fInclination < m_fInclination)
		return;

	m_fOffset = _fOffset;
	m_fInclination = _fOffset * _fInclination;

}

void CCamera::Shake()
{
	m_vOffSetDir = _float3(0.f, 0.f, 0.f);
	_float3 vShakeDir;
	RandomVec(&vShakeDir, -1.f, 1.f);
	D3DXVec3Normalize(&vShakeDir, &vShakeDir);

	m_vOffSetDir += m_fOffset * vShakeDir;

	
	m_fOffset -= m_fInclination;
	if (DBL_EPSILON > m_fOffset)
	{
		m_fOffset = 0.f;
		m_fInclination = 0.f;
		return;
	}
}


void CCamera::RandomVec(_float3* _vDir, float _flowBound, float _fHighBound)
{
	if (_flowBound > _fHighBound)
	{
		float fTemp = _flowBound;
		_flowBound = _fHighBound;
		_fHighBound = fTemp;
	}
	float fX = (rand() % 10000) * 0.0001f;
	float fY = (rand() % 10000) * 0.0001f;
	float fZ = (rand() % 10000) * 0.0001f;

	_vDir->x = (fX * (_fHighBound - _flowBound)) + _flowBound;
	_vDir->y = (fY * (_fHighBound - _flowBound)) + _flowBound;
	_vDir->z = (fZ * (_fHighBound - _flowBound)) + _flowBound;
}

CCamera* CCamera::Create()
{
	CREATE_PIPELINE(CCamera);
}

CComponent* CCamera::Clone(void* pArg)
{
	CLONE_PIPELINE(CCamera);
}

void CCamera::Free()
{
	__super::Free();

	if(m_pTransform)
		m_pTransform->Return_WeakPtr(&m_pTransform);

	delete this;
}

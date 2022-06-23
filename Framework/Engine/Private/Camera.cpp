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
	_float4x4		TargetMatrix = m_pTarget_Transform ?
		CMath_Utillity::Get_Position_Matrix(m_pTarget_Transform->Get_WorldMatrix())
		: *D3DXMatrixIdentity(&TargetMatrix);


	_float4x4		WorldMatrix = m_pTransform->Get_WorldMatrix() * TargetMatrix;
	


	return WorldMatrix;
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

	D3DXMatrixInverse(&ViewMatrix, nullptr, &WorldMatrix);
	DEVICE->SetTransform(D3DTS_VIEW, &ViewMatrix);

	_float4x4		ProjMatrix;

	D3DXMatrixPerspectiveFovLH(&ProjMatrix, m_CamDesc.fFovy, m_CamDesc.fAspect, m_CamDesc.fNear, m_CamDesc.fFar);
	DEVICE->SetTransform(D3DTS_PROJECTION, &ProjMatrix);

	return S_OK;
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

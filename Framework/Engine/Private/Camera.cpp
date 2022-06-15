#include "Camera.h"
#include "GameInstance.h"
#include "Engine_Macro.h"

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

void CCamera::Link_TransformCom(CTransform* _pTransform)
{
	m_pTransfrom = _pTransform;
	m_pTransfrom->Set_WeakPtr(&m_pTransfrom);
}

HRESULT CCamera::Bind_PipeLine()
{
	ISVALID(m_pTransfrom, E_FAIL);

	_float4x4		WorldMatrix = m_pTransfrom->Get_WorldMatrix();
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

	if(m_pTransfrom)
		m_pTransfrom->Return_WeakPtr(&m_pTransfrom);

	delete this;
}

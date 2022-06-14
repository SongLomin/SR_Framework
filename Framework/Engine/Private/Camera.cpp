#include "Camera.h"
#include "GameInstance.h"

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

void CCamera::Set_Transform(CTransform* _pTransform)
{
	m_pTransfrom = _pTransform;
	m_pTransfrom->Set_WeakPtr(&m_pTransfrom);
}

CCamera* CCamera::Create()
{
	CCamera* pInstance = new CCamera();

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Cloned : CCamera");
		//Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CCamera::Clone(void* pArg)
{
	CCamera* pInstance = new CCamera();

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CCamera");
		//Safe_Release(pInstance);
	}

	return pInstance;
}

void CCamera::Free()
{
	__super::Free();

	delete this;
}

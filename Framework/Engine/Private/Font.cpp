#include "Font.h"

CFont::CFont()
{
}

HRESULT CFont::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CFont::Initialize(void* pArg)
{
	return S_OK;
}

CFont* CFont::Create()
{
	CFont* pInstance = new CFont();

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CFont");
		//Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CFont::Clone(void* pArg)
{
	CFont* pInstance = new CFont();

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CFont");
		//Safe_Release(pInstance);
	}

	return pInstance;
}

void CFont::Free()
{
	__super::Free();
}

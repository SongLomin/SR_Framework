#include "Font.h"

CFont::CFont()
{
}

HRESULT CFont::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CFont::Initialize(TEXTINFO* TextInfo, _float CountTime)
{

	m_fCountTime = CountTime;

	memcpy(&m_tTextInfo, TextInfo, sizeof(TEXTINFO));
	

	return S_OK;
}



CFont* CFont::Create(TEXTINFO* TextInfo, _float CountTime)
{
	CFont* pInstance = new CFont();

	if (FAILED(pInstance->Initialize(TextInfo, CountTime)))
	{
		MSG_BOX("Failed to Created : CFont");
		//Safe_Release(pInstance);
	}

	return pInstance;
}



void CFont::Free()
{
	__super::Free();

	delete this;
}

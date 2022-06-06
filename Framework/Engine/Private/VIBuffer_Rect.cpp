#include "..\Public\VIBuffer_Rect.h"

CVIBuffer_Rect::CVIBuffer_Rect(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CVIBuffer(pGraphic_Device)
{
}

CVIBuffer_Rect::CVIBuffer_Rect(const CVIBuffer_Rect & Prototype)
	: CVIBuffer(Prototype)
{
}

HRESULT CVIBuffer_Rect::Initialize_Prototype()
{
	m_iStride = sizeof(VTXTEX);
	m_iNumVertices = 6;
	m_dwFVF = D3DFVF_XYZ | D3DFVF_TEX1; /* | D3DFVF_TEXCOORDSIZE2(0) */
	
	/* 정점배열이 할당된다. */
	if (FAILED(__super::Create_VertexBuffer()))
		return E_FAIL;

	VTXTEX*			pVertices = nullptr;

	/*void**		pData = (void**)&pVertices;*/

	m_pVB->Lock(0, m_iStride * m_iNumVertices, (void**)&pVertices, 0);

	//pVertices[0].vPosition = ;
	//pVertices[0].vTexUV = ;
	
	m_pVB->Unlock();

	return S_OK;
}

HRESULT CVIBuffer_Rect::Initialize(void * pArg)
{
	return S_OK;
}

CVIBuffer_Rect * CVIBuffer_Rect::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CVIBuffer_Rect*		pInstance = new CVIBuffer_Rect(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CVIBuffer_Rect");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CVIBuffer_Rect::Clone(void * pArg)
{
	return nullptr;
}

void CVIBuffer_Rect::Free()
{
	__super::Free();

}

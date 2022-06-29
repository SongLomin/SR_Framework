#include "..\Public\VIBuffer.h"
#include "GameInstance.h"

CVIBuffer::CVIBuffer()
{
}

CVIBuffer::CVIBuffer(const CVIBuffer & Prototype)
	//: CComponent(Prototype)
	//, m_pVB(Prototype.m_pVB)
	//, m_iStride(Prototype.m_iStride)
	//, m_iNumVertices(Prototype.m_iNumVertices)
	//, m_dwFVF(Prototype.m_dwFVF)
	//, m_iNumPrimitive(Prototype.m_iNumPrimitive)
{
	*this = Prototype;
	//m_pVB
}

HRESULT CVIBuffer::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CVIBuffer::Initialize(void * pArg)
{
	return S_OK;
}

HRESULT CVIBuffer::Render()
{

	if (nullptr == LPDEVICE)
		return E_FAIL;

	if (!Get_Enable())
	{
		return S_OK;
	}
	DEVICE->SetFVF(m_dwFVF);
	DEVICE->SetStreamSource(0, m_pVB, 0, m_iStride);
	DEVICE->SetIndices(m_pIB);
	DEVICE->DrawIndexedPrimitive(m_ePrimitiveType, 0, 0, m_iNumVertices, 0, m_iNumPrimitive);
	
	DEVICE->SetTexture(0, 0);

	return S_OK;
}

HRESULT CVIBuffer::Create_VertexBuffer()
{
	if (nullptr == LPDEVICE)
		return E_FAIL;

	if (FAILED(DEVICE->CreateVertexBuffer(m_iStride * m_iNumVertices, 0, m_dwFVF, D3DPOOL_MANAGED, &m_pVB, nullptr)))
		return E_FAIL;

	return S_OK;
}

HRESULT CVIBuffer::Create_IndexBuffer()
{

	if (FAILED(DEVICE->CreateIndexBuffer(m_iIndicesSizePerPrimitive * m_iNumPrimitive, 0, m_eFormat, D3DPOOL_MANAGED, &m_pIB, nullptr)))
		return E_FAIL;

	return S_OK;
}

void CVIBuffer::Free()
{
	__super::Free();

	Safe_Delete_Array(m_pVerticesPos);
	Safe_Delete_Array(m_pIndices);

	if (m_pVB)
		m_pVB->Release();

	if (m_pIB)
		m_pIB->Release();
}

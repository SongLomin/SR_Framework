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

	//장치에 바인드하는데 여러 버텍스 버퍼를 장치에 바인드할 수 있다.
	//즉, 동일한 파이프라인을 통과하는 버텍스 버퍼들을 묶어서 처리할 수 있다.
	DEVICE->SetStreamSource(0, m_pVB, 0, m_iStride);
	DEVICE->SetFVF(m_dwFVF);
	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_iNumPrimitive);

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

void CVIBuffer::Free()
{
	__super::Free();


}

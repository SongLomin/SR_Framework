#include "..\Public\VIBuffer_Terrain.h"

CVIBuffer_Terrain::CVIBuffer_Terrain(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CVIBuffer(pGraphic_Device)
{
}

CVIBuffer_Terrain::CVIBuffer_Terrain(const CVIBuffer_Terrain & Prototype)
	: CVIBuffer(Prototype)
	, m_iNumVerticesX(Prototype.m_iNumVerticesX)
	, m_iNumVerticesZ(Prototype.m_iNumVerticesZ)
{
}

HRESULT CVIBuffer_Terrain::Initialize_Prototype(_uint iNumVerticesX, _uint iNumVerticesZ)
{
	m_iStride = sizeof(VTXTEX);
	m_iNumVertices = iNumVerticesX * iNumVerticesZ;
	m_dwFVF = D3DFVF_XYZ | D3DFVF_TEX1;
	m_iNumPrimitive = (iNumVerticesX - 1) * (iNumVerticesZ - 1) * 2;
	m_iNumVerticesX = iNumVerticesX;
	m_iNumVerticesZ = iNumVerticesZ;
	
	/* �����迭�� �Ҵ�ȴ�. */
	if (FAILED(__super::Create_VertexBuffer()))
		return E_FAIL;

	VTXTEX*			pVertices = nullptr;

	m_pVB->Lock(0, m_iStride * m_iNumVertices, (void**)&pVertices, 0);

	for (_uint i = 0; i < iNumVerticesZ; ++i)
	{
		for (_uint j = 0; j < iNumVerticesX; ++j)
		{
			_uint iIndex = i * iNumVerticesX + j;

			pVertices[iIndex].vPosition = _float3(j, 0.f, i);
			pVertices[iIndex].vTexUV = _float2(j / (iNumVerticesX - 1.f) * 20.f, i / (iNumVerticesZ - 1.f) * 20.f);
		}
	}	
	
	m_pVB->Unlock();

	m_iIndicesSizePerPrimitive = sizeof(FACEINDICES32);
	m_eFormat = D3DFMT_INDEX32;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;

	if (FAILED(__super::Create_IndexBuffer()))
		return E_FAIL;

	FACEINDICES32*		pIndices = nullptr;

	_uint			iNumFaces = 0;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);

	for (_uint i = 0; i < iNumVerticesZ - 1; ++i)
	{
		for (_uint j = 0; j < iNumVerticesX - 1; ++j)
		{
			_uint	iIndex = i * iNumVerticesX + j;

			_uint	iIndices[] = {
				iIndex + iNumVerticesX, 
				iIndex + iNumVerticesX + 1,
				iIndex + 1, 
				iIndex
			};

			pIndices[iNumFaces]._1 = iIndices[0];
			pIndices[iNumFaces]._2 = iIndices[1];
			pIndices[iNumFaces]._3 = iIndices[2];
			++iNumFaces;

			pIndices[iNumFaces]._1 = iIndices[0];
			pIndices[iNumFaces]._2 = iIndices[2];
			pIndices[iNumFaces]._3 = iIndices[3];
			++iNumFaces;
		}
	}

	m_pIB->Unlock();

	return S_OK;
}

HRESULT CVIBuffer_Terrain::Initialize_Prototype(const _tchar * pHeightMapFilePath)
{
	HANDLE			hFile = CreateFile(pHeightMapFilePath, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (0 == hFile)
		return E_FAIL;

	_ulong			dwByte = 0;

	BITMAPFILEHEADER			fh;
	ReadFile(hFile, &fh, sizeof(BITMAPFILEHEADER), &dwByte, nullptr);

	BITMAPINFOHEADER			ih;
	ReadFile(hFile, &ih, sizeof(BITMAPINFOHEADER), &dwByte, nullptr);

	m_iNumVerticesX = ih.biWidth;
	m_iNumVerticesZ = ih.biHeight;

	_ulong*		pPixel = new _ulong[m_iNumVerticesX * m_iNumVerticesZ];
	ZeroMemory(pPixel, sizeof(_ulong) * m_iNumVerticesX * m_iNumVerticesZ);

	ReadFile(hFile, pPixel, sizeof(_ulong) * m_iNumVerticesX * m_iNumVerticesZ, &dwByte, nullptr);

	CloseHandle(hFile);

	m_iStride = sizeof(VTXTEX);
	m_iNumVertices = m_iNumVerticesX * m_iNumVerticesZ;
	m_dwFVF = D3DFVF_XYZ | D3DFVF_TEX1;
	m_iNumPrimitive = (m_iNumVerticesX - 1) * (m_iNumVerticesZ - 1) * 2;

	/* �����迭�� �Ҵ�ȴ�. */
	if (FAILED(__super::Create_VertexBuffer()))
		return E_FAIL;

	m_pVerticesPos = new _float3[m_iNumVertices];
	VTXTEX*			pVertices = nullptr;

	m_pVB->Lock(0, m_iStride * m_iNumVertices, (void**)&pVertices, 0);

	for (_uint i = 0; i < m_iNumVerticesZ; ++i)
	{
		for (_uint j = 0; j < m_iNumVerticesX; ++j)
		{
			_uint iIndex = i * m_iNumVerticesX + j;

			/*1111 1111 1001 0111 1111 1111 1111 1111
		&   0000 0000 1111 1111 0000 0000 0000 0000
			0000 0000 1001 0111 0000 0000 0000 0000*/
			pVertices[iIndex].vPosition = m_pVerticesPos[iIndex] = _float3(j, (pPixel[iIndex] & 0x000000ff) / 15.f, i);
			pVertices[iIndex].vTexUV = _float2(j / (m_iNumVerticesX - 1.f) * 20.f, i / (m_iNumVerticesZ - 1.f) * 20.f);
		}
	}

	m_pVB->Unlock();

	m_iIndicesSizePerPrimitive = sizeof(FACEINDICES32);
	m_eFormat = D3DFMT_INDEX32;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;

	if (FAILED(__super::Create_IndexBuffer()))
		return E_FAIL;

	m_pIndices = new FACEINDICES32[m_iNumPrimitive];
	FACEINDICES32*		pIndices = nullptr;

	_uint			iNumFaces = 0;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);

	for (_uint i = 0; i < m_iNumVerticesZ - 1; ++i)
	{
		for (_uint j = 0; j < m_iNumVerticesX - 1; ++j)
		{
			_uint	iIndex = i * m_iNumVerticesX + j;

			_uint	iIndices[] = {
				iIndex + m_iNumVerticesX,
				iIndex + m_iNumVerticesX + 1,
				iIndex + 1,
				iIndex
			};

			pIndices[iNumFaces]._1 = iIndices[0];
			pIndices[iNumFaces]._2 = iIndices[1];
			pIndices[iNumFaces]._3 = iIndices[2];
			++iNumFaces;

			pIndices[iNumFaces]._1 = iIndices[0];
			pIndices[iNumFaces]._2 = iIndices[2];
			pIndices[iNumFaces]._3 = iIndices[3];
			++iNumFaces;
		}
	}

	memcpy(m_pIndices, pIndices, sizeof(FACEINDICES32) * m_iNumPrimitive);

	m_pIB->Unlock();

	Safe_Delete_Array(pPixel);

	return S_OK;
}

HRESULT CVIBuffer_Terrain::Initialize(void * pArg)
{
	return S_OK;
}

CVIBuffer_Terrain * CVIBuffer_Terrain::Create(LPDIRECT3DDEVICE9 pGraphic_Device, _uint iNumVerticesX, _uint iNumVerticesZ)
{
	CVIBuffer_Terrain*		pInstance = new CVIBuffer_Terrain(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype(iNumVerticesX, iNumVerticesZ)))
	{
		MSG_BOX("Failed to Created : CVIBuffer_Rect");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CVIBuffer_Terrain * CVIBuffer_Terrain::Create(LPDIRECT3DDEVICE9 pGraphic_Device, const _tchar * pHeightMapFilePath)
{
	CVIBuffer_Terrain*		pInstance = new CVIBuffer_Terrain(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype(pHeightMapFilePath)))
	{
		MSG_BOX("Failed to Created : CVIBuffer_Rect");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CVIBuffer_Terrain::Clone(void * pArg)
{
	CVIBuffer_Terrain*		pInstance = new CVIBuffer_Terrain(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CVIBuffer_Rect");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CVIBuffer_Terrain::Free()
{
	__super::Free();

}

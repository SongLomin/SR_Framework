#pragma once

#include "Component.h"

/* 부모클래스다. */

/* Vertex Buffer, Index Buffer */

BEGIN(Engine)

class ENGINE_DLL CVIBuffer abstract : public CComponent
{
protected:
	CVIBuffer();
	CVIBuffer(const CVIBuffer& Prototype);
	virtual ~CVIBuffer() = default;

public:
	_uint Get_NumPrimitive() const {
		return m_iNumPrimitive;
	}

	const _float3* Get_VerticesPos() const {
		return m_pVerticesPos;
	}

	virtual _uint3 Get_Indices(_uint iIndex) const = 0;


public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Render();

protected:
	LPDIRECT3DVERTEXBUFFER9			m_pVB = nullptr;
	_uint							m_iStride = 0; /* 정점하나의 바이트 크기 .*/
	_uint							m_iNumVertices = 0; /* 정점의 갯수 */
	_ulong							m_dwFVF = 0;
	_uint							m_iNumPrimitive = 0;
	D3DPRIMITIVETYPE				m_ePrimitiveType;
	_float3* m_pVerticesPos = nullptr;

protected:
	LPDIRECT3DINDEXBUFFER9			m_pIB = nullptr;
	_uint							m_iIndicesSizePerPrimitive = 0;
	D3DFORMAT						m_eFormat;
	void* m_pIndices = nullptr;


protected:
	HRESULT Create_VertexBuffer();
	HRESULT Create_IndexBuffer();


public:
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free() override;

};

END
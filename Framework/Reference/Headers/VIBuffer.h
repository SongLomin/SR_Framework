#pragma once

#include "Component.h"

/* 부모클래스다. */

/* Vertex Buffer, Index Buffer */

BEGIN(Engine)

class ENGINE_DLL CVIBuffer abstract : public CComponent
{
protected:
	CVIBuffer(LPDIRECT3DDEVICE9 pGraphic_Device);
	CVIBuffer(const CVIBuffer& Prototype);
	virtual ~CVIBuffer() = default;

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

protected:
	HRESULT Create_VertexBuffer();
	

public:	
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free() override;

};

END
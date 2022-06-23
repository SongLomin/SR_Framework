#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CMesh abstract : public CComponent
{
protected:
	CMesh();
	CMesh(const CMesh& Prototype);
	virtual ~CMesh() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Render_Mesh();

public:
	ID3DXMesh* Get_Mesh();

protected:
	/*메쉬 렌더*/
	ID3DXMesh*		m_pMesh = nullptr;
	_ulong			m_dwNumSubsets = 0;
	vector<LPDIRECT3DBASETEXTURE9>*		m_vTextures = nullptr;
	//vector<D3DXMATERIAL>			m_vMtrl;
	/*메쉬 생성*/
	_uint			m_iNumVertices = 0;
	_uint			m_iNumPrimitive = 0;
	_ulong			m_dwFVF;



protected:
	HRESULT	Create_EmptyMesh();

public:
	virtual	CComponent* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END


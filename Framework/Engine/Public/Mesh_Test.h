#pragma once
#include "Mesh.h"

BEGIN(Engine)

class ENGINE_DLL CMesh_Test :
    public CMesh
{
protected:
	CMesh_Test();
	CMesh_Test(const CMesh_Test& Prototype);
	virtual ~CMesh_Test() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Render_Mesh() override;

private:
	LPD3DXBUFFER	m_pAdj = nullptr;
	LPD3DXBUFFER	m_pMtrl = nullptr;
	LPD3DXBUFFER	m_pEffectInstances = nullptr;
	DWORD			m_iNumMtrl = 0;

public:
	static CMesh_Test* Create();
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;

};

END

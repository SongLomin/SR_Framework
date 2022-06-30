#pragma once
#include "Mesh.h"

BEGIN(Engine)

class ENGINE_DLL CMesh_Sphere : public CMesh
{
protected:
	CMesh_Sphere();
	CMesh_Sphere(const CMesh_Sphere& Prototype);
	virtual ~CMesh_Sphere() = default;

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
	static CMesh_Sphere* Create();
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;

};

END


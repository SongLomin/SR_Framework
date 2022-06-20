#pragma once
#include "Mesh.h"

BEGIN(Engine)

class ENGINE_DLL CMesh_Terrain final : public CMesh
{
protected:
	CMesh_Terrain();
	CMesh_Terrain(const CMesh_Terrain& Prototype);
	virtual ~CMesh_Terrain() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);

public:
	static CMesh_Terrain* Create();
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;

private:
	_point m_Terrain_Count;

private:
	void Bake_Terrain_Mesh();
};

END

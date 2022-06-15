#pragma once
#include "Mesh.h"

BEGIN(Engine)

class ENGINE_DLL CMesh_Cube final : public CMesh
{
protected:
	CMesh_Cube();
	CMesh_Cube(const CMesh_Cube& Prototype);
	virtual ~CMesh_Cube() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);

public:
	static CMesh_Cube* Create();
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END


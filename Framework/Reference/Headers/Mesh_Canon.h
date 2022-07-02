#pragma once
#include "Mesh.h"

BEGIN(Engine)

class ENGINE_DLL CMesh_Canon final : public CMesh
{
protected:
	CMesh_Canon();
	CMesh_Canon(const CMesh_Canon& Prototype);
	virtual ~CMesh_Canon() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Render_Mesh() override;

public:
	static CMesh_Canon* Create();
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END

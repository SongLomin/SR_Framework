#pragma once
#include "Mesh.h"

BEGIN(Engine)

class ENGINE_DLL CMesh_Lazer final : public CMesh
{
protected:
	CMesh_Lazer();
	CMesh_Lazer(const CMesh_Lazer& Prototype);
	virtual ~CMesh_Lazer() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Render_Mesh() override;

public:
	static CMesh_Lazer* Create();
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END
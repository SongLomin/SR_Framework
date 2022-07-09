#pragma once
#include "Mesh.h"

BEGIN(Engine)

class ENGINE_DLL CMesh_Ship6 final : public CMesh
{
protected:
	CMesh_Ship6();
	CMesh_Ship6(const CMesh_Ship6& Prototype);
	virtual ~CMesh_Ship6() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Render_Mesh() override;

public:
	static CMesh_Ship6* Create();
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END
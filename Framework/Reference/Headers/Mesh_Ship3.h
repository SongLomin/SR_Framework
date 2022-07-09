#pragma once
#include "Mesh.h"

BEGIN(Engine)

class ENGINE_DLL CMesh_Ship3 final : public CMesh
{
protected:
	CMesh_Ship3();
	CMesh_Ship3(const CMesh_Ship3& Prototype);
	virtual ~CMesh_Ship3() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Render_Mesh() override;

public:
	static CMesh_Ship3* Create();
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END

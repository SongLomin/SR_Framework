#pragma once
#include "Mesh.h"

BEGIN(Engine)

class ENGINE_DLL CMesh_Ship2 final : public CMesh
{
protected:
	CMesh_Ship2();
	CMesh_Ship2(const CMesh_Ship2& Prototype);
	virtual ~CMesh_Ship2() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Render_Mesh() override;

public:
	static CMesh_Ship2* Create();
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END

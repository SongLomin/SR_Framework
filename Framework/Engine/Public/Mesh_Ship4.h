#pragma once
#include "Mesh.h"

BEGIN(Engine)

class ENGINE_DLL CMesh_Ship4 final : public CMesh
{
protected:
	CMesh_Ship4();
	CMesh_Ship4(const CMesh_Ship4& Prototype);
	virtual ~CMesh_Ship4() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Render_Mesh() override;

public:
	static CMesh_Ship4* Create();
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END

#pragma once
#include "Mesh.h"

BEGIN(Engine)

class ENGINE_DLL CMesh_Ship5 final : public CMesh
{
protected:
	CMesh_Ship5();
	CMesh_Ship5(const CMesh_Ship5& Prototype);
	virtual ~CMesh_Ship5() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Render_Mesh() override;

public:
	static CMesh_Ship5* Create();
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END


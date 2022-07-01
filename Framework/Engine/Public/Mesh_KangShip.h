#pragma once
#include "Mesh.h"

BEGIN(Engine)

class ENGINE_DLL CMesh_KangShip final : public CMesh
{
protected:
	CMesh_KangShip();
	CMesh_KangShip(const CMesh_KangShip& Prototype);
	virtual ~CMesh_KangShip() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Render_Mesh() override;

public:
	static CMesh_KangShip* Create();
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END


#pragma once
#include "Mesh.h"

BEGIN(Engine)

class ENGINE_DLL CMesh_HongShip final : public CMesh
{
protected:
	CMesh_HongShip();
	CMesh_HongShip(const CMesh_HongShip& Prototype);
	virtual ~CMesh_HongShip() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Render_Mesh() override;

public:
	static CMesh_HongShip* Create();
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END


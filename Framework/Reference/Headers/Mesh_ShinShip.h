#pragma once
#include "Mesh.h"

BEGIN(Engine)

class ENGINE_DLL CMesh_ShinShip final : public CMesh
{
protected:
	CMesh_ShinShip();
	CMesh_ShinShip(const CMesh_ShinShip& Prototype);
	virtual ~CMesh_ShinShip() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Render_Mesh() override;

public:
	static CMesh_ShinShip* Create();
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END


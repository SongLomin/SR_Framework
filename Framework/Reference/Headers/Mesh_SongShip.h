#pragma once
#include "Mesh.h"

BEGIN(Engine)

class ENGINE_DLL CMesh_SongShip final : public CMesh
{
protected:
	CMesh_SongShip();
	CMesh_SongShip(const CMesh_SongShip& Prototype);
	virtual ~CMesh_SongShip() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Render_Mesh() override;

public:
	static CMesh_SongShip* Create();
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END


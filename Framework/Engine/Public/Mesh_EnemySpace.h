#pragma once
#include "Mesh.h"

BEGIN(Engine)

class ENGINE_DLL CMesh_EnemySpace final : public CMesh
{
protected:
	CMesh_EnemySpace();
	CMesh_EnemySpace(const CMesh_EnemySpace& Prototype);
	virtual ~CMesh_EnemySpace() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Render_Mesh() override;

public:
	static CMesh_EnemySpace* Create();
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END


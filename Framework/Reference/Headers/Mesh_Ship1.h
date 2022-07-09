#pragma once
#include "Mesh.h"

/* 거꾸로 되있음 디테일 좀 높음*/

BEGIN(Engine)

class ENGINE_DLL CMesh_Ship1 final : public CMesh
{
protected:
	CMesh_Ship1();
	CMesh_Ship1(const CMesh_Ship1& Prototype);
	virtual ~CMesh_Ship1() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Render_Mesh() override;

public:
	static CMesh_Ship1* Create();
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END


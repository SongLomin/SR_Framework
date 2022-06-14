#pragma once
#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Terrain final : public CVIBuffer
{
private:
	CVIBuffer_Terrain() = default;
	CVIBuffer_Terrain(const CVIBuffer_Terrain & Prototype);
	virtual ~CVIBuffer_Terrain() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);

public:
	static CVIBuffer_Terrain* Create();
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;

private:
	_point m_Terrain_Count;
	
private:
	void Bake_Terrain_Mesh();
};

END
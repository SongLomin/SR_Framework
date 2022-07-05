#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CVIBuffer_Cube;
class CMesh_Cube;
END

BEGIN(Client)

class CSelectPlanet_SkyBox final : public CGameObject
{
private:
	CSelectPlanet_SkyBox();
	CSelectPlanet_SkyBox(const CSelectPlanet_SkyBox& Prototype);
	virtual ~CSelectPlanet_SkyBox() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render_Begin(ID3DXEffect** Shader) override;
	virtual HRESULT Render
	() override;

private:
	CRenderer* m_pRendererCom = nullptr;
	CTransform* m_pTransformCom = nullptr;
	//CVIBuffer_Cube* m_pVIBufferCom = nullptr;
	CMesh_Cube* m_pMeshCom = nullptr;


private:
	HRESULT SetUp_Components();

public:
	static CSelectPlanet_SkyBox* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END


#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CMesh_Cube;
END

BEGIN(Client)

class CSkyBox abstract : public CGameObject
{
protected:
	CSkyBox();
	virtual ~CSkyBox() = default;

public:
	virtual HRESULT Initialize_Prototype() final;
	virtual HRESULT Initialize(void* pArg) PURE;
	virtual void Tick(_float fTimeDelta) final;
	virtual void LateTick(_float fTimeDelta) final;
	virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) final;
	virtual HRESULT Render() final;

private:
	CRenderer* m_pRendererCom = nullptr;
	CTransform* m_pTransformCom = nullptr;
	CMesh_Cube* m_pMeshCom = nullptr;

	_uint m_iTextureNumber;

protected:
	HRESULT SetUp_Components();
	virtual void SetUp_For_Child() PURE;
	virtual void SetUp_Varialbes_For_Child(_uint TextureIndex);

public:
	virtual void Free() override;
};

END
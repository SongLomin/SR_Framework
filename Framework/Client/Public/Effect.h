#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CTransform;
class CRenderer;
END

BEGIN(Client)

class CEffect abstract : public CGameObject
{
protected:
	CEffect();
	virtual ~CEffect() = default;


public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg)override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) override;
	virtual HRESULT Render() override;

public:
	void Set_Pos(_float3 _Pos);


protected:
	CTransform* m_pTransformCom = nullptr;
	CRenderer* m_pRendererCom = nullptr;


protected:
	_uint	m_iTexture_Min = 0;
	_uint	m_iTexture_Max = 0;
	_float  m_fRadian = 0.f;
	
protected:
	virtual void LookAtCamera();

protected:
	HRESULT SetUp_Components();
	virtual void SetUp_Components_For_Child() PURE;

public:
	virtual void Free() override;
};

END
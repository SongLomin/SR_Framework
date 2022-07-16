#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CTransform;
class CRenderer;
class CVIBuffer_Rect;
END


BEGIN(Client)

class CTrajectory final : public CGameObject
{
private:
	CTrajectory() = default;
	virtual ~CTrajectory() = default;
	CTrajectory(const CTrajectory& Prototype);

protected:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) override;
	virtual HRESULT Render() override;

private:
	void SetUp_Components();

private:
	CTransform* m_pTransformCom = nullptr;
	CRenderer* m_pRendererCom = nullptr;
	CVIBuffer_Rect* m_pVIBufferCom = nullptr;

private:
	ID3DXEffect** m_ppShader = nullptr;

public:
	static CTrajectory* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

	
	
};

END
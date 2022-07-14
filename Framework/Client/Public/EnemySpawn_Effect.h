#pragma once
#include "Effect.h"
#include "Client_Defines.h"

BEGIN(Engine)
class CVIBuffer_Rect;
END

BEGIN(Client)

class CEnemySpawn_Effect final : public CEffect
{
private:
	CEnemySpawn_Effect();
	CEnemySpawn_Effect(const CEnemySpawn_Effect& Prototype);
	virtual ~CEnemySpawn_Effect() = default;


public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg)override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) override;
	virtual HRESULT Render() override;


private:
	CVIBuffer_Rect* m_pVIBufferCom = nullptr;

private:
	_float m_fTime = 2.f;


public:
	virtual void SetUp_Components_For_Child();

public:
	static CEnemySpawn_Effect* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END
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

	CTransform* m_pTargetTransform = nullptr;
	CTrajectory* m_pBackNodeTrajectoryObject = nullptr;

	_float	m_fUpdateTime = 1.f;

	_float3 m_vScale = _float3(0.15f, 1.4f, 0.15f);
	_float3 m_vOffset;
	_float m_fMovement;

	_bool m_bDraw = false;
	_float m_fAlpha = 0.6f;

public:
	void Set_BackNode(CTrajectory* _pTrajectoryObject);
	void Set_LocalMatrix_WithOutScale(const _float4x4& _LocalMat, _bool _bDraw, _float _fAlpha);
	void Make_TrajectoryNode(const _uint& _iNodeCnt, CTransform* _pTargetTransform, const _float3& _vOffset = { 0.f, 0.f, 0.f });
	void Set_Dead_AllTrajectory();
	void Set_Draw(_bool _bDraw) { m_bDraw = _bDraw; }
	void Set_Alpha(_float _fAlpha) { m_fAlpha = _fAlpha; }


protected:
	virtual void OnEnable(void* _Arg) override;

public:
	static CTrajectory* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

	
	
};

END
#pragma once

#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CCamera abstract : public CGameObject
{
public:
	typedef struct CameraDesc
	{
		_uint		iLevelIndex;
		_tchar*		pTransformPrototypeTag;

		_float3		vEye;
		_float3		vAt;

		CTransform::TRANSFORMDESC		TransformDesc;

	}CAMERADESC;
private:
	CCamera(LPDIRECT3DDEVICE9 pGraphic_Device);
	CCamera(const CCamera& Prototype);
	virtual ~CCamera() = default;
	
public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();

protected:
	class CTransform*				m_pTransformCom = nullptr;
	CAMERADESC						m_CameraDesc;

	static const _tchar*			m_pTransformComTag;

public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END
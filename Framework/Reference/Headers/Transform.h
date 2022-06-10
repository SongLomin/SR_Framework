#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CTransform final :
    public CComponent
{
public:
	enum STATE { STATE_RIGHT, STATE_UP, STATE_LOOK, STATE_POSITION, STATE_END };

public:
	typedef struct tagTransformDesc
	{
		_float		fSpeedPerSec;
		_float		fRotationPerSec;
	}TRANSFORMDESC;

private:
	CTransform() = default;
	CTransform(const CTransform& Prototype);
	virtual ~CTransform() = default;

public:
	_float3 Get_State(STATE eState) const {
		return *(_float3*)&m_WorldMatrix.m[eState][0];
	}

	void Set_State(STATE eState, const _float3 & vState) {
		memcpy(&m_WorldMatrix.m[eState][0], &vState, sizeof(_float3));
	}

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);

public:
	HRESULT Bind_WorldMatrix();
	_float4x4 Get_WorldMatrix() const;

public:
	void Go_Straight(_float fTimeDelta);
	void Go_Left(_float fTimeDelta);
	void Go_Right(_float fTimeDelta);
	void Go_Backward(_float fTimeDelta);
	void Go_Target(CTransform* _Trans, _float fTimeDelta);

	void Rotation(const _float3 & vAxis, _float fRadian);
	void Turn(const _float3 & vAxis, _float fTimeDelta);

private:
	_float4x4			m_WorldMatrix;
	TRANSFORMDESC		m_TransformDesc;

public:
	void Set_Parent(CTransform* _pParent);
	void Add_Child(CTransform* _pChild);

private:
	CTransform*		m_pParent = nullptr;
	list<CTransform*>	m_pChildren;

public:
	static CTransform* Create();
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END
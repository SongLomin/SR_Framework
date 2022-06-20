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
		_float		fSpeedPerSec = 5.f;
		_float		fRotationPerSec = D3DXToRadian(90.0f);;
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

	_float3 Get_Scaled() {
		return _float3(D3DXVec3Length(&Get_State(STATE_RIGHT)),
			D3DXVec3Length(&Get_State(STATE_UP)),
			D3DXVec3Length(&Get_State(STATE_LOOK)));
	}

	void Set_Desc(_float fSpeed, _float fRadSpeed)
	{
		m_TransformDesc.fSpeedPerSec = fSpeed;
		m_TransformDesc.fRotationPerSec = fRadSpeed;
	}

	_float Get_Speed() {	return m_TransformDesc.fSpeedPerSec;}
	_float Get_RotationSpeed() { return m_TransformDesc.fRotationPerSec; }

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);

public:
	HRESULT Bind_WorldMatrix();
	_float4x4 Get_WorldMatrix() const;

public:
	/*void Go_Straight(_float fTimeDelta);
	void Go_Left(_float fTimeDelta);
	void Go_Right(_float fTimeDelta);
	void Go_Up(_float fJump,_float fTimeDelta);
	void Go_Backward(_float fTimeDelta);*/
	void Go_Target(CTransform* _Trans, _float fTimeDelta);
	void Scaling(_float3 vScale);

	void Go_BackAndForth(_float fSpeed, _float ftimeDelta);
	void Go_SideToSide(_float fSpeed, _float ftimeDelta);
	void Go_UpAndDown(_float fSpeed, _float ftimeDelta);
	
	void Rotation(const _float3 & vAxis, _float fRadian);
	void Turn(const _float3 & vAxis, _float fRadSpeed,_float fTimeDelta);
	void Turn_Look(const _float3& vAxis, _float fTimeDelta);
	
	void Turn_AxisZ(const _float& fRadian, _float fTimeDelta);
	void Turn_AxisY(const _float& fRadian, _float fTimeDelta);

	void LookAt(const _float3& vAt);
	void LookAt(CTransform* pTargetTransform);

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
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

	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	_float3 Get_State(STATE eState, _bool _bWorld = false) const {

		if(_bWorld)
			return *(_float3*)&m_WorldMatrix.m[eState][0];

 		return *(_float3*)&m_LocalMatrix.m[eState][0];
	}

	void Set_State(STATE eState, const _float3 & vState, _bool _bWorld = false) {

		if (_bWorld)
			memcpy(&m_WorldMatrix.m[eState][0], &vState, sizeof(_float3));

		else
			memcpy(&m_LocalMatrix.m[eState][0], &vState, sizeof(_float3));
	}

	_float3 Get_World_State(STATE eState) const {
		return *(_float3*)&m_WorldMatrix.m[eState][0];
	}

	void Set_World_State(STATE eState, const _float3& vState) {
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
	list<CTransform*>* Get_Children();

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);

public:
	_float4x4 Update_WorldMatrix(BYTE MyFlags = D3D_ALL, BYTE ParentFlags = D3D_ALL);

	HRESULT Bind_WorldMatrix(BYTE MyFlags = D3D_ALL, BYTE ParentFlags = D3D_ALL);
	_float4x4 Get_WorldMatrix(BYTE MyFlags = D3D_ALL, BYTE ParentFlags = D3D_ALL);

public:
	void Go_Target(CTransform* _Trans, _float fTimeDelta, _bool _bWorld = false);
	void Scaling(_float3 vScale, _bool _bWorld = false);

	void Go_BackAndForth(_float fSpeed, _float ftimeDelta, _bool _bWorld = false);
	void Go_SideToSide(_float fSpeed, _float ftimeDelta, _bool _bWorld = false);
	void Go_UpAndDown(_float fSpeed, _float ftimeDelta, _bool _bWorld = false);

	void Rotation(const _float3 & vAxis, _float fRadian, _bool _bWorld = false);
	void Turn(const _float3& vAxis, _float fRadSpeed, _float fTimeDelta, _bool _bWorld = false);
	void Turn_Look(const _float3& vAxis, _float fTimeDelta, _bool _bWorld = false);

	void Turn_AxisZ(const _float& fRadian, _float fTimeDelta, _bool _bWorld = false);
	void Turn_AxisY(const _float& fRadian, _float fTimeDelta, _bool _bWorld = false);

	void LookAt(const _float3& vAt, _bool _bWorld = false);
	void LookAt(CTransform* pTargetTransform, _bool _bWorld = false);

	void Chase(CTransform* pTargetTransform, _float fTimeDelta, _float fLimit, _bool _bWorld = false);


private:
	_float4x4			m_WorldMatrix;
	_float4x4			m_LocalMatrix;
	TRANSFORMDESC		m_TransformDesc;

public:
	void Set_Parent(CTransform* _pParent);
	void Add_Child(CTransform* _pChild);
	void Remove_Child(CTransform* _pChild);

private:
	CTransform*		m_pParent = nullptr;
	list<CTransform*>	m_pChildren;

public:
	static CTransform* Create();
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;

};

END
#include "Transform.h"
#include "GameInstance.h"
#include "GameObject.h"

CTransform::CTransform(const CTransform& Prototype)
{
	*this = Prototype;

}

HRESULT CTransform::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	D3DXMatrixIdentity(&m_WorldMatrix);

	return S_OK;
}

HRESULT CTransform::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	if (nullptr != pArg)
		memcpy(&m_TransformDesc, pArg, sizeof(TRANSFORMDESC));

	return S_OK;
}

HRESULT CTransform::Bind_WorldMatrix()
{

	DEVICE->SetTransform(D3DTS_WORLD, &Get_WorldMatrix());

	return S_OK;
}

_float4x4 CTransform::Get_WorldMatrix() const
{
	_float4x4 _matParent;
	D3DXMatrixIdentity(&_matParent);


	if (m_pParent)
	{
		_matParent = m_pParent->Get_WorldMatrix();
	}

	return m_WorldMatrix * _matParent;
}

void CTransform::Go_Straight(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vLook = Get_State(CTransform::STATE_LOOK);

	vPosition += *D3DXVec3Normalize(&vLook, &vLook) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);
}

void CTransform::Go_Left(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vRight = Get_State(CTransform::STATE_RIGHT);

	vPosition -= *D3DXVec3Normalize(&vRight, &vRight) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);
}

void CTransform::Go_Right(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vRight = Get_State(CTransform::STATE_RIGHT);

	vPosition += *D3DXVec3Normalize(&vRight, &vRight) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);
}

void CTransform::Go_Backward(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vLook = Get_State(CTransform::STATE_LOOK);

	vPosition -= *D3DXVec3Normalize(&vLook, &vLook) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);
}

void CTransform::Go_Target(CTransform* _Trans, _float fTimeDelta)
{
	_float3 vPlayerPos = _Trans->Get_State(CTransform::STATE_POSITION);
	_float3 vLook = vPlayerPos - Get_State(CTransform::STATE_POSITION);
	D3DXVec3Normalize(&vLook, &vLook);

	_float3 vRight;
	D3DXVec3Cross(&vRight, &_float3(0.f, 1.f, 0.f), &vLook);

	_float3 vUp;
	D3DXVec3Cross(&vUp, &vLook, &vRight);
	
	Set_State(CTransform::STATE_RIGHT, vRight);
	Set_State(CTransform::STATE_UP, vUp);
	Set_State(CTransform::STATE_LOOK, vLook);

	Go_Straight(fTimeDelta);
}

void CTransform::Rotation(const _float3& vAxis, _float fRadian)
{
	_float3		vRight = _float3(1.f, 0.f, 0.f);
	_float3		vUp = _float3(0.f, 1.f, 0.f);
	_float3		vLook = _float3(0.f, 0.f, 1.f);

	_float4x4	RotationMatrix;
	D3DXMatrixRotationAxis(&RotationMatrix, &vAxis, fRadian);

	D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrix);
	D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrix);
	D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrix);

	Set_State(CTransform::STATE_RIGHT, vRight);
	Set_State(CTransform::STATE_UP, vUp);
	Set_State(CTransform::STATE_LOOK, vLook);


}

void CTransform::Turn(const _float3& vAxis, _float fTimeDelta)
{
	_float3		vRight = Get_State(CTransform::STATE_RIGHT);
	_float3		vUp = Get_State(CTransform::STATE_UP);
	_float3		vLook = Get_State(CTransform::STATE_LOOK);

	_float4x4	RotationMatrix;
	D3DXMatrixRotationAxis(&RotationMatrix, &vAxis, m_TransformDesc.fRotationPerSec * fTimeDelta);

	D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrix);
	D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrix);
	D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrix);

	Set_State(CTransform::STATE_RIGHT, vRight);
	Set_State(CTransform::STATE_UP, vUp);
	Set_State(CTransform::STATE_LOOK, vLook);
}

void CTransform::Set_Parent(CTransform* _pParent)
{
	m_pParent = _pParent;
	m_pParent->Set_WeakPtr(&m_pParent);
}

void CTransform::Add_Child(CTransform* _pChild)
{
	m_pChildren.push_back(_pChild);
	m_pChildren.back()->Set_WeakPtr(&m_pChildren.back());
}

CTransform* CTransform::Create()
{
	CTransform* pInstance = new CTransform();

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CRenderer");
		//Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CTransform::Clone(void* pArg)
{
	CTransform* pInstance = new CTransform(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CTransform");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTransform::Free()
{
	__super::Free();

	delete this;
}
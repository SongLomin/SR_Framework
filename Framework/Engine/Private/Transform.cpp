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

//void CTransform::Go_Straight(_float fTimeDelta)
//{
//	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
//	_float3		vLook = Get_State(CTransform::STATE_LOOK);
//
//	vPosition += *D3DXVec3Normalize(&vLook, &vLook) * m_TransformDesc.fSpeedPerSec * fTimeDelta;
//
//	Set_State(CTransform::STATE_POSITION, vPosition);
//}
//
//void CTransform::Go_Left(_float fTimeDelta)
//{
//	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
//	_float3		vRight = Get_State(CTransform::STATE_RIGHT);
//
//	vPosition -= *D3DXVec3Normalize(&vRight, &vRight) * m_TransformDesc.fSpeedPerSec * fTimeDelta;
//
//	Set_State(CTransform::STATE_POSITION, vPosition);
//}
//
//void CTransform::Go_Right(_float fTimeDelta)
//{
//	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
//	_float3		vRight = Get_State(CTransform::STATE_RIGHT);
//
//	vPosition += *D3DXVec3Normalize(&vRight, &vRight) * m_TransformDesc.fSpeedPerSec * fTimeDelta;
//
//	Set_State(CTransform::STATE_POSITION, vPosition);
//}
//
//void CTransform::Go_Up(_float fJump,_float fTimeDelta)
//{
//	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
//	_float3		vUp = Get_State(CTransform::STATE_UP);
//
//	vPosition += *D3DXVec3Normalize(&vUp, &vUp) * fJump * fTimeDelta;
//
//	Set_State(CTransform::STATE_POSITION, vPosition);
//}
//
//void CTransform::Go_Backward(_float fTimeDelta)
//{
//	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
//	_float3		vLook = Get_State(CTransform::STATE_LOOK);
//
//	vPosition -= *D3DXVec3Normalize(&vLook, &vLook) * m_TransformDesc.fSpeedPerSec * fTimeDelta;
//
//	Set_State(CTransform::STATE_POSITION, vPosition);
//}
//
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

	
}

void CTransform::Scaling(_float3 vScale)
{
	//Get_Scaled();


	_float3		vRight = Get_State(CTransform::STATE_RIGHT);
	_float3		vUp = Get_State(CTransform::STATE_UP);
	_float3		vLook = Get_State(CTransform::STATE_LOOK);

	Set_State(CTransform::STATE_RIGHT, *D3DXVec3Normalize(&vRight, &vRight) * vScale.x);
	Set_State(CTransform::STATE_UP, *D3DXVec3Normalize(&vUp, &vUp) * vScale.y);
	Set_State(CTransform::STATE_LOOK, *D3DXVec3Normalize(&vLook, &vLook) * vScale.z);
}

void CTransform::Go_BackAndForth(_float fSpeed, _float ftimeDelta)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vLook = Get_State(CTransform::STATE_LOOK);

	vPosition += *D3DXVec3Normalize(&vLook, &vLook) * fSpeed * ftimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);
}

void CTransform::Go_SideToSide(_float fSpeed, _float ftimeDelta)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vRight = Get_State(CTransform::STATE_RIGHT);

	vPosition += *D3DXVec3Normalize(&vRight, &vRight) * fSpeed * ftimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);
}

void CTransform::Go_UpAndDown(_float fSpeed, _float ftimeDelta)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vUp = Get_State(CTransform::STATE_UP);

	vPosition += *D3DXVec3Normalize(&vUp, &vUp) * fSpeed * ftimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);
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

void CTransform::Turn(const _float3& vAxis, _float fRadSpeed,_float fTimeDelta)
{
	_float3		vRight = Get_State(CTransform::STATE_RIGHT);
	_float3		vUp = Get_State(CTransform::STATE_UP);
	_float3		vLook = Get_State(CTransform::STATE_LOOK);

	_float4x4	RotationMatrix;
	D3DXMatrixRotationAxis(&RotationMatrix, &vAxis, fRadSpeed * fTimeDelta);

	D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrix);
	D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrix);
	D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrix);

	Set_State(CTransform::STATE_RIGHT, vRight);
	Set_State(CTransform::STATE_UP, vUp);
	Set_State(CTransform::STATE_LOOK, vLook);
}

void CTransform::Turn_Look(const _float3& vAxis, _float fTimeDelta)
{
	_float3		vLook = Get_State(CTransform::STATE_LOOK);

	_float4x4	RotationMatrix;
	D3DXMatrixRotationAxis(&RotationMatrix, &vAxis, m_TransformDesc.fRotationPerSec * fTimeDelta);
	D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrix);

	_float3 vRight;
	D3DXVec3Cross(&vRight, &_float3(0.f, 1.f, 0.f), &vLook);

	_float3 vUp;
	D3DXVec3Cross(&vUp, &vLook, &vRight);

	Set_State(CTransform::STATE_RIGHT, vRight);
	Set_State(CTransform::STATE_UP, vUp);
	Set_State(CTransform::STATE_LOOK, vLook);
}

void CTransform::Turn_AxisZ(const _float & fRadian, _float fTimeDelta)
{
	_float3 vUp = _float3(0.f, 1.f, 0.f);
	_float3 vLook = Get_State(CTransform::STATE_LOOK);
	_float3 vRight = Get_State(CTransform::STATE_RIGHT);
	_float4x4	matRotation;

	D3DXMatrixRotationAxis(&matRotation, &vLook, fRadian);
	
	D3DXVec3TransformNormal(&vUp, &vUp, &matRotation);
	D3DXVec3Cross(&vRight, &vUp, &vLook);

	Set_State(CTransform::STATE_RIGHT, vRight);
	Set_State(CTransform::STATE_UP, vUp);
	Set_State(CTransform::STATE_LOOK, vLook);

}

void CTransform::Turn_AxisY(const _float & fRadian, _float fTimeDelta)
{
	_float3 vUp = _float3(0.f, 1.f, 0.f);
	_float3 vLook = Get_State(CTransform::STATE_LOOK);
	_float3 vRight = Get_State(CTransform::STATE_RIGHT);
	_float4x4	matRotation;

	D3DXMatrixRotationAxis(&matRotation, &vUp, fRadian*fTimeDelta);

	D3DXVec3TransformNormal(&vLook, &vLook, &matRotation);
	D3DXVec3Cross(&vRight, &vUp, &vLook);
	D3DXVec3Cross(&vUp, &vLook, &vRight);

	Set_State(CTransform::STATE_RIGHT, vRight);
	Set_State(CTransform::STATE_UP, vUp);
	Set_State(CTransform::STATE_LOOK, vLook);
}

void CTransform::LookAt(const _float3& vAt)
{
	_float3		vScale = Get_Scaled();

	_float3		vPosition = Get_State(CTransform::STATE_POSITION);

	_float3		vLook = vAt - vPosition;
	_float3		vRight = *D3DXVec3Cross(&vRight, &_float3(0.f, 1.f, 0.f), &vLook);
	_float3		vUp = *D3DXVec3Cross(&vUp, &vLook, &vRight);

	vRight = *D3DXVec3Normalize(&vRight, &vRight) * vScale.x;
	vUp = *D3DXVec3Normalize(&vUp, &vUp) * vScale.y;
	vLook = *D3DXVec3Normalize(&vLook, &vLook) * vScale.z;

	Set_State(CTransform::STATE_RIGHT, vRight);
	Set_State(CTransform::STATE_UP, vUp);
	Set_State(CTransform::STATE_LOOK, vLook);

}

void CTransform::LookAt(CTransform* pTargetTransform)
{
	_float3		vScale = Get_Scaled();

	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vAt = pTargetTransform->Get_State(CTransform::STATE_POSITION);

	_float3		vLook = vAt - vPosition;
	_float3		vRight = *D3DXVec3Cross(&vRight, &_float3(0.f, 1.f, 0.f), &vLook);
	_float3		vUp = *D3DXVec3Cross(&vUp, &vLook, &vRight);

	vRight = *D3DXVec3Normalize(&vRight, &vRight) * vScale.x;
	vUp = *D3DXVec3Normalize(&vUp, &vUp) * vScale.y;
	vLook = *D3DXVec3Normalize(&vLook, &vLook) * vScale.z;

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
	CREATE_PIPELINE(CTransform);
}

CComponent* CTransform::Clone(void* pArg)
{
	CLONE_PIPELINE(CTransform);
}

void CTransform::Free()
{
	__super::Free();

	delete this;
}
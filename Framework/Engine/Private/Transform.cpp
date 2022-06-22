#include "Transform.h"
#include "GameInstance.h"
#include "GameObject.h"
#include "Math_Utillity.h"

CTransform::CTransform(const CTransform& Prototype)
{
	*this = Prototype;

}

void CTransform::Tick(_float fTimeDelta)
{
	Update_WorldMatrix();
}

void CTransform::LateTick(_float fTimeDelta)
{
}

HRESULT CTransform::Render()
{
	return S_OK;
}

list<CTransform*>* CTransform::Get_Children()
{
	return &m_pChildren;
}

HRESULT CTransform::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	D3DXMatrixIdentity(&m_LocalMatrix);

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

_float4x4 CTransform::Update_WorldMatrix(BYTE MyFlags, BYTE ParentFlags)
{
	_float4x4 _matMySelected;
	D3DXMatrixIdentity(&_matMySelected);

	if (MyFlags & D3D_SCALE)
	{
		_matMySelected *= CMath_Utillity::Get_Scale_Matrix(m_LocalMatrix);
	}

	if (MyFlags & D3D_ROTATE)
	{
		_matMySelected *= CMath_Utillity::Get_Rotation_Matrix(m_LocalMatrix);
	}

	if (MyFlags & D3D_TRANS)
	{
		_matMySelected *= CMath_Utillity::Get_Position_Matrix(m_LocalMatrix);
	}

	_float4x4 _matParent;
	D3DXMatrixIdentity(&_matParent);

	if (m_pParent)
	{
		_matParent = m_pParent->Update_WorldMatrix(ParentFlags, ParentFlags);
	}

	m_WorldMatrix = _matMySelected * _matParent;

	return m_WorldMatrix;
}

HRESULT CTransform::Bind_WorldMatrix(BYTE MyFlags, BYTE ParentFlags)
{

	DEVICE->SetTransform(D3DTS_WORLD, &m_WorldMatrix);

	return S_OK;
}

_float4x4 CTransform::Get_WorldMatrix(BYTE MyFlags, BYTE ParentFlags)
{
	return m_WorldMatrix;
}

void CTransform::Go_Target(CTransform* _Trans, _float fTimeDelta, _bool _bWorld)
{
	_float3 vPlayerPos = _Trans->Get_State(CTransform::STATE_POSITION, _bWorld);
	_float3 vLook = vPlayerPos - Get_State(CTransform::STATE_POSITION, _bWorld);
	D3DXVec3Normalize(&vLook, &vLook);

	_float3 vRight;
	D3DXVec3Cross(&vRight, &_float3(0.f, 1.f, 0.f), &vLook);

	_float3 vUp;
	D3DXVec3Cross(&vUp, &vLook, &vRight);
	
	Set_State(CTransform::STATE_RIGHT, vRight, _bWorld);
	Set_State(CTransform::STATE_UP, vUp, _bWorld);

	//_float fPre_LookS_cale = D3DXVec3Length(&Get_State(CTransform::STATE_LOOK, _bWorld));
	//vLook *= fPre_LookS_cale;

	Set_State(CTransform::STATE_LOOK, vLook, _bWorld);

	
}

void CTransform::Scaling(_float3 vScale, _bool _bWorld)
{
	//Get_Scaled();


	_float3		vRight = Get_State(CTransform::STATE_RIGHT, _bWorld);
	_float3		vUp = Get_State(CTransform::STATE_UP, _bWorld);
	_float3		vLook = Get_State(CTransform::STATE_LOOK, _bWorld);

	Set_State(CTransform::STATE_RIGHT, *D3DXVec3Normalize(&vRight, &vRight) * vScale.x, _bWorld);
	Set_State(CTransform::STATE_UP, *D3DXVec3Normalize(&vUp, &vUp) * vScale.y, _bWorld);
	Set_State(CTransform::STATE_LOOK, *D3DXVec3Normalize(&vLook, &vLook) * vScale.z, _bWorld);
}

void CTransform::Go_BackAndForth(_float fSpeed, _float ftimeDelta, _bool _bWorld)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION, _bWorld);
	_float3		vLook = Get_State(CTransform::STATE_LOOK, _bWorld);

	vPosition += *D3DXVec3Normalize(&vLook, &vLook) * fSpeed * ftimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition, _bWorld);
}

void CTransform::Go_SideToSide(_float fSpeed, _float ftimeDelta, _bool _bWorld)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION, _bWorld);
	_float3		vRight = Get_State(CTransform::STATE_RIGHT, _bWorld);

	vPosition += *D3DXVec3Normalize(&vRight, &vRight) * fSpeed * ftimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition, _bWorld);
}

void CTransform::Go_UpAndDown(_float fSpeed, _float ftimeDelta, _bool _bWorld)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION, _bWorld);
	_float3		vUp = Get_State(CTransform::STATE_UP, _bWorld);

	vPosition += *D3DXVec3Normalize(&vUp, &vUp) * fSpeed * ftimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition, _bWorld);
}


void CTransform::Rotation(const _float3& vAxis, _float fRadian, _bool _bWorld)
{
	_float3		vRight = _float3(1.f, 0.f, 0.f);
	_float3		vUp = _float3(0.f, 1.f, 0.f);
	_float3		vLook = _float3(0.f, 0.f, 1.f);


	_float4x4	RotationMatrix;
	D3DXMatrixRotationAxis(&RotationMatrix, &vAxis, fRadian);

	D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrix);
	D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrix);
	D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrix);


	Set_State(CTransform::STATE_RIGHT, vRight, _bWorld);
	Set_State(CTransform::STATE_UP, vUp, _bWorld);
	Set_State(CTransform::STATE_LOOK, vLook, _bWorld);


}

void CTransform::Turn(const _float3& vAxis, _float fRadSpeed,_float fTimeDelta, _bool _bWorld)
{
	_float3		vRight = Get_State(CTransform::STATE_RIGHT, _bWorld);
	_float3		vUp = Get_State(CTransform::STATE_UP, _bWorld);
	_float3		vLook = Get_State(CTransform::STATE_LOOK, _bWorld);

	_float4x4	RotationMatrix;
	D3DXMatrixRotationAxis(&RotationMatrix, &vAxis, fRadSpeed * fTimeDelta);

	D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrix);
	D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrix);
	D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrix);

	Set_State(CTransform::STATE_RIGHT, vRight, _bWorld);
	Set_State(CTransform::STATE_UP, vUp, _bWorld);
	Set_State(CTransform::STATE_LOOK, vLook, _bWorld);
}

void CTransform::Turn_Look(const _float3& vAxis, _float fTimeDelta, _bool _bWorld)
{
	_float3		vLook = Get_State(CTransform::STATE_LOOK, _bWorld);

	_float4x4	RotationMatrix;
	D3DXMatrixRotationAxis(&RotationMatrix, &vAxis, m_TransformDesc.fRotationPerSec * fTimeDelta);
	D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrix);

	_float3 vRight;
	D3DXVec3Cross(&vRight, &_float3(0.f, 1.f, 0.f), &vLook);

	_float3 vUp;
	D3DXVec3Cross(&vUp, &vLook, &vRight);

	Set_State(CTransform::STATE_RIGHT, vRight, _bWorld);
	Set_State(CTransform::STATE_UP, vUp, _bWorld);
	Set_State(CTransform::STATE_LOOK, vLook, _bWorld);
}

void CTransform::Turn_AxisZ(const _float & fRadian, _float fTimeDelta, _bool _bWorld)
{
	_float3 vUp = _float3(0.f, 1.f, 0.f);
	_float3 vLook = Get_State(CTransform::STATE_LOOK, _bWorld);
	_float3 vRight = Get_State(CTransform::STATE_RIGHT, _bWorld);
	_float4x4	matRotation;

	D3DXMatrixRotationAxis(&matRotation, &vLook, fRadian);
	
	D3DXVec3TransformNormal(&vUp, &vUp, &matRotation);
	D3DXVec3Cross(&vRight, &vUp, &vLook);

	Set_State(CTransform::STATE_RIGHT, vRight, _bWorld);
	Set_State(CTransform::STATE_UP, vUp, _bWorld);
	Set_State(CTransform::STATE_LOOK, vLook, _bWorld);

}

void CTransform::Turn_AxisY(const _float & fRadian, _float fTimeDelta, _bool _bWorld)
{
	_float3 vUp = _float3(0.f, 1.f, 0.f);
	_float3 vLook = Get_State(CTransform::STATE_LOOK, _bWorld);
	_float3 vRight = Get_State(CTransform::STATE_RIGHT, _bWorld);
	_float4x4	matRotation;

	D3DXMatrixRotationAxis(&matRotation, &vUp, fRadian*fTimeDelta);

	D3DXVec3TransformNormal(&vLook, &vLook, &matRotation);
	D3DXVec3Cross(&vRight, &vUp, &vLook);
	D3DXVec3Cross(&vUp, &vLook, &vRight);

	Set_State(CTransform::STATE_RIGHT, vRight, _bWorld);
	Set_State(CTransform::STATE_UP, vUp, _bWorld);
	Set_State(CTransform::STATE_LOOK, vLook, _bWorld);
}

void CTransform::LookAt(const _float3& vAt, _bool _bWorld)
{
	_float3		vScale = Get_Scaled();

	_float3		vPosition = Get_State(CTransform::STATE_POSITION, _bWorld);

	_float3		vLook = vAt - vPosition;
	_float3		vRight = *D3DXVec3Cross(&vRight, &_float3(0.f, 1.f, 0.f), &vLook);
	_float3		vUp = *D3DXVec3Cross(&vUp, &vLook, &vRight);

	vRight = *D3DXVec3Normalize(&vRight, &vRight) * vScale.x;
	vUp = *D3DXVec3Normalize(&vUp, &vUp) * vScale.y;
	vLook = *D3DXVec3Normalize(&vLook, &vLook) * vScale.z;

	Set_State(CTransform::STATE_RIGHT, vRight, _bWorld);
	Set_State(CTransform::STATE_UP, vUp, _bWorld);
	Set_State(CTransform::STATE_LOOK, vLook, _bWorld);

}

void CTransform::LookAt(CTransform* pTargetTransform, _bool _bWorld)
{
	_float3		vScale = Get_Scaled();

	_float3		vPosition = Get_State(CTransform::STATE_POSITION, _bWorld);
	_float3		vAt = pTargetTransform->Get_State(CTransform::STATE_POSITION, _bWorld);

	_float3		vLook = vAt - vPosition;
	_float3		vRight = *D3DXVec3Cross(&vRight, &_float3(0.f, 1.f, 0.f), &vLook);
	_float3		vUp = *D3DXVec3Cross(&vUp, &vLook, &vRight);

	vRight = *D3DXVec3Normalize(&vRight, &vRight) * vScale.x;
	vUp = *D3DXVec3Normalize(&vUp, &vUp) * vScale.y;
	vLook = *D3DXVec3Normalize(&vLook, &vLook) * vScale.z;

	Set_State(CTransform::STATE_RIGHT, vRight, _bWorld);
	Set_State(CTransform::STATE_UP, vUp, _bWorld);
	Set_State(CTransform::STATE_LOOK, vLook, _bWorld);

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



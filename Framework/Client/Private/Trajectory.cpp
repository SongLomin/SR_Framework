#include "stdafx.h"
#include "Trajectory.h"
#include "GameInstance.h"

CTrajectory::CTrajectory(const CTrajectory& Prototype)
{
	*this = Prototype;
}

HRESULT CTrajectory::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CTrajectory::Initialize(void* pArg)
{
	SetUp_Components();

	m_ppShader = GAMEINSTANCE->Get_Shader_From_Key(TEXT("DrawColor"), MEMORY_TYPE::MEMORY_STATIC);

	return S_OK;
}

void CTrajectory::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	/*if (m_pForwardTargetTransformCom)
	{
		m_pForwardTargetTransformCom
	}*/

	//첫번째 노드가 아니라면 검사하지 않는다.
	if (!m_pTargetTransform)
		return;

	_float4x4 MyLocalMatrix;
	D3DXMatrixIdentity(&MyLocalMatrix);

	MyLocalMatrix = CMath_Utillity::Rotate_Matrix(MyLocalMatrix, _float3(1.f, 0.f, 0.f), D3DXToRadian(90.f));
	MyLocalMatrix._41 = m_vOffset.x;
	MyLocalMatrix._42 = m_vOffset.y;
	MyLocalMatrix._43 = m_vOffset.z;


	_float4x4 TargetWorldMatrix = m_pTargetTransform->Get_WorldMatrix();
	TargetWorldMatrix = CMath_Utillity::Set_Scale_Matrix(TargetWorldMatrix, m_vScale);

	MyLocalMatrix *= TargetWorldMatrix;

	Set_LocalMatrix_WithOutScale(MyLocalMatrix, m_bDraw, m_fAlpha);

	//m_fUpdateTime -= fTimeDelta;

	//if (m_fUpdateTime < 0.f)
	//{
	//	//m_pBackNodeTrajectoryObject->Set_LocalMatrix_WithOutScale(m_pTransformCom->Get_WorldMatrix());
	//	_float4x4 MyLocalMatrix;
	//	D3DXMatrixIdentity(&MyLocalMatrix);

	//	MyLocalMatrix = CMath_Utillity::Rotate_Matrix(MyLocalMatrix, _float3(1.f, 0.f, 0.f), D3DXToRadian(90.f));

	//	_float4x4 TargetWorldMatrix = m_pTargetTransform->Get_WorldMatrix();
	//	TargetWorldMatrix = CMath_Utillity::Set_Scale_Matrix(TargetWorldMatrix, m_vScale);

	//	MyLocalMatrix *= TargetWorldMatrix;

	//	Set_LocalMatrix_WithOutScale(MyLocalMatrix);
	//	m_fUpdateTime = 0.01f;
	//}

	

}

void CTrajectory::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	//_float fMovement = CMath_Utillity::Get_Distance(m_pTransformCom->Get_State(CTransform::STATE_POSITION), m_pTransformCom->Get_State(CTransform::STATE_POSITION, true));

	/*if (m_fMovement > 150.f)
	{
		int i = 0;
	}*/

	if(m_bDraw)
		m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_ALPHABLEND, this);
}

HRESULT CTrajectory::Render_Begin(ID3DXEffect** Shader)
{
	__super::Render_Begin(Shader);

	D3DXHANDLE worldHandle = (*m_ppShader)->GetParameterByName(0, "world");
	D3DXHANDLE viewHandle = (*m_ppShader)->GetParameterByName(0, "view");
	D3DXHANDLE projHandle = (*m_ppShader)->GetParameterByName(0, "proj");
	D3DXHANDLE ColorHandle = (*m_ppShader)->GetParameterByName(0, "Color");
	D3DXHANDLE TextureHandle = (*m_ppShader)->GetParameterByName(0, "g_Texture");

	_float4x4 view, proj, world;
	DEVICE->GetTransform(D3DTS_VIEW, &view);
	DEVICE->GetTransform(D3DTS_PROJECTION, &proj);
	float floatArray[4];
	floatArray[0] = 1.f;
	floatArray[1] = 1.f;
	floatArray[2] = 1.f;
	floatArray[3] = m_fAlpha;


	(*m_ppShader)->SetMatrix(viewHandle, &view);
	(*m_ppShader)->SetMatrix(projHandle, &proj);
	(*m_ppShader)->SetMatrix(worldHandle, &m_pTransformCom->Get_WorldMatrix());
	(*m_ppShader)->SetFloatArray(ColorHandle, floatArray, 4);

	__super::Render_Begin(Shader);

	//DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);


	D3DXHANDLE hTech = 0;
	UINT numPasses = 0;

	hTech = (*m_ppShader)->GetTechniqueByName("DefaultTechnique");
	(*m_ppShader)->SetTechnique(hTech);

	(*m_ppShader)->Begin(nullptr, 0);
	(*m_ppShader)->BeginPass(0);

	return S_OK;
}

HRESULT CTrajectory::Render()
{
	__super::Render();


	//DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

	(*m_ppShader)->EndPass();
	(*m_ppShader)->End();

	return S_OK;
}

void CTrajectory::SetUp_Components()
{
	m_pTransformCom = Add_Component<CTransform>();
	WEAK_PTR(m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	WEAK_PTR(m_pRendererCom);

	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	WEAK_PTR(m_pVIBufferCom);

	m_pTransformCom->Rotation(_float3(1.f, 0.f, 0.f), D3DXToRadian(90.f));
	m_pTransformCom->Scaling(_float3(1.f, 1.f, 1.f));

}

void CTrajectory::Set_BackNode(CTrajectory* _pTrajectoryObject)
{
	if (m_pBackNodeTrajectoryObject)
	{
		RETURN_WEAKPTR(m_pBackNodeTrajectoryObject);
	}

	m_pBackNodeTrajectoryObject = _pTrajectoryObject;

	if (_pTrajectoryObject)
	{
		WEAK_PTR(m_pBackNodeTrajectoryObject);
	}
}


CTrajectory* CTrajectory::Create()
{
	CREATE_PIPELINE(CTrajectory);
}

void CTrajectory::OnEnable(void* _Arg)
{
	/*CTransform* pParentTransform = m_pTransformCom->Get_Parent();

	if (!pParentTransform)
		return;

	m_vParentPrePosition = pParentTransform->Get_World_State(CTransform::STATE_POSITION);*/

}


CGameObject* CTrajectory::Clone(void* pArg)
{
	CLONE_PIPELINE(CTrajectory);
}

void CTrajectory::Free()
{
	__super::Free();

	RETURN_WEAKPTR(m_pBackNodeTrajectoryObject);
	RETURN_WEAKPTR(m_pTargetTransform);

	delete this;

}

void CTrajectory::Set_LocalMatrix_WithOutScale(const _float4x4& _LocalMat, _bool _bDraw, _float _fAlpha)
{
	if (m_pBackNodeTrajectoryObject)
	{
		m_pBackNodeTrajectoryObject->Set_LocalMatrix_WithOutScale(m_pTransformCom->Get_LocalMatrix(), m_bDraw, m_fAlpha);
	}
	
	m_fMovement = CMath_Utillity::Get_Distance(*(_float3*)&_LocalMat.m[3][0], m_pTransformCom->Get_State(CTransform::STATE_POSITION));

	/*_float3 Dir = *(_float3*)&_LocalMat.m[3][0] - m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	
	*(_float3*)&_LocalMat.m[3][0] = m_pTransformCom->Get_State(CTransform::STATE_POSITION) + (Dir * 0.9f);*/

	m_pTransformCom->Set_LocalMatrix(_LocalMat);
	m_pTransformCom->Scaling(m_vScale);
	m_bDraw = _bDraw;
	m_fAlpha = _fAlpha;
	

}

void CTrajectory::Make_TrajectoryNode(const _uint& _iNodeCnt, CTransform* _pTargetTransform, const _float3& _vOffset)
{
	if (m_pTargetTransform)
		RETURN_WEAKPTR(m_pTargetTransform);

	m_pTargetTransform = _pTargetTransform;

	if (m_pTargetTransform)
		WEAK_PTR(m_pTargetTransform);

	CTrajectory* pPreNode = this;

	for (_uint i = 0; i < _iNodeCnt; i++)
	{
		CTrajectory* pNode = static_cast<CTrajectory*>(GAMEINSTANCE->Add_GameObject<CTrajectory>(LEVEL_STATIC, TEXT("Trajectory")));
		pNode->Get_Component<CTransform>()->Set_LocalMatrix(_pTargetTransform->Get_WorldMatrix());

		if (pPreNode)
		{
			pPreNode->Set_BackNode(pNode);
		}
		
		pPreNode = pNode;
	}

	m_vOffset = _vOffset;

	//m_pTransformCom->Add_Position(_vOffset);
}

void CTrajectory::Set_Dead_AllTrajectory()
{
	if (m_pBackNodeTrajectoryObject)
	{
		m_pBackNodeTrajectoryObject->Set_Dead_AllTrajectory();
		RETURN_WEAKPTR(m_pBackNodeTrajectoryObject);
		m_pBackNodeTrajectoryObject = nullptr;
	}

	Set_Dead();

}

#include "stdafx.h"
#include "AI_HPBar.h"
#include "GameInstance.h"

CAI_HPBar::CAI_HPBar(const CAI_HPBar& Prototype)
{
	*this = Prototype;
}

HRESULT CAI_HPBar::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CAI_HPBar::Initialize(void* pArg)
{

	SetUp_Components();

	m_ppShader = GAMEINSTANCE->Get_Shader_From_Key(TEXT("HPBar"), MEMORY_TYPE::MEMORY_STATIC);

	return S_OK;
}

void CAI_HPBar::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	if (!m_pMyBodyStatusCom)
	{
		m_pMyBodyStatusCom = m_pTransformCom->Get_Parent()->Get_Owner()->Get_Component<CStatus>();
	}

	_float CurHP = m_pMyBodyStatusCom->Get_Status(CStatus::STATUS_HP);
	_float MaxHP = m_pMyBodyStatusCom->Get_Status(CStatus::STATUS_MAXHP);

	//목표 HP 비율이다.
	_float Target_HPRatio = CurHP / MaxHP;

	m_fHPRatio = CMath_Utillity::fLerp(m_fHPRatio, Target_HPRatio, 0.1f);

	if (!m_pTransformCom->Get_Parent()->Get_Enable())
	{
		this->Set_Enable(false);
	}

}

void CAI_HPBar::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	LookAtCamera();
	m_pTransformCom->Scaling(_float3(5.f, 1.f, 1.f), true);

	if (m_fHPRatio > 0.01f)
	{
		m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
	}

	
}

HRESULT CAI_HPBar::Render_Begin(ID3DXEffect** Shader)
{
	D3DXHANDLE worldHandle = (*m_ppShader)->GetParameterByName(0, "world");
	D3DXHANDLE viewHandle = (*m_ppShader)->GetParameterByName(0, "view");
	D3DXHANDLE projHandle = (*m_ppShader)->GetParameterByName(0, "proj");
	D3DXHANDLE RatioHandle = (*m_ppShader)->GetParameterByName(0, "g_Ratio");
	D3DXHANDLE TextureHandle = (*m_ppShader)->GetParameterByName(0, "g_Texture");

	_float4x4 view, proj, world;
	DEVICE->GetTransform(D3DTS_VIEW, &view);
	DEVICE->GetTransform(D3DTS_PROJECTION, &proj);
	
	(*m_ppShader)->SetMatrix(viewHandle, &view);
	(*m_ppShader)->SetMatrix(projHandle, &proj);
	(*m_ppShader)->SetMatrix(worldHandle, &m_pTransformCom->Get_WorldMatrix());
	(*m_ppShader)->SetFloat(RatioHandle, m_fHPRatio);
	(*m_ppShader)->SetTexture(TextureHandle, m_pRendererCom->Get_Texture(0));

	__super::Render_Begin(Shader);

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 250);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	D3DXHANDLE hTech = 0;
	UINT numPasses = 0;

	hTech = (*m_ppShader)->GetTechniqueByName("DefaultTechnique");
	(*m_ppShader)->SetTechnique(hTech);

	(*m_ppShader)->Begin(nullptr, 0);
	(*m_ppShader)->BeginPass(0);

	//m_pRendererCom->Bind_Texture(0);

	return S_OK;
}

HRESULT CAI_HPBar::Render()
{
	__super::Render();

	//m_pRendererCom->UnBind_Texture();

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	(*m_ppShader)->EndPass();
	(*m_ppShader)->End();

	return S_OK;
}

void CAI_HPBar::Update_Hp_Bar()
{
}

void CAI_HPBar::LookAtCamera()
{
	_float4x4		ViewMatrix;

	DEVICE->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, *(_float3*)&ViewMatrix.m[0][0], true);
	m_pTransformCom->Set_State(CTransform::STATE_UP, *(_float3*)&ViewMatrix.m[1][0], true);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, *(_float3*)&ViewMatrix.m[2][0], true);
	m_pTransformCom->Add_Position(*(_float3*)&ViewMatrix.m[2][0] * -1.f, true);
	m_pTransformCom->Add_Position(*(_float3*)&ViewMatrix.m[1][0] * 5.f, true);
}

HRESULT CAI_HPBar::SetUp_Components()
{
	m_pTransformCom = Add_Component<CTransform>();
	WEAK_PTR(m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	WEAK_PTR(m_pRendererCom);

	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	WEAK_PTR(m_pVIBufferCom);

	m_pRendererCom->Set_Textures_From_Key(TEXT("Logo"), MEMORY_TYPE::MEMORY_STATIC);



	return S_OK;
}

CAI_HPBar* CAI_HPBar::Create()
{
	CREATE_PIPELINE(CAI_HPBar);
}

CGameObject* CAI_HPBar::Clone(void* pArg)
{
	CLONE_PIPELINE(CAI_HPBar);
}

void CAI_HPBar::Free()
{
	__super::Free();

	delete this;

}

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

	return S_OK;
}

void CAI_HPBar::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	LookAtCamera();
}

void CAI_HPBar::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CAI_HPBar::Render_Begin(ID3DXEffect** Shader)
{

	m_pTransformCom->Bind_WorldMatrix();
	__super::Render_Begin(Shader);

	return S_OK;
}

HRESULT CAI_HPBar::Render()
{
	__super::Render();

	return S_OK;
}

void CAI_HPBar::Update_Hp_Bar(CStatus* pStatus)
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

	m_pRendererCom->Set_Textures_From_Key(TEXT("Planet"), MEMORY_TYPE::MEMORY_STATIC);

	//정해진 값 안에서만 놀게끔 짜고 싶을 때,
	_float i = min(1300.f, 800.f);
	_float j = max(-1300.f, 0.f);
	_float MonsterScreenPos_X = 1300.f;


	MonsterScreenPos_X = max(min(MonsterScreenPos_X, 800.f), 0.f);

	//i = 800.f



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

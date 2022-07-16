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

}

void CTrajectory::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	
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
	floatArray[3] = 0.5f;


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
	m_pTransformCom->Scaling(_float3(5.f, 30.f, 1.f));
	

}

CTrajectory* CTrajectory::Create()
{
	CREATE_PIPELINE(CTrajectory);
}

CGameObject* CTrajectory::Clone(void* pArg)
{
	CLONE_PIPELINE(CTrajectory);
}

void CTrajectory::Free()
{
	__super::Free();

	delete this;

}

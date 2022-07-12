 
#include "stdafx.h"
#include "Rader.h"
#include "GameInstance.h"
#include "Rader_PSystem.h"

CRader::CRader()
{
}

CRader::CRader(const CRader& Prototype)
{
	*this = Prototype;
}

HRESULT CRader::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CRader::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_fX = 200.f;
	m_fY = 630.f;
	m_fSizeX = 100.0f;
	m_fSizeY = 100.0f;

	SetRect(&m_rcRader, m_fX - m_fSizeX * 0.5f, m_fY - m_fSizeY * 0.5f,
		m_fX + m_fSizeX * 0.5f, m_fY + m_fSizeY * 0.5f);


	D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinCX, g_iWinCY, 0.0f, 1.f);

	return S_OK;
}

void CRader::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	m_fComputeTime -= fTimeDelta;
	if (m_fComputeTime < 0.f)
	{
		Compute_Distance();
		m_fComputeTime = 2.f;
	}
}

void CRader::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pTransformCom->Scaling(_float3(m_fSizeX, m_fSizeY, 1.f)* 1.5f);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_fX - (g_iWinCX >> 1), -m_fY + (g_iWinCY >> 1), 0.f));

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CRader::Render()
{
	

	m_pTransformCom->Bind_WorldMatrix();

	m_pRendererCom->Bind_Texture(1);

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 200);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);


	_float4x4 CurView, CurProj;
	DEVICE->GetTransform(D3DTS_VIEW, &CurView);
	DEVICE->GetTransform(D3DTS_PROJECTION, &CurProj);

	_float4x4	ViewMatrix;
	D3DXMatrixIdentity(&ViewMatrix);

	DEVICE->SetTransform(D3DTS_VIEW, &ViewMatrix);
	DEVICE->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	__super::Render();


	m_pRendererCom->UnBind_Texture();



	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	DEVICE->SetTransform(D3DTS_VIEW, &CurView);
	DEVICE->SetTransform(D3DTS_PROJECTION, &CurProj);

	return S_OK;
}

HRESULT CRader::SetUp_Components()
{
	m_pTransformCom = Add_Component<CTransform>();
	WEAK_PTR(m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_Textures_From_Key(TEXT("Rader"), MEMORY_TYPE::MEMORY_STATIC);
	WEAK_PTR(m_pRendererCom);

	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	WEAK_PTR(m_pVIBufferCom);




	return S_OK;
}

void CRader::Compute_Distance()
{
	_float3 Distance = { 0.f, 0.f, 0.f };
	m_pCameraTransform = GAMEINSTANCE->Get_Camera(CURRENT_CAMERA)->Get_Transform();

	list<CGameObject*>* Monster = GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("Monster"));

	if (!Monster)
	{
		return;
	}
	for (auto& elem : *Monster)
	{
		_float3 MonsterPos = elem->Get_Component<CTransform>()->Get_World_State(CTransform::STATE_POSITION);

		_float3 CameraPos = m_pCameraTransform->Get_World_State(CTransform::STATE_POSITION);

		Distance = MonsterPos - CameraPos;
		Distance.y = 0.f;
		
		_float Length = D3DXVec3Length(&Distance);

		// 100 : 1 비율 
		_float Ratio = Length / 50.f;

		// xz 평면상의 방향벡터
		D3DXVec3Normalize(&Distance, &Distance);

		_float3 Pos = Distance* Ratio;
		Pos.x += m_fX;
		Pos.y =  Pos.z + m_fY;
		int i = 10;
		((CRader_PSystem*)GAMEINSTANCE->Get_ParticleSystem<CRader_PSystem>(CURRENT_LEVEL, TEXT("Particle_Rader")))->AddParticle(1, Pos);

	}
}

CRader* CRader::Create()
{
	CREATE_PIPELINE(CRader);
}

CGameObject* CRader::Clone(void* pArg)
{
	CLONE_PIPELINE(CRader);
}

void CRader::Free()
{
	__super::Free();

	delete this;
}

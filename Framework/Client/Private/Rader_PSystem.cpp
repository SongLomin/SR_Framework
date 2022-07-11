#include "stdafx.h"
#include "Rader_PSystem.h"
#include "GameInstance.h"
#include "Math_Utillity.h"

CRader_PSystem::CRader_PSystem(const CRader_PSystem& Prototype)
{
	*this = Prototype;
}

HRESULT CRader_PSystem::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CRader_PSystem::Initialize(void* pArg)
{
	m_vbSize = 2048;
	m_vbOffset = 0;
	m_vbBatchSize = 512;

	//D3DXMatrixOrthoLH(&m_ProjMatrix, 200.f, 630.f, 0.0f, 1.f);
	//D3DXMatrixOrthoLH(&m_ProjMatrix, g_iWinCX, g_iWinCY, 0.0f, 1.f);

	__super::Initialize(pArg);

	return S_OK;
}

void CRader_PSystem::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	std::list<ParticleDesc>::iterator iter;
	for (iter = m_particles.begin(); iter != m_particles.end(); iter++)
	{

		//iter->position += iter->velocity * fTimeDelta;

		if (iter->lifeTime < iter->age)
		{
			iter->isAlive = false;
			//ResetParticle(&(*iter));
			continue;
		}

		iter->age += fTimeDelta;
	}

	if (IsDead())
	{
		Set_Enable(false);
	}
}

void CRader_PSystem::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRenderer->Add_RenderGroup(RENDERGROUP::RENDER_UI, this);
}

HRESULT CRader_PSystem::Render_Begin(ID3DXEffect** Shader)
{
	m_pTransform->Bind_WorldMatrix();

	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	DEVICE->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	DEVICE->SetRenderState(D3DRS_POINTSIZE, CMath_Utillity::FtoDw(m_size));
	DEVICE->SetRenderState(D3DRS_POINTSIZE_MIN, CMath_Utillity::FtoDw(0.0f));

	// control the size of the particle relative to distance
	DEVICE->SetRenderState(D3DRS_POINTSCALE_A, CMath_Utillity::FtoDw(0.0f));
	DEVICE->SetRenderState(D3DRS_POINTSCALE_B, CMath_Utillity::FtoDw(0.0f));
	DEVICE->SetRenderState(D3DRS_POINTSCALE_C, CMath_Utillity::FtoDw(1.0f));



	//DEVICE->SetTransform(D3DTS_WORLD, &I);

	// use alpha from texture
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	return S_OK;
}

HRESULT CRader_PSystem::Render()
{
	m_pRenderer->Bind_Texture(0);



	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 253);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	_float4x4 CurView, CurProj;
	DEVICE->GetTransform(D3DTS_VIEW, &CurView);
	DEVICE->GetTransform(D3DTS_PROJECTION, &CurProj);

	_float4x4	ViewMatrix;
	D3DXMatrixIdentity(&ViewMatrix);

	DEVICE->SetTransform(D3DTS_VIEW, &ViewMatrix);
	DEVICE->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);


	__super::Render();


	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	DEVICE->SetTransform(D3DTS_VIEW, &CurView);
	DEVICE->SetTransform(D3DTS_PROJECTION, &CurProj);



	//DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);


	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	DEVICE->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);



	//언바인드
	m_pRenderer->UnBind_Texture();
	return S_OK;
}

void CRader_PSystem::ResetParticle(ParticleDesc* Desc)
{
	Desc->isAlive = true;

	m_size = 0.5f;

	Desc->position;
	//Desc->position
	//CMath_Utillity::WorldToScreen(&Desc->position, &Desc->position);
	//D3DXVec3TransformCoord(&Desc->position, &Desc->position, &m_WorldMat);
	int i = 10;

	Desc->color = D3DCOLOR_ARGB(255, 255, 0, 0);

	Desc->age = 0.f;
	Desc->lifeTime = 2.f;
}

CRader_PSystem* CRader_PSystem::Create()
{
	CREATE_PIPELINE(CRader_PSystem);
}

CGameObject* CRader_PSystem::Clone(void* pArg)
{
	CLONE_PIPELINE(CRader_PSystem);
}

void CRader_PSystem::Free()
{
	__super::Free();

	delete this;
}

void CRader_PSystem::OnEnable(void* _Arg)
{
}

void CRader_PSystem::OnDisable()
{
}

#include "stdafx.h"
#include "Rocket_PSystem.h"
#include "GameInstance.h"
#include <Math_Utillity.h>

CRocket_PSystem::CRocket_PSystem(const CRocket_PSystem& Prototype)
{
	*this = Prototype;
}

HRESULT CRocket_PSystem::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CRocket_PSystem::Initialize(void* pArg)
{
	m_vbSize = 2048;
	m_vbOffset = 0;
	m_vbBatchSize = 512;

	__super::Initialize(pArg);
	m_pRenderer->Set_Textures_From_Key(TEXT("Smoke_Particle"), MEMORY_TYPE::MEMORY_STATIC);

	return S_OK;
}

void CRocket_PSystem::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	std::list<ParticleDesc>::iterator iter;
	for (iter = m_particles.begin(); iter != m_particles.end(); iter++)
	{

		iter->position += iter->velocity * fTimeDelta;

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

void CRocket_PSystem::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRenderer->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CRocket_PSystem::Render_Begin(ID3DXEffect** Shader)
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

HRESULT CRocket_PSystem::Render()
{

	m_pRenderer->Bind_Texture(0);



	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 250);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	__super::Render();

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);


	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	DEVICE->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);



	//언바인드
	m_pRenderer->UnBind_Texture();
	return S_OK;
}

void CRocket_PSystem::ResetParticle(ParticleDesc* Desc)
{
	Desc->isAlive = true;

	m_size = 1.f;

	Desc->position.x = 0.f;
	Desc->position.y = 0.f;
	Desc->position.z = -4.f;

	D3DXVec3TransformCoord(&Desc->position, &Desc->position, &m_WorldMat);

	//Desc->position -= m_pTransform->Get_World_State(CTransform::STATE_LOOK) * 50.f;

	Desc->velocity.x = 0.f;
	Desc->velocity.y = 0.f;
	Desc->velocity.z = 0.f;

	Desc->color = D3DCOLOR_ARGB(255, 200, 200, 200);

	Desc->age = 0.f;
	Desc->lifeTime = 1.f;
}

CRocket_PSystem* CRocket_PSystem::Create()
{
	CREATE_PIPELINE(CRocket_PSystem);
}

CGameObject* CRocket_PSystem::Clone(void* pArg)
{
	CLONE_PIPELINE(CRocket_PSystem);
}

void CRocket_PSystem::Free()
{
	__super::Free();

	delete this;
}

void CRocket_PSystem::OnEnable(void* _Arg)
{
}

void CRocket_PSystem::OnDisable()
{
}

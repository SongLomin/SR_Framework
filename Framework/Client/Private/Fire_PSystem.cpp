#include "stdafx.h"
#include "Fire_PSystem.h"
#include "GameInstance.h"
#include "Math_Utillity.h"

CFire_PSystem::CFire_PSystem(const CFire_PSystem& Prototype)
{
	*this = Prototype;
}

HRESULT CFire_PSystem::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CFire_PSystem::Initialize(void* pArg)
{
	m_size = 0.1f;


	m_vbSize = 2048;
	m_vbOffset = 0;
	m_vbBatchSize = 512;

	m_BeginColor = _float3(1.f, 0.9f, 0.f);
	m_EndColor = _float3(1.f, 0.f, 0.f);

	__super::Initialize(pArg);

	return S_OK;
}

void CFire_PSystem::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	//수명 진행상황 퍼센트 0 ~ 1
	_float fAge_ratio;
	_float3 CurrentColor;
	std::list<ParticleDesc>::iterator iter;
	for (iter = m_particles.begin(); iter != m_particles.end(); iter++)
	{
		iter->position += iter->velocity * fTimeDelta;
		fAge_ratio = iter->age / iter->lifeTime;

		CurrentColor = m_BeginColor * (1.f - fAge_ratio) + m_EndColor * (fAge_ratio);
		iter->color = D3DCOLOR_ARGB(255, (_uint)(CurrentColor.x * 255), (_uint)(CurrentColor.y * 255), (_uint)(CurrentColor.z * 255));

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
		printf("%s : Set_Enable(false).\n", typeid(*this).name());
	}
}

void CFire_PSystem::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRenderer->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CFire_PSystem::Render_Begin(ID3DXEffect** Shader)
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

HRESULT CFire_PSystem::Render()
{
	//m_pRenderer->Bind_Texture();

	__super::Render();

	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	DEVICE->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

	//언바인드
	return S_OK;
}

void CFire_PSystem::ResetParticle(ParticleDesc* Desc)
{
	Desc->isAlive = true;


	m_size = (_float)((rand() % 5 + 10) * 0.01f);
	
	Desc->position.x = 0.f;
	Desc->position.y = 0.f + 1.f;
	Desc->position.z = 0.f;

	Desc->velocity.x = (_float)((rand() % 31) * 0.5f) - 10.5f;
	Desc->velocity.y = (_float)((rand() % 31) * 0.5f) - 7.5f;
	Desc->velocity.z = (_float)((rand() % 7) * 0.5f) - 1.5f;

	//Desc->velocity.x = 1.f;
	//Desc->velocity.y = 1.f;
	//Desc->velocity.z = 1.f;

	//Desc->velocity *= 10.f;

	// white snow flake
	Desc->color = D3DCOLOR_ARGB(255, (_uint)(m_BeginColor.x * 255), (_uint)(m_BeginColor.y * 255), (_uint)(m_BeginColor.z * 255));
	//Desc->colorFade = D3DCOLOR_RGBA(255, 0, 0, 255);
	Desc->age = 0.f;
	Desc->lifeTime = 1.f;
}

CFire_PSystem* CFire_PSystem::Create()
{
	CREATE_PIPELINE(CFire_PSystem);
}

CGameObject* CFire_PSystem::Clone(void* pArg)
{
	CLONE_PIPELINE(CFire_PSystem);
}

void CFire_PSystem::Free()
{
	__super::Free();

	delete this;
}

void CFire_PSystem::OnEnable(void* _Arg)
{
}

void CFire_PSystem::OnDisable()
{
}

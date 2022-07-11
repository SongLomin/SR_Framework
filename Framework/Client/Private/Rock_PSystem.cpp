#include "stdafx.h"
#include "Rock_PSystem.h"
#include "Math_Utillity.h"
#include "GameInstance.h"

CRock_PSystem::CRock_PSystem(const CRock_PSystem& Prototype)
{
	*this = Prototype;
}

HRESULT CRock_PSystem::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CRock_PSystem::Initialize(void* pArg)
{
	m_size = 0.1f;


	m_vbSize = 2048;
	m_vbOffset = 0;
	m_vbBatchSize = 512;


	m_BeginColor = _float3(1.f, 1.f, 1.f);
	m_EndColor = _float3(1.f, 1.f, 1.f);

	__super::Initialize(pArg);
	
	m_pRenderer->Set_Textures_From_Key(TEXT("Rock"), MEMORY_TYPE::MEMORY_STATIC);



	return S_OK;
}

void CRock_PSystem::Tick(_float fTimeDelta)
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

void CRock_PSystem::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRenderer->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CRock_PSystem::Render_Begin(ID3DXEffect** Shader)
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

HRESULT CRock_PSystem::Render()
{
	m_pRenderer->Bind_Texture(0);



	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 253);
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

void CRock_PSystem::ResetParticle(ParticleDesc* Desc)
{
	Desc->isAlive = true;



	m_size = CMath_Utillity::Get_RandomFloat(0.2f, 2.5f);

	Desc->position.x = 0.f;
	Desc->position.y = 0.f + 1.f;
	Desc->position.z = 0.f;

	D3DXVec3TransformCoord(&Desc->position, &Desc->position, &m_WorldMat);

	Desc->velocity.x = CMath_Utillity::Get_RandomFloat(-20.f, 20.f);
	Desc->velocity.y = CMath_Utillity::Get_RandomFloat(-20.f, 20.f);
	Desc->velocity.z = CMath_Utillity::Get_RandomFloat(-20.f, 20.f);

	//Desc->velocity.x = 1.f;
	//Desc->velocity.y = 1.f;
	//Desc->velocity.z = 1.f;

	//Desc->velocity *= 10.f;

	// white snow flake
	Desc->color = D3DCOLOR_ARGB(255, (_uint)(m_BeginColor.x * 255), (_uint)(m_BeginColor.y * 255), (_uint)(m_BeginColor.z * 255));
	//Desc->colorFade = D3DCOLOR_RGBA(255, 0, 0, 255);
	Desc->age = 0.f;
	Desc->lifeTime = CMath_Utillity::Get_RandomFloat(0.5f, 1.f);
}

CRock_PSystem* CRock_PSystem::Create()
{
	CREATE_PIPELINE(CRock_PSystem);
}

CGameObject* CRock_PSystem::Clone(void* pArg)
{
	CLONE_PIPELINE(CRock_PSystem);
}

void CRock_PSystem::Free()
{
	__super::Free();

	delete this;
}

void CRock_PSystem::OnEnable(void* _Arg)
{
}

void CRock_PSystem::OnDisable()
{
}

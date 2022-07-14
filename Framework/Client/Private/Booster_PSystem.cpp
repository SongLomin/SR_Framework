#include "stdafx.h"
#include "Booster_PSystem.h"
#include "Math_Utillity.h"
#include "GameInstance.h"

CBooster_PSystem::CBooster_PSystem(const CBooster_PSystem& Prototype)
{
	*this = Prototype;
}

HRESULT CBooster_PSystem::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CBooster_PSystem::Initialize(void* pArg)
{
	m_size = 1.f;


	m_vbSize = 2048;
	m_vbOffset = 0;
	m_vbBatchSize = 512;

	

	m_fCurSpeed = 0.f;
	m_fMaxSpeed = 1.f;
	m_BeginColor = _float3(1.f, 1.f, 1.f);
	m_EndColor = _float3(0.f, 0.1f, 0.8f);

	__super::Initialize(pArg);

	//m_pRenderer = Get_Component<CRenderer>();
	m_pRenderer->Set_Textures_From_Key(TEXT("Booster"), MEMORY_TYPE::MEMORY_STATIC);


	return S_OK;
}

void CBooster_PSystem::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	//수명 진행상황 퍼센트 0 ~ 1
	_float fAge_ratio;
	//_float fSpeed_ratio;
	_float3 CurrentColor;
	std::list<ParticleDesc>::iterator iter;
	for (iter = m_particles.begin(); iter != m_particles.end(); iter++)
	{
		++m_iTextureCount;
		if (m_iTextureCount == 83)
		{
			m_iTextureCount = 0;
		}
		//m_fCurSpeed += 0.002f;
		//if (m_fCurSpeed >= 1.f)
		//{
		//	m_fCurSpeed = m_fMaxSpeed;
		//}
		//fSpeed_ratio = m_fCurSpeed / m_fMaxSpeed;

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
	}
}

void CBooster_PSystem::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRenderer->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CBooster_PSystem::Render_Begin(ID3DXEffect** Shader)
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

HRESULT CBooster_PSystem::Render()
{
	m_pRenderer->Bind_Texture(m_iTextureCount);

	//DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

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

void CBooster_PSystem::ResetParticle(ParticleDesc* Desc)
{
	Desc->isAlive = true;


	//m_size = (_float)((rand() % 5 + 10) * 0.01f);
	m_size = 1.f;


	Desc->position.x = 0.f;
	Desc->position.y = 0.f;
	Desc->position.z = -7.f;

	D3DXVec3TransformCoord(&Desc->position, &Desc->position, &m_WorldMat);

	Desc->velocity.x = (_float)((rand() % 21) * 0.5f) - 5.f;
	Desc->velocity.y = (_float)((rand() % 21) * 0.5f) - 11.f;
	Desc->velocity.z = (_float)((rand() % 21) * 0.5f) - 5.f;


	Desc->color = D3DCOLOR_ARGB(255, (_uint)(m_BeginColor.x * 255), (_uint)(m_BeginColor.y * 255), (_uint)(m_BeginColor.z * 255));


	

	Desc->age = 0.f;
	Desc->lifeTime = 0.5f;
}

CBooster_PSystem* CBooster_PSystem::Create()
{
	CREATE_PIPELINE(CBooster_PSystem);
}

CGameObject* CBooster_PSystem::Clone(void* pArg)
{
	CLONE_PIPELINE(CBooster_PSystem);
}

void CBooster_PSystem::Free()
{
	__super::Free();

	delete this;
}

void CBooster_PSystem::OnEnable(void* _Arg)
{
}

void CBooster_PSystem::OnDisable()
{
}

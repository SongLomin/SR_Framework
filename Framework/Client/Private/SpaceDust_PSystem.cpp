#include "stdafx.h"
#include "SpaceDust_PSystem.h"
#include "GameInstance.h"
#include "Math_Utillity.h"

CSpaceDust_PSystem::CSpaceDust_PSystem(const CSpaceDust_PSystem& Prototype)
{
	*this = Prototype;
}

HRESULT CSpaceDust_PSystem::Initialize_Prototype()
{

	return S_OK;
}

HRESULT CSpaceDust_PSystem::Initialize(void* pArg)
{
	//버텍스 크기를 미리 정해놓은 뒤에 부모의 Initialize를 호출해서 버텍스를 생성한다.
	m_size = 0.1f;
	m_vbSize = 2048;
	m_vbOffset = 0;
	m_vbBatchSize = 512;

	__super::Initialize(pArg);

	/*for (int i = 0; i < numParticles; i++)
		AddParticle();*/

	return S_OK;
}

void CSpaceDust_PSystem::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	std::list<ParticleDesc>::iterator i;
	for (i = m_particles.begin(); i != m_particles.end(); i++)
	{
		i->position += i->velocity * fTimeDelta;

		//// is the point outside bounds?
		//if (_boundingBox.isPointInside(i->_position) == false)
		//{
		//	// nope so kill it, but we want to recycle dead 
		//	// particles, so respawn it instead.
		//	resetParticle(&(*i));
		//}
	}
}

void CSpaceDust_PSystem::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRenderer->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CSpaceDust_PSystem::Render_Begin(ID3DXEffect** Shader)
{
	__super::Render_Begin(Shader);

	//스카이 박스처럼 카메라를 따라다닌다.
	_float3 CamWorldPos = GAMEINSTANCE->Get_Camera()->Get_Transform()->Get_World_State(CTransform::STATE_POSITION);
	m_pTransform->Set_State(CTransform::STATE_POSITION, CamWorldPos, true);
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

HRESULT CSpaceDust_PSystem::Render()
{
	__super::Render();

	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	DEVICE->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

	return S_OK;
}

void CSpaceDust_PSystem::ResetParticle(ParticleDesc* Desc)
{
	Desc->isAlive = true;

	
	m_size = (_float)((rand() % 5 + 10) * 0.01f);
	// no randomness for height (y-coordinate).  Snow flake
	// always starts at the top of bounding box.
	Desc->position.x = (_float)(rand() % 10 + 10);
	Desc->position.y = (_float)(rand() % 10 + 10);
	Desc->position.z = (_float)(rand() % 10 + 10);

	// snow flakes fall downwards and slightly to the left
	Desc->velocity.x = -0.f;
	Desc->velocity.y = -0.f;
	Desc->velocity.z = 0.0f;

	// white snow flake
	Desc->color = D3DCOLOR_RGBA(255, 255, 255, 255);

}

CSpaceDust_PSystem* CSpaceDust_PSystem::Create()
{
	CREATE_PIPELINE(CSpaceDust_PSystem);
}

CGameObject* CSpaceDust_PSystem::Clone(void* pArg)
{
	CLONE_PIPELINE(CSpaceDust_PSystem);
}

void CSpaceDust_PSystem::Free()
{
	__super::Free();

	delete this;
}

void CSpaceDust_PSystem::OnEnable(void* _Arg)
{
}

void CSpaceDust_PSystem::OnDisable()
{
}

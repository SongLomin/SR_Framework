#include "stdafx.h"
#include "Trajectory_PSystem.h"
#include "GameInstance.h"

CTrajectory_PSystem::CTrajectory_PSystem(const CTrajectory_PSystem& Prototype)
{
	*this = Prototype;
}

HRESULT CTrajectory_PSystem::Initialize_Prototype()
{
	__super::Initialize_Prototype();

	return S_OK;
}

HRESULT CTrajectory_PSystem::Initialize(void* pArg)
{
	__super::Initialize(pArg);
	return S_OK;
}

void CTrajectory_PSystem::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


}

void CTrajectory_PSystem::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
}

HRESULT CTrajectory_PSystem::Render_Begin(ID3DXEffect** Shader)
{
	__super::Render_Begin(Shader);

	return S_OK;
}

HRESULT CTrajectory_PSystem::Render()
{
	__super::Render();



	return S_OK;
}

void CTrajectory_PSystem::ResetParticle(ParticleDesc* attribute)
{
	attribute->isAlive = true;
	


	attribute->color = D3DCOLOR_ARGB(255, 255, 255, 255);
}

CTrajectory_PSystem* CTrajectory_PSystem::Create()
{
	CREATE_PIPELINE(CTrajectory_PSystem);
}

CGameObject* CTrajectory_PSystem::Clone(void* pArg)
{
	CLONE_PIPELINE(CTrajectory_PSystem);
}

void CTrajectory_PSystem::OnEnable(void* _Arg)
{
}

void CTrajectory_PSystem::OnDisable()
{
}

#include "stdafx.h"
#include "SpaceDust_PSystem.h"
#include "GameInstance.h"

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
	__super::Initialize(pArg);

	return S_OK;
}

void CSpaceDust_PSystem::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


}

void CSpaceDust_PSystem::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);


}

HRESULT CSpaceDust_PSystem::Render_Begin(ID3DXEffect** Shader)
{
	__super::Render_Begin(Shader);

	return S_OK;
}

HRESULT CSpaceDust_PSystem::Render()
{
	__super::Render();

	return S_OK;
}

void CSpaceDust_PSystem::ResetParticle(ParticleDesc* attribute)
{


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

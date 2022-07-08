#include "stdafx.h"
#include "Scourge.h"

CScouge::CScouge(const CScouge& Prototype)
{
	*this = Prototype;
}

HRESULT CScouge::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CScouge::Initialize(void* pArg)
{
	return S_OK;
}

void CScouge::Tick(_float fTimeDelta)
{
}

void CScouge::LateTick(_float fTimeDelta)
{
}

HRESULT CScouge::Render_Begin(ID3DXEffect** Shader)
{
	return S_OK;
}

HRESULT CScouge::Render()
{
	return S_OK;
}

void CScouge::Update_Target(CGameObject* _Target)
{
}

void CScouge::SetUp_Components_For_Child()
{
}

void CScouge::On_Change_Controller(const CONTROLLER& _IsAI)
{
	__super::On_Change_Controller(_IsAI);
}

void CScouge::On_Collision_Enter(CCollider* _Other_Collider)
{
	__super::On_Collision_Enter(_Other_Collider);
}

void CScouge::On_Collision_Stay(CCollider* _Other_Collider)
{
	__super::On_Collision_Stay(_Other_Collider);
}

void CScouge::On_Collision_Exit(CCollider* _Other_Collider)
{
	__super::On_Collision_Exit(_Other_Collider);
}

CScouge* CScouge::Create()
{
	CREATE_PIPELINE(CScouge);
}

CGameObject* CScouge::Clone(void* pArg)
{
	CLONE_PIPELINE(CScouge);
}

void CScouge::Free()
{
	__super::Free();

	delete this;
}

#include "stdafx.h"
#include "Bullet.h"
#include "GameInstance.h"

CBullet::CBullet()
{
}

CBullet::CBullet(const CBullet& Prototype)
{
}

HRESULT CBullet::Initialize_Prototype()
{
    return E_NOTIMPL;
}

HRESULT CBullet::Initialize(void* pArg)
{
    return E_NOTIMPL;
}

void CBullet::Tick(_float fTimeDelta)
{
}

void CBullet::LateTick(_float fTimeDelta)
{
}

HRESULT CBullet::Render_Begin(ID3DXEffect** Shader)
{
    return E_NOTIMPL;
}

HRESULT CBullet::Render()
{
    return E_NOTIMPL;
}

void CBullet::Link_PosinTransform(CTransform* _pTransform)
{
}

void CBullet::On_Collision_Enter(CCollider* _Other_Collider)
{
}

void CBullet::On_Collision_Stay(CCollider* _Other_Collider)
{
}

void CBullet::On_Collision_Exit(CCollider* _Other_Collider)
{
}

void CBullet::Free()
{
}

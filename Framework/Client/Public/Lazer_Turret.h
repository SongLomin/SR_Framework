#pragma once
#include "Client_Defines.h"
#include "Turret.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CMesh_Cube;
END

BEGIN(Client)

class CLazer_Turret final :public CTurret
{
private:
    CLazer_Turret() = default;
    CLazer_Turret(const CLazer_Turret& Prototype);
    virtual ~CLazer_Turret() = default;

protected:
    // CTurret을(를) 통해 상속됨
    virtual HRESULT Initialize(void* pArg) override;
    virtual void    Tick(_float fTimeDelta) override;
    virtual void    Command_Fire() override;

protected:
    virtual void SetUp_Components_For_Child() override;

private:
    COLLISION_TYPE m_eBulletCollisionType = COLLISION_TYPE::PLAYER_ATTACK;
       
    _float3     m_vColor=_float3(1.f,1.f,1.f);

public:
    // CGameObject을(를) 통해 상속됨
    static CLazer_Turret* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;
};

END


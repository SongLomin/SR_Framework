#pragma once
#include "Turret.h"



BEGIN(Client)

class CRocket_Turret final :public CTurret
{
private:
    CRocket_Turret() = default;
    CRocket_Turret(const CRocket_Turret& Prototype);
    virtual ~CRocket_Turret() = default;

protected:
    // CTurret을(를) 통해 상속됨
    virtual HRESULT Initialize(void* pArg) override;
    virtual void    Command_Fire() override;

protected:
    virtual void SetUp_Components_For_Child() override;

private:
    COLLISION_TYPE m_eBulletCollisionType = COLLISION_TYPE::PLAYER_ATTACK;


public:
    // CGameObject을(를) 통해 상속됨
    static CRocket_Turret* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;
};

END

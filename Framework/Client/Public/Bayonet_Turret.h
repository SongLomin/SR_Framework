#pragma once
#include "Turret.h"

BEGIN(Client)

class CBayonet_Turret final :public CTurret
{
private:
    CBayonet_Turret() = default;
    CBayonet_Turret(const CBayonet_Turret& Prototype);
    virtual ~CBayonet_Turret() = default;

protected:
    // CTurret을(를) 통해 상속됨
    virtual HRESULT Initialize(void* pArg) override;
    virtual void    Tick(_float fTimeDelta) final;
    virtual void    LateTick(_float fTimeDelta) final;
    virtual HRESULT Render();
    virtual void    Command_Fire() override;
    virtual void    On_EventMessage(void* _Arg) override;

protected:
    virtual void SetUp_Components_For_Child() override;

private:
    COLLISION_TYPE  m_eBulletCollisionType = COLLISION_TYPE::PLAYER_ATTACK;
    _float          m_fPreheatTime = 0.f;
    _float          m_fLerpTime = 2.f;

public:
    // CGameObject을(를) 통해 상속됨
    static CBayonet_Turret* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;
};

END

#pragma once
#include "Base.h"

BEGIN(Engine)

class CParticle_Manager final :
    public CBase
{
    DECLARE_SINGLETON(CParticle_Manager)

public:
    CParticle_Manager();
    virtual ~CParticle_Manager() = default;

public:
    void Initialize();
    void Tick();

public:
    void Add_Particle();
    void Add_ParticleSystem();
private:

private:


public:
    virtual void Free() override;

};

END
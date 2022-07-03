#pragma once
#include "Client_Defines.h"
#include "ParticleSystem.h"

BEGIN(Engine)
class CTransform;

END


BEGIN(Client)

class CSpaceDust_PSystem final :
    public CParticleSystem
{
private:
    CSpaceDust_PSystem() = default;
    CSpaceDust_PSystem(const CSpaceDust_PSystem& Prototype);
    virtual ~CSpaceDust_PSystem() = default;

public:
    // CGameObject을(를) 통해 상속됨
    virtual HRESULT Initialize_Prototype() override;

    virtual HRESULT Initialize(void* pArg) override;
    virtual void Tick(_float fTimeDelta);
    virtual void LateTick(_float fTimeDelta);
    //렌더 이전 작업 수행 (상수버퍼 세팅)
    virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr);
    virtual HRESULT Render();

public:
    virtual void ResetParticle(ParticleDesc* Desc) override;

private:

public:

    // CParticleSystem을(를) 통해 상속됨
    static CSpaceDust_PSystem* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;

public:
    //객체의 상태가 활성화 상태로 변경될 때, 호출되는 이벤트입니다.
    virtual void OnEnable(void* _Arg = nullptr) override;

    //객체의 상태가 비활성화 상태로 변경될 때, 호출되는 이벤트입니다.
    virtual void OnDisable() override;

};

END
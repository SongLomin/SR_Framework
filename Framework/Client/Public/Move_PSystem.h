#pragma once
#include "Client_Defines.h"
#include "ParticleSystem.h"
BEGIN(Engine)

END

BEGIN(Client)

class CMove_PSystem final : public CParticleSystem
{

private:
    CMove_PSystem() = default;
    CMove_PSystem(const CMove_PSystem& Prototype);
    virtual ~CMove_PSystem() = default;

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
    _float3     m_BeginColor;
    _float3     m_EndColor;

public:

    // CParticleSystem을(를) 통해 상속됨
    static CMove_PSystem* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;

public:
    //객체의 상태가 활성화 상태로 변경될 때, 호출되는 이벤트입니다.
    virtual void OnEnable(void* _Arg = nullptr) override;

    //객체의 상태가 비활성화 상태로 변경될 때, 호출되는 이벤트입니다.
    virtual void OnDisable() override;
};

END
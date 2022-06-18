#pragma once
#include "Component.h"

BEGIN(Engine)
class CTransform;

class ENGINE_DLL CCamera final :
    public CComponent
{
protected:
    struct Desc
    {
        _float fFovy = 0.f;
        _float fAspect = 0.f;
        _float fNear = 0.f;
        _float fFar = 0.f;
    };

private:
    CCamera() = default;
    CCamera(const CCamera & Prototype);
    virtual ~CCamera() = default;

public:
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;

public:
    void Link_TransformCom(CTransform* _pTransform);
    void Set_Target(CTransform* _pTransform);

    void Set_Param(_float _fFovy, _float _fAspect, _float _fNear, _float _fFar);
    
    HRESULT Bind_PipeLine();

private:
    CTransform* m_pTransform = nullptr;
    CTransform* m_pTarget_Transform = nullptr;
    Desc m_CamDesc;

public:
    static CCamera* Create();
    virtual CComponent* Clone(void* pArg) override;
    virtual void Free() override;

};

END
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
    CTransform* Get_Transform() { return m_pTransform; }
    _float4x4 Get_CameraWorldMat();

public:
    void Link_TransformCom(CTransform* _pTransform);
    void Set_Target(CTransform* _pTransform);

    void Set_Param(_float _fFovy, _float _fAspect, _float _fNear, _float _fFar);
	CTransform* Get_Target()
	{
		return m_pTarget_Transform;
	}
    
    _float Get_Fov() const { return m_CamDesc.fFovy; }
    _float Get_Aspect() const { return m_CamDesc.fAspect; }
    _float Get_Far() const { return m_CamDesc.fFar; }

    HRESULT Bind_PipeLine();
    void Add_Shaking(_float _fOffset, _float _fInclination);

private:
    void Shake();
    void RandomVec(_float3* _vDir, float _flowBound, float _fHighBound);


private:
    CTransform* m_pTransform = nullptr;
    CTransform* m_pTarget_Transform = nullptr;
    Desc m_CamDesc;

    _float  m_fOffset = 0.f;
    _float  m_fInclination = 0.f;
    _float3 m_vOffSetDir;


public:
    static CCamera* Create();
    virtual CComponent* Clone(void* pArg) override;
    virtual void Free() override;

};

END
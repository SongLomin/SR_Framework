#pragma once
#include "GameObject.h"


BEGIN(Engine)
class CTransform;
class CCamera;



class CCam_Free :
    public CGameObject
{
private:
    explicit CCam_Free() = default;
    CCam_Free(const CCam_Free& Prototype);
    virtual ~CCam_Free() = default;

public:
    // CGameObject을(를) 통해 상속됨
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render() override;

//    void    Set_RouteCamera(CCamera* _pCurCamera, const _tchar* _NextCameraTag, _float _fTime);
//    void    Switch_Player(_float4x4 _pCurCamera, CTransform* _pNextCamera, const _tchar* _NextCameraTag, _float fTime);
//    //바꾼 후에는 무조건 3인칭으로
//private:
//    void    Make_Route();//시점 전환용
//
//    void    Switch_PlayerCamera(_float fTimeDelta);
//    void    Swap_Camera(_float fTimeDelta);

    

private:
    CTransform* m_pTransformCom = nullptr;
    CCamera* m_pCameraCom = nullptr;

    //루트 생성에만 쓰임
    const _tchar* m_NextCameraTag = L"";
    CTransform* m_pNextCameraTransform = nullptr;
    _float4x4  m_pCurCameraTransform;

    //계산 후에 실제로 트랜스폼에 넣을 방벡,위치벡
    _float3     m_vLook;
    _float3     m_vUp;
    _float3     m_vRight;
    _float3     m_vPos;
    
    _float3     m_vdLook;
    _float3     m_vdUp;
    _float3     m_vdRight;
    _float3     m_vdPos;

    _float      m_fTime=0.f;
    _float      m_fLerpTime = 0.016f;

    _bool       m_bFlag = false;
    _bool       m_bSwitchPlayer = false;
  

public:
    static CCam_Free* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;

};

END

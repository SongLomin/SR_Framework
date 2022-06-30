#pragma once
#include "Base.h"

BEGIN(Engine)

class CTransform;
class CCamera;
class CGameObject;

class CCamera_Manager :
    public CBase
{
    DECLARE_SINGLETON(CCamera_Manager)

private:
    CCamera_Manager() = default;
    virtual ~CCamera_Manager() = default;

public:
    void Register_Camera(const _tchar* _CameraTag, CCamera* _CameraCom);
    void Set_Target(CTransform* _Target = nullptr, const _tchar* _CameraTag = TEXT(""));
    CCamera* Get_Camera(const _tchar* _CameraTag = TEXT(""));
    void Set_Current_Camera(const _tchar* _CameraTag = TEXT(""));
    void Add_Shaking(_float _fOffset, _float _fInclination);

    
    void Update_MovingCam()
    {
        m_pTempCam = m_pCurrentCam;
        Set_Current_Camera(TEXT("Moving"));
    }

    void Swap_Camera()
    {
        m_pCurrentCam = m_pTempCam;
    }

    void Set_MovingCam(CGameObject* _pMovingCam)
    {
        m_pMovingCam = _pMovingCam;
    }
    CGameObject* Get_MovingCam()
    {
        return m_pMovingCam;
    }

public:
    void Tick(_float fTimeDelta);
    void LateTick(_float fTimeDelta);

private:
    void Clear_Empty_Camera();
    void Shake(_float fTimeDelta);
    void RandomVec(_float3* _vDir, float _flowBound, float _fHighBound);

private:
    map<const _tchar*, class CCamera*>	m_Cams;

    CGameObject* m_pMovingCam = nullptr;

    CCamera* m_pCurrentCam = nullptr;
    CCamera* m_pTempCam = nullptr;

    _float  m_fOffset = 0.f;
    _float  m_fInclination = 0.f;
   // _float  m_fTime=0.f;

public:
    virtual void Free() override;
};

END
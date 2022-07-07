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

    
    void Update_MovingCam()//연출용 카메라로 바꿈
    {
        m_pTempCam = m_pCurrentCam;
        Set_Current_Camera(TEXT("Moving"));
    }

    void Swap_Camera()//연출이 모두 끝나고 나면 다시 원래 카메라로 돌아옴
    {
        m_pCurrentCam = m_pTempCam;
    }

    void Set_MovingCam(CGameObject* _pMovingCam)//연출용 카메라 생성시 카메라 매니저에 지정해줌
    {
        m_pMovingCam = _pMovingCam;
    }
    CGameObject* Get_MovingCam()//현재 연출용 카메라로 쓰는 오브젝트 반환
    {
        return m_pMovingCam;
    }

public:
    void    Switch_Camera(const _tchar* _CameraTag, _float _fTime);
    void    Switch_Player(CTransform* _pCurCamera, CTransform* _pNextCamera, const _tchar* _NextCameraTag, _float fTime);


public:
    void Tick(_float fTimeDelta);
    void LateTick(_float fTimeDelta);

private:
    void Clear_Empty_Camera();
   
private:
    map<const _tchar*, class CCamera*>	m_Cams;

    CGameObject* m_pMovingCam = nullptr;
    CGameObject* m_pFreeCam = nullptr;//Free Camera

    CCamera* m_pCurrentCam = nullptr;
    CCamera* m_pTempCam = nullptr;

 
public:
    virtual void Free() override;
};

END
#pragma once
#include "Base.h"

BEGIN(Engine)

class CTransform;
class CCamera;

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

public:
    void Tick(_float fTimeDelta);
    void LateTick(_float fTimeDelta);

private:
    void Clear_Empty_Camera();

private:
    map<const _tchar*, class CCamera*>	m_Cams;
    CCamera* m_pCurrentCam = nullptr;
    //CGameObject* m_pMovingCam = nullptr;

public:
    virtual void Free() override;
};

END
#pragma once
#include "Base.h"

BEGIN(Engine)

class CCamera_Manager :
    public CBase
{
    DECLARE_SINGLETON(CCamera_Manager)

private:
    CCamera_Manager() = default;
    virtual ~CCamera_Manager() = default;

public:


private:
    map<const _tchar*, class CGameObject*>	m_Cams;
    CGameObject* m_pCurrentCam = nullptr;
    CGameObject* m_pDummy = nullptr;
};

END
#pragma once
#include "Base.h"

BEGIN(Engine)

class CTime_Manager final :
    public CBase
{
    DECLARE_SINGLETON(CTime_Manager)
private:
    CTime_Manager() = default;
    virtual ~CTime_Manager() = default;

public:


private:

};

END
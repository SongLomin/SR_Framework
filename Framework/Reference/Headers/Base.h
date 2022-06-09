#pragma once

#include "Engine_Defines.h"

BEGIN(Engine)

class ENGINE_DLL CBase abstract
{
//protected:
//	CBase();
//	virtual ~CBase() = default;
//public:
//	unsigned long AddRef();
//	unsigned long Release();
//
//protected:
//	unsigned long		m_dwRefCnt = 0;
//
public:
	void	Set_WeakPtr(void** WeakPtr);
	virtual void Free();

private:
	list<void**> m_WeakList;
};

END


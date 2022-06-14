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
	template<typename T>
	void	Set_WeakPtr(T** WeakPtr)
	{
		m_WeakList.push_back((void**)WeakPtr);
	}

	//참조 포인터의 인스턴스가 원본보다 먼저 삭제되는 경우 사용 해제를 해줘야 합니다.
	//예) 몬스터가 플레이어를 참조한다. 몬스터가 먼저 삭제된 경우엔 플레이어 참조 포인터를 사용 해제함.
	template<typename T>
	void	Return_WeakPtr(T** WeakPtr)
	{
		m_WeakList.remove((void**)WeakPtr);
	}

	virtual void Free();

private:
	list<void**> m_WeakList;
};

END


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
		m_WeakList.push_back((CBase**)WeakPtr);

		if (m_iLastWeakCnt + 200 <= m_WeakList.size())
		{
			printf("Warning! the instance had too many weakptrs\t %s : \t%d\n", typeid(*this).name(), m_WeakList.size());
			m_iLastWeakCnt += 200;
		}

		

	}

	//참조 포인터의 인스턴스가 원본보다 먼저 삭제되는 경우 사용 해제를 해줘야 합니다.
	//예) 몬스터가 플레이어를 참조한다. 몬스터가 먼저 삭제된 경우엔 플레이어 참조 포인터를 사용 해제함.
	template<typename T>
	void	Return_WeakPtr(T** WeakPtr)
	{
		m_WeakList.remove((CBase**)WeakPtr);
	}

	virtual void Free();

public:
	//해당 객체의 활성화 상태를 바꿉니다. 활성화 상태가 변한다면 OnEnable / OnDisable 이벤트 함수를 호출합니다.
	void Set_Enable(_bool _Enable, void* _Arg = nullptr);
	bool Get_Enable();

public:
	//객체의 상태가 활성화 상태로 변경될 때, 호출되는 이벤트입니다.
	virtual void OnEnable(void* _Arg = nullptr) {};

	//객체의 상태가 비활성화 상태로 변경될 때, 호출되는 이벤트입니다.
	virtual void OnDisable() {};

	virtual void OnTimerEvent(const _uint _iEventIndex) {};

private:
	list<CBase**>	m_WeakList;
	_bool			m_bEnable = true;
	_uint			m_iLastWeakCnt = 0;
};

END


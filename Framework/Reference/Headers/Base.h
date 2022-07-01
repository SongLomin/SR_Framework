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

	//���� �������� �ν��Ͻ��� �������� ���� �����Ǵ� ��� ��� ������ ����� �մϴ�.
	//��) ���Ͱ� �÷��̾ �����Ѵ�. ���Ͱ� ���� ������ ��쿣 �÷��̾� ���� �����͸� ��� ������.
	template<typename T>
	void	Return_WeakPtr(T** WeakPtr)
	{
		m_WeakList.remove((void**)WeakPtr);
	}

	virtual void Free();

public:
	//�ش� ��ü�� Ȱ��ȭ ���¸� �ٲߴϴ�. Ȱ��ȭ ���°� ���Ѵٸ� OnEnable / OnDisable �̺�Ʈ �Լ��� ȣ���մϴ�.
	void Set_Enable(_bool _Enable, void* _Arg = nullptr);
	bool Get_Enable();

public:
	//��ü�� ���°� Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
	virtual void OnEnable(void* _Arg = nullptr) {};

	//��ü�� ���°� ��Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
	virtual void OnDisable() {};

private:
	list<void**>	m_WeakList;
	_bool			m_bEnable = true;
};

END


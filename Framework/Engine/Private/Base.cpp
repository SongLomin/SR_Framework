#include "..\Public\Base.h"

void CBase::Set_WeakPtr(void** WeakPtr)
{
	m_WeakList.push_back(WeakPtr);
}

//CBase::CBase()
//{
//	int a = 10;
//}
//
//unsigned long CBase::AddRef()
//{
//	return ++m_dwRefCnt;	
//}
//
//unsigned long CBase::Release()
//{
//	if (0 == m_dwRefCnt)
//	{
//		Free();
//
//		delete this;
//
//		return 0;
//	}
//	else
//	{
//		return m_dwRefCnt--;
//	}
//
//
//	
//}
//
void CBase::Free()
{
	for (auto& elem : m_WeakList)
	{
		(*elem) = nullptr;
	}

	m_WeakList.clear();
}

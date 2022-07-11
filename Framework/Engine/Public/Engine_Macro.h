#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_DLL _declspec(dllexport)
#else
#define ENGINE_DLL _declspec(dllimport)
#endif

#define MSG_BOX(MESSAGE) MessageBox(0, TEXT(MESSAGE), TEXT("System Error"), MB_OK)


#define BEGIN(NAMESPACE) namespace NAMESPACE { 
#define END }


#define NO_COPY(ClassName)								\
ClassName(const ClassName&) = delete;					\
ClassName& operator=(const ClassName&) = delete;

#define DECLARE_SINGLETON(ClassName)					\
		NO_COPY(ClassName)								\
public :												\
	static ClassName* Get_Instance();					\
	static void Destroy_Instance();			\
private:												\
	static ClassName* m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)					\
ClassName* ClassName::m_pInstance = nullptr;			\
ClassName* ClassName::Get_Instance()					\
{														\
	if (nullptr == m_pInstance)							\
		m_pInstance = new ClassName;					\
	return m_pInstance;									\
}														\
void ClassName::Destroy_Instance()						\
{														\
	return Safe_Release(m_pInstance);					\
}

#define LPDEVICE (CGameInstance::Get_Instance()->Get_Device())
#define DEVICE (*(LPDEVICE))
#define GAMEINSTANCE CGameInstance::Get_Instance()

#define ISVALID(instance, return_type) if(instance == nullptr) return return_type;

#define CURRENT_LEVEL GAMEINSTANCE->Get_CurrentLevelIndex()

#define CURRENT_CAMERA TEXT("")

#define KEY_INPUT GAMEINSTANCE->Is_KeyState

#define CREATE_PIPELINE(ClassName)						\
	ClassName* pInstance = new ClassName();				\
	if (FAILED(pInstance->Initialize_Prototype()))		\
	{													\
		MSG_BOX("Failed to Create.");					\
	}													\
	return pInstance;									

#define CLONE_PIPELINE(ClassName)						\
	ClassName* pInstance = new ClassName(*this);		\
	if (FAILED(pInstance->Initialize(pArg)))			\
	{													\
		MSG_BOX("Failed to Cloned.");		\
		Safe_Release(pInstance);						\
	}													\
	return pInstance;		

#define WEAK_PTR(Instance) if(Instance) Instance->Set_WeakPtr(&Instance)
#define RETURN_WEAKPTR(Instance) if(Instance) Instance->Return_WeakPtr(&Instance)

#define TIMEDELTA GAMEINSTANCE->Get_UnScaledTimeDelta() * GAMEINSTANCE->Get_TimeScale()
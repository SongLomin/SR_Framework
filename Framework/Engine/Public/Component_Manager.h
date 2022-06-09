#pragma once



/* 컴포넌트들의 원형을 가지고 있는다. */
#include "Renderer.h"
#include "VIBuffer_Rect.h"
#include "Transform.h"

BEGIN(Engine)

class CComponent_Manager final : public CBase
{
	DECLARE_SINGLETON(CComponent_Manager)
public:
	CComponent_Manager();
	virtual ~CComponent_Manager() = default;

public:
	//HRESULT Reserve_Container(_uint iNumLevels);
	CComponent** Add_Prototype(const _char* pPrototypeTag, class CComponent* pPrototype);


private:
	_uint			m_iNumLevels = 0;

	map<const _char*, class CComponent*>				m_pPrototypes;
	typedef map<const _char*, class CComponent*>		PROTOTYPES;

private:
	class CComponent** Find_Components(const _char* pPrototypeTag);

public:
	virtual void Free() override;

public: /* Template Function*/
	template <typename T>
	T* Clone_Component(void* pArg)
	{
		/*
		T가 컴포넌트를 상속 받는지 검사합니다.
		왜? T에 컴포넌트가 아닌 다른 클래스가 들어오는 것을 사전에 방지합니다.
		*/
		if (!is_base_of<CComponent, T>::value)
		{
			MessageBox(g_hWnd, TEXT("T isn't base of CComponent : CComponent_Manager"), TEXT("System Error"), MB_OK);
			return nullptr;
		}
		
		CComponent** pPrototype = nullptr;
		/*Find_Components*/
		auto	iter = find_if(m_pPrototypes.begin(), m_pPrototypes.end(), CTag_Finder_c_str(typeid(T).name()));

		if (iter != m_pPrototypes.end())
		{
			pPrototype = &iter->second;
		}

		if (nullptr == pPrototype)
		{
			/*Add_Prototype*/
			CComponent* T_Instance = T::Create();

			m_pPrototypes.emplace(typeid(T).name(), T_Instance);

			return static_cast<T*>(T_Instance->Clone(pArg));
		}

		return static_cast<T*>((*pPrototype)->Clone(pArg));
	}
};

END
#pragma once



/* 컴포넌트들의 원형을 가지고 있는다. */
#include "Renderer.h"
#include "VIBuffer_Rect.h"
#include "VIBuffer_Terrain.h"
#include "VIBuffer_Cube.h"
#include "Transform.h"
#include "Mesh_Cube.h"
#include "Mesh_Terrain.h"
#include "Camera.h"
#include "Status.h"
#include "Font.h"
#include "Rigid_Body.h"
#include "Collider.h"
#include "Collider_OBB.h"
#include "State_Move.h"
#include "Targeting.h"
#include "Mesh_Test.h"
#include "Mesh_SongShip.h"
#include "Collider_Pre.h"
#include "Light.h"
#include "DirectionalLight.h"

BEGIN(Engine)

class CComponent_Manager final : public CBase
{
	DECLARE_SINGLETON(CComponent_Manager)
public:
	CComponent_Manager();
	virtual ~CComponent_Manager() = default;

public:
	//HRESULT Reserve_Container(_uint iNumLevels);
	CComponent* Add_Prototype(const _char* pPrototypeTag, class CComponent* pPrototype);


private:
	_uint			m_iNumLevels = 0;

	map<const _char*, class CComponent*>				m_pPrototypes;
	typedef map<const _char*, class CComponent*>		PROTOTYPES;

private:
	class CComponent* Find_Components(const _char* pPrototypeTag);

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
		static_assert(is_base_of<CComponent, T>::value, "T isn't base of CComponent : CComponent_Manager");
		
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
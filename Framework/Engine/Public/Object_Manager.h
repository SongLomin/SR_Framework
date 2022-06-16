#pragma once

/* 객체들의 원형을 관리하낟. */
/* 원형객체를 찾아서 복제하여 씬(레벨)별로 모아서 관린하다.*/

#include "Base.h"

BEGIN(Engine)

class CTransform;

class CObject_Manager final : public CBase
{
	DECLARE_SINGLETON(CObject_Manager)
private:
	CObject_Manager();
	virtual ~CObject_Manager() = default;

public:
	HRESULT Reserve_Container(_uint iNumLevels);

public:
	/* 원형객체를 추가한다. */
	class CGameObject* Get_Player();


	void Tick(_float fTimeDelta);
	void LateTick(_float fTimeDelta);

public:
	void Clear(_uint iLevelIndex);


private:
	map<const _char*, class CGameObject*>			m_Prototypes;
	typedef map<const _char*, class CGameObject*>	PROTOTYPES;

private:

	map<const _tchar*, list<CGameObject*>>*				m_pLayers = nullptr;
	typedef map<const _tchar*, list<CGameObject*>>	LAYERS;
	_uint					m_iNumLevels = 0;


private:
	class CGameObject* Find_Prototype(const _char* pPrototypeTag);
	list<CGameObject*>* Find_Layer(_uint iLevelIndex, const _tchar* pLayerTag);

public:
	virtual void Free() override;

public: /* Template Function */
	template <typename T>
	T* Add_Prototype()
	{
		static_assert(is_base_of<CGameObject, T>::value, "T Isn't base of CGameObject");

		T* pInstance = T::Create();

		m_Prototypes.emplace(typeid(T).name(), pInstance);

		return pInstance;
	}
	
	template <typename T>
	T* Add_GameObject(_uint iLevelIndex, const _tchar* pLayerTag, CTransform* pParent = nullptr ,void* pArg = nullptr)
	{
		static_assert(is_base_of<CGameObject, T>::value, "T Isn't base of CGameObject");

		if (m_iNumLevels <= iLevelIndex - 1)
		{
			//잘못된 레벨 인덱스
#ifdef _DEBUG
			assert(false);
#endif
			return nullptr;
		}

		CGameObject* pPrototype = nullptr;

		auto iter = find_if(m_Prototypes.begin(), m_Prototypes.end(), CTag_Finder_c_str(typeid(T).name()));

		if (iter != m_Prototypes.end())
		{
			pPrototype = (*iter).second;
		}

		if (nullptr == pPrototype)
		{
			pPrototype = Add_Prototype<T>();
		}

		CGameObject* pCloneObject = pPrototype->Clone(pArg);

		if (nullptr == pCloneObject)
			return nullptr;

		m_pLayers[iLevelIndex][pLayerTag].push_back(pCloneObject);

		if (pParent)
		{
			CTransform* pTransfromCom = pCloneObject->Get_Component<CTransform>();
			pTransfromCom->Set_Parent(pParent);
			pParent->Add_Child(pTransfromCom);
		}

		return static_cast<T*>(pCloneObject);
	}
};

END
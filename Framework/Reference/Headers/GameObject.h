#pragma once

#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CGameObject abstract : public CBase
{
protected:
	CGameObject();	
	CGameObject(const CGameObject& Prototype);
	virtual ~CGameObject() = default;

public:
	virtual HRESULT Initialize_Prototype() PURE;
	virtual HRESULT Initialize(void* pArg) PURE;
	virtual void Tick(_float fTimeDelta) PURE;
	virtual void LateTick(_float fTimeDelta) PURE;
	virtual HRESULT Render() PURE;
	

protected:
	map<const _char*, class CComponent*> m_pComs;

public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;

public: /* Template Function*/
	
	template <typename T>
	T* Get_Component()
	{
		auto iter = find_if(m_pComs.begin(), m_pComs.end(), CTag_Finder_c_str(typeid(T).name()));

		if (m_pComs.end() == iter)
		{
			return nullptr;
		}

		return static_cast<T*>(iter->second);
	}

	template <typename T>
	T* Add_Component(void* pArg = nullptr)
	{
		if (Get_Component<T>() != nullptr)
			assert(false);

		T* temp = CGameInstance::Get_Instance()->Clone_Component<T>(pArg);

		if (nullptr == temp)
		{
			return nullptr;
		}
		temp->Set_Owner(this);
		m_pComs.emplace(typeid(T).name(), temp);

		return temp;
	}
};



END
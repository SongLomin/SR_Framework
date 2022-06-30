#pragma once

#include "Base.h"

BEGIN(Engine)

class CCollider;

class ENGINE_DLL CGameObject abstract : public CBase
{
protected:
	CGameObject();
	CGameObject(const CGameObject& Prototype);
	virtual ~CGameObject() = default;

public:
	virtual HRESULT Initialize_Prototype() PURE;
	virtual HRESULT Initialize(void* pArg) PURE;
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	//렌더 이전 작업 수행 (상수버퍼 세팅)
	virtual HRESULT Render_Begin();
	virtual HRESULT Render();

public:
	void Set_Controller(const CONTROLLER& _eController);
	CONTROLLER Get_Controller() { return m_eController; };

	void Set_Dead();
	bool Get_Dead() const { return m_bDead; }

	void Set_Internal_Tag(const _tchar* _Tag);

public:
	list<CGameObject*> Get_Children_From_Key(const _tchar* _Key);

private:
	void Add_List_Child_From_Key(const _tchar* _Key, list<CGameObject*>& _List);

protected: 
	virtual void On_Change_Controller(const CONTROLLER& _eController);

public: /* For Event Function */
	virtual void On_Collision_Enter(CCollider* _Other_Collider);
	virtual void On_Collision_Stay(CCollider* _Other_Collider);
	virtual void On_Collision_Exit(CCollider* _Other_Collider);

protected:
	map<const _char*, class CComponent*> m_pComs;


private:
	CONTROLLER	m_eController = CONTROLLER::CONTROLLER_END;
	bool m_bDead = false;
	const _tchar* m_Tag;

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

		if (!iter->second->Get_Enable())
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
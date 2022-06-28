#include "..\Public\GameObject.h"
#include "GameInstance.h"
#include <iostream>

CGameObject::CGameObject()
{
	//Safe_AddRef(m_pGraphic_Device);
}

CGameObject::CGameObject(const CGameObject & Prototype)
{
	//Safe_AddRef(m_pGraphic_Device);
}

void CGameObject::Free()
{
	//Safe_Release(m_pGraphic_Device);
	__super::Free();

	for (auto& elem : m_pComs)
	{
		Safe_Release(elem.second);
	}
	
	m_pComs.clear();

	//delete this;
}

void CGameObject::Tick(_float fTimeDelta)
{
	for (auto& elem : m_pComs)
	{
		if (elem.second)
		{
			elem.second->Tick(fTimeDelta);
		}
	}

}

void CGameObject::LateTick(_float fTimeDelta)
{
	for (auto& elem : m_pComs)
	{
		if (elem.second)
		{
			elem.second->LateTick(fTimeDelta);
		}
	}
}

HRESULT CGameObject::Render_Begin()
{
	for (auto& elem : m_pComs)
	{
		if (elem.second)
		{
			elem.second->Render();
		}
	}

	return S_OK;
}

HRESULT CGameObject::Render()
{
	for (auto& elem : m_pComs)
	{
		if (elem.second)
		{
			elem.second->Render();
		}
	}

	return S_OK;
}

void CGameObject::Set_Controller(const CONTROLLER& _eController)
{
	if (m_eController != _eController)
	{
		m_eController = _eController;
		On_Change_Controller(_eController);
	}

	/// 이 아래 코드는 재귀적으로 내 자식들의 컨트롤러를 변경해줌.

	//내 트랜스폼 받기
	CTransform* myTransform = Get_Component<CTransform>();

	//자식 트랜스폼 리스트
	list<CTransform*>* Children = myTransform->Get_Children();

	ISVALID(Children, );

	//걔네 for문
	for (auto& elem : *Children)
	{
		//소유자(GameObject) -> Set_Controller
		elem->Get_Owner()->Set_Controller(_eController);
	}

}

void CGameObject::Set_Dead()
{
	m_bDead = true;

	CTransform* pMyTransform = Get_Component<CTransform>();

	if (!pMyTransform)
	{
		return;
	}

	list<CTransform*>* pMyChildren = pMyTransform->Get_Children();

	for (auto& elem : *pMyChildren)
	{
		elem->Get_Owner()->Set_Dead();
	}

}

void CGameObject::Set_Internal_Tag(const _tchar* _Tag)
{
	m_Tag = _Tag;
}

list<CGameObject*> CGameObject::Get_Children_From_Key(const _tchar* _Key)
{
	list<CGameObject*> Target_Children;

	Add_List_Child_From_Key(_Key, Target_Children);

	return Target_Children;
}

void CGameObject::Add_List_Child_From_Key(const _tchar* _Key, list<CGameObject*>& _List)
{

	CTransform* pMyTransform = Get_Component<CTransform>();

	if (!pMyTransform)
	{
		return;
	}

	//태그가 서로 같으면 리스트에 담아준다.
	if (!lstrcmp(_Key, m_Tag))
	{
		_List.push_back(this);
	}

	for (auto& elem : *pMyTransform->Get_Children())
	{
		elem->Get_Owner()->Add_List_Child_From_Key(_Key, _List);
	}

}




//컨트롤러가 변경될 때 호출된다.
void CGameObject::On_Change_Controller(const CONTROLLER& _IsAI)
{
	//do nothing.
}

void CGameObject::On_Collision_Enter(CCollider* _Other_Collider)
{
}

void CGameObject::On_Collision_Stay(CCollider* _Other_Collider)
{
}

void CGameObject::On_Collision_Exit(CCollider* _Other_Collider)
{
}

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

void CGameObject::Set_Controller(const bool& _IsAI)
{
	m_IsAI = _IsAI;

	//내 트랜스폼 받기
	CTransform* myTransform = Get_Component<CTransform>();

	//자식 트랜스폼 리스트
	list<CTransform*>* Children = myTransform->Get_Children();

	ISVALID(Children, );

	//걔네 for문
	for (auto& elem : *Children)
	{
		//소유자(GameObject) -> Set_Controller
		elem->Get_Owner()->Set_Controller(_IsAI);
	}

}

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

	//�� Ʈ������ �ޱ�
	CTransform* myTransform = Get_Component<CTransform>();

	//�ڽ� Ʈ������ ����Ʈ
	list<CTransform*>* Children = myTransform->Get_Children();

	ISVALID(Children, );

	//�³� for��
	for (auto& elem : *Children)
	{
		//������(GameObject) -> Set_Controller
		elem->Get_Owner()->Set_Controller(_IsAI);
	}

}

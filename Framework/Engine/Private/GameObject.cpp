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
	m_eController = _eController;
	On_Change_Controller(_eController);

	//�� Ʈ������ �ޱ�
	CTransform* myTransform = Get_Component<CTransform>();

	//�ڽ� Ʈ������ ����Ʈ
	list<CTransform*>* Children = myTransform->Get_Children();

	ISVALID(Children, );

	//�³� for��
	for (auto& elem : *Children)
	{
		//������(GameObject) -> Set_Controller
		elem->Get_Owner()->Set_Controller(_eController);
	}

}

//��Ʈ�ѷ��� ����� �� ȣ��ȴ�.
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

#include "Collision_Manager.h"
#include "GameObject.h"
#include "GameInstance.h"
#include "Collider.h"

IMPLEMENT_SINGLETON(CCollision_Manager)

CCollision_Manager::CCollision_Manager()
	:m_arrCheck{}
{
}

void CCollision_Manager::Initialize()
{
	CheckGroup(COLLISION_TYPE::PLAYER_ATTACK, COLLISION_TYPE::MONSTER);
	CheckGroup(COLLISION_TYPE::MONSTER_ATTACK, COLLISION_TYPE::PLAYER);

	//CheckGroup(COLLISION_TYPE::PLAYER_ATTACK, COLLISION_TYPE::PLAYER_ATTACK);
	//CheckGroup(COLLISION_TYPE::PLAYER, COLLISION_TYPE::MONSTER);
	//CheckGroup(COLLISION_TYPE::MONSTER, COLLISION_TYPE::MONSTER);
}

void CCollision_Manager::Tick()
{
	for (UINT iRow = 0; iRow < (UINT)COLLISION_TYPE::TYPE_END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)COLLISION_TYPE::TYPE_END; ++iCol) // üũ �ڽ� �ݸ� �ؾߵǱ� ������ �÷��� row����
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((COLLISION_TYPE)iRow, (COLLISION_TYPE)iCol);
			}
		}
	}

	Clear_ColliderList();
}

void CCollision_Manager::CheckGroup(COLLISION_TYPE _eLeft, COLLISION_TYPE _eRight)
{
	UINT iRow = (UINT)_eLeft; // ��
	UINT iCol = (UINT)_eRight; // ��

	if (iRow > iCol)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol)) // �̹� �� �ڸ��� 1�̸�
		m_arrCheck[iRow] &= ~(1 << iCol); // ���ְ�
	else
		m_arrCheck[iRow] |= (1 << iCol); // 1�� �÷� ��ŭ �о �־���..?
}

void CCollision_Manager::Reset()
{
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)COLLISION_TYPE::TYPE_END);

	for (UINT i = 0; i < (UINT)COLLISION_TYPE::TYPE_END; ++i)
		m_ColliderList->clear();
}

void CCollision_Manager::Add_Collider(CCollider* pCollider)
{
	m_ColliderList[(UINT)pCollider->Get_Collision_Type()].push_back(pCollider);

	pCollider->Set_WeakPtr(&m_ColliderList[(UINT)pCollider->Get_Collision_Type()].back());
}

void CCollision_Manager::Erase_Collider(CCollider* pCollider)
{
	COLLISION_TYPE collisontype = pCollider->Get_Collision_Type();

	/*for (auto iter = m_ColliderList[(UINT)collisontype].begin(); iter != m_ColliderList[(UINT)collisontype].end(); ++iter)
	{
		if (*iter == pCollider)
		{
			(*iter)->Return_WeakPtr(&(*iter));
			m_ColliderList[(UINT)collisontype].erase(iter);
			break;
		}

	}*/

	m_Erase_ColliderIDList.push_back(pCollider->Get_ID());

	
}

list<CCollider*>* CCollision_Manager::Get_ColliderList(COLLISION_TYPE _eType)
{
	return &m_ColliderList[(_uint)_eType];
}

void CCollision_Manager::Clear_ColliderList()
{
	for (auto& ColliderList_Type : m_ColliderList)
	{
		for (auto& elem_Collider : ColliderList_Type)
		{
			RETURN_WEAKPTR(elem_Collider);
		}

		ColliderList_Type.clear();
	}

	for (_ulong& elem_ID : m_Erase_ColliderIDList)
	{
		for (auto iter = m_mapColInfo.begin(); iter != m_mapColInfo.end();)
		{
			_ulong Collider_ID = elem_ID;

			if (Collider_ID == (*iter).first / 100000
				|| Collider_ID == (*iter).first % 100000)
			{
				iter = m_mapColInfo.erase(iter);
			}

			else
			{
				iter++;
			}
		}
	}
	m_Erase_ColliderIDList.clear();

	
}

void CCollision_Manager::CollisionGroupUpdate(COLLISION_TYPE _eLeft, COLLISION_TYPE _eRight)
{

	map<ULONGLONG, bool>::iterator iter;

	for (auto LeftIter = m_ColliderList[(UINT)_eLeft].begin(); LeftIter != m_ColliderList[(UINT)_eLeft].end(); )
	{
		if (!(*LeftIter))
		{
			LeftIter = m_ColliderList[(UINT)_eLeft].erase(LeftIter);
			continue;
		} //�̹� ������ ��ü�� ����Ʈ���� ����� �ѱ��.

		for (auto RightIter = m_ColliderList[(UINT)_eRight].begin(); RightIter != m_ColliderList[(UINT)_eRight].end(); )
		{
			if (!(*RightIter))
			{
				RightIter = m_ColliderList[(UINT)_eRight].erase(RightIter);
				continue;
			} //�̹� ������ ��ü�� ����Ʈ���� ����� �ѱ��.

			if (*LeftIter == *RightIter) // �� �ڽŰ� �浹 ����
			{
				++RightIter;
				continue;
			}
				

			COLLIDER_ID ID;
			ID.ID = 0;
			ID.Left_id = (*LeftIter)->Get_ID();		// 4����Ʈ
			ID.Right_id = (*RightIter)->Get_ID();		// 4����Ʈ
			//���ļ� ���� 8����Ʈ�� ���� �Ȱ�ħ.
			/*string id_to_string = to_string(ID.Left_id) + to_string(ID.Right_id);

			ID.ID = stoll(id_to_string.c_str());*/

			_ulonglong Byte8ID;

			Byte8ID = (_ulonglong)ID.Left_id * 100000;
			Byte8ID += ID.Right_id;

			iter = m_mapColInfo.find(Byte8ID);

			//�浹 ������ �ƿ� �̵�� ������ ���
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(Byte8ID, false)); // �ƿ� ������� �ȵ��ִ� ��Ȳ�̹Ƿ� �ʿ� �߰�
				iter = m_mapColInfo.find(Byte8ID); // ���� �� �ٽ� ���ͷ� �ް�
			}

			//��¥ �浹 �˻�
			if (Is3DCollision((*LeftIter), (*RightIter)))
			{
				//���� �浹 ��
				if (iter->second) // ���ݵ� �浹���ε� �������� �浹���� ��Ȳ
				{
					if (!(*LeftIter) || !(*RightIter)) // ���� �ϳ��� ��ȿ���� ���� ���
					{
						(*LeftIter)->Get_Owner()->On_Collision_Exit((*RightIter));
						(*RightIter)->Get_Owner()->On_Collision_Exit((*LeftIter));
						iter->second = false;
						//m_mapColInfo.erase(iter);
					}
					else
					{
						(*LeftIter)->Get_Owner()->On_Collision_Stay((*RightIter));
						(*RightIter)->Get_Owner()->On_Collision_Stay((*LeftIter));

					}


				}
				else // �̹��� ���� �浹
				{
					if ((*LeftIter) && (*RightIter)) // �Ѵ� Ȱ��ȭ�� ���� ����
					{
						(*LeftIter)->Get_Owner()->On_Collision_Enter((*RightIter));
						(*RightIter)->Get_Owner()->On_Collision_Enter((*LeftIter));
						iter->second = true;

					}
					else
					{
						//m_mapColInfo.erase(iter);
					}
				}
			}
			else // ���� �浹������ ����
			{
				if (iter->second) // ��ݱ��� �浹���̾���, �浹�� �� ����� ����
				{
					(*LeftIter)->Get_Owner()->On_Collision_Exit((*RightIter));
					(*RightIter)->Get_Owner()->On_Collision_Exit((*LeftIter));
					iter->second = false;
					//m_mapColInfo.erase(iter);
				}
			}

			++RightIter;
		}

		++LeftIter;

	}
}

bool CCollision_Manager::Is3DCollision(CCollider* _pLeft, CCollider* _pRight)
{

	/*if (!IsSphereCollision(_pLeft->Get_Pre_Collider(), _pRight->Get_Pre_Collider()))
	{
		return false;
	}*/


	//if ((_pLeft->Get_Collider_Shape() == COLLIDER_SHAPE::OBB)
	//	&& (_pRight->Get_Collider_Shape() == COLLIDER_SHAPE::OBB))
	//{
	//	return IsOBBCollision(_pLeft, _pRight);
	//}// �簢 - �簢
	//else
	//{
	//	return IsSphereCollision(_pLeft, _pRight);
	//}// �簢 - ��, �� - ��

	return IsSphereCollision(_pLeft, _pRight);
}

bool CCollision_Manager::IsOBBCollision(CCollider* _pLeft, CCollider* _pRight)
{
	OBBINFO	LeftBox = static_cast<CCollider_OBB*>(_pLeft)->Get_OBBInfo();
	OBBINFO	RightBox = static_cast<CCollider_OBB*>(_pRight)->Get_OBBInfo();


	D3DXVECTOR3 Axis_c1[3] = {
		LeftBox.tVertex[1] - LeftBox.tVertex[0],
		LeftBox.tVertex[3] - LeftBox.tVertex[0],
		LeftBox.tVertex[4] - LeftBox.tVertex[0] };

	D3DXVECTOR3 Axis_c2[3] = {
		RightBox.tVertex[1] - RightBox.tVertex[0],
		RightBox.tVertex[3] - RightBox.tVertex[0],
		RightBox.tVertex[4] - RightBox.tVertex[0] };

	// 2. ���� �������� �˻� 
	for (int i = 0; i < 3; ++i)
	{
		// ������ �Ǵ� �� ����
		D3DXVECTOR3 Axis_norm;
		D3DXVec3Normalize(&Axis_norm, &Axis_c1[i]);

		// 2 - 1. �࿡���� ���� A�� B ����
		map<float, UINT> mValue_Right;
		map<float, UINT> mValue_Left;
		UINT minIndex_Right, maxIndex_Right;
		UINT minIndex_Left, maxIndex_Left;

		//���� ª�������� ������ ã�Ƴ���.
		for (int v = 0; v < sizeof(RightBox.tVertex) / sizeof(D3DXVECTOR3); ++v)
		{
			mValue_Right.insert(make_pair(fabsf(D3DXVec3Dot(&Axis_norm, &RightBox.tVertex[v])), v));
			mValue_Left.insert(make_pair(fabsf(D3DXVec3Dot(&Axis_norm, &LeftBox.tVertex[v])), v));
		}


		// �񱳵� ��� ����� �ִ�, ���� ������ Index ��ȣ

		map<float, UINT>::iterator Right_iter;
		Right_iter = mValue_Right.end();
		--Right_iter;

		minIndex_Right = mValue_Right.begin()->second;
		maxIndex_Right = Right_iter->second;

		map<float, UINT>::iterator Left_iter;
		Left_iter = mValue_Left.end();
		--Left_iter;

		minIndex_Left = mValue_Left.begin()->second;
		maxIndex_Left = Left_iter->second;


		// 1, 3, 4 ������ ���� ŭ
		FLOAT A, B, Dist;
		D3DXVECTOR3 vec;

		FLOAT A1 = (D3DXVec3Dot(&Axis_norm, &LeftBox.tVertex[maxIndex_Left]));
		FLOAT A2 = (D3DXVec3Dot(&Axis_norm, &LeftBox.tVertex[minIndex_Left]));

		A = fabs(A1 - A2);


		FLOAT B1 = (D3DXVec3Dot(&Axis_norm, &RightBox.tVertex[maxIndex_Right]));
		FLOAT B2 = (D3DXVec3Dot(&Axis_norm, &RightBox.tVertex[minIndex_Right]));

		B = fabs(B1 - B2);

		A = A * 0.5F;
		B = B * 0.5F;

		// 2 - 2. �� ���������� ���� ������������ ���� Dist ����

		B1 = (D3DXVec3Dot(&Axis_norm, &LeftBox.ObbCenterPos));
		B2 = (D3DXVec3Dot(&Axis_norm, &RightBox.ObbCenterPos));
		Dist = fabsf(B1 - B2);

		// 2 - 3. Dist�� A * 0.5 + B * 0.5 �� ��
		if (Dist > A + B)
			return false; //�浹 ����
		// Dist < A + B �浹 ��
	}

	// 2. ���� �������� �˻� 
	for (int i = 0; i < 3; ++i)
	{
		D3DXVECTOR3 Axis_norm;
		D3DXVec3Normalize(&Axis_norm, &Axis_c2[i]);

		// 2 - 1. �࿡���� ���� A�� B ����
		map<float, UINT> mValue_Right;
		map<float, UINT> mValue_Left;
		UINT minIndex_Right, maxIndex_Right;
		UINT minIndex_Left, maxIndex_Left;

		//���� ª�������� ������ ã�Ƴ���.
		for (int v = 0; v < sizeof(RightBox.tVertex) / sizeof(D3DXVECTOR3); ++v)
		{
			mValue_Right.insert(make_pair(fabsf(D3DXVec3Dot(&Axis_norm, &RightBox.tVertex[v])), v));
			mValue_Left.insert(make_pair(fabsf(D3DXVec3Dot(&Axis_norm, &LeftBox.tVertex[v])), v));
		}


		// �񱳵� ��� ����� �ִ�, ���� ������ Index ��ȣ

		map<float, UINT>::iterator Right_iter;
		Right_iter = mValue_Right.end();
		--Right_iter;

		minIndex_Right = mValue_Right.begin()->second;
		maxIndex_Right = Right_iter->second;

		map<float, UINT>::iterator Left_iter;
		Left_iter = mValue_Left.end();
		--Left_iter;

		minIndex_Left = mValue_Left.begin()->second;
		maxIndex_Left = Left_iter->second;


		// 1, 3, 4 ������ ���� ŭ
		FLOAT A, B, Dist;
		D3DXVECTOR3 vec;

		FLOAT A1 = (D3DXVec3Dot(&Axis_norm, &LeftBox.tVertex[maxIndex_Left]));
		FLOAT A2 = (D3DXVec3Dot(&Axis_norm, &LeftBox.tVertex[minIndex_Left]));

		A = fabs(A1 - A2);


		FLOAT B1 = (D3DXVec3Dot(&Axis_norm, &RightBox.tVertex[maxIndex_Right]));
		FLOAT B2 = (D3DXVec3Dot(&Axis_norm, &RightBox.tVertex[minIndex_Right]));

		B = fabs(B1 - B2);

		A = A * 0.5F;
		B = B * 0.5F;

		// 2 - 2. �� ���������� ���� ������������ ���� Dist ����

		B1 = (D3DXVec3Dot(&Axis_norm, &LeftBox.ObbCenterPos));
		B2 = (D3DXVec3Dot(&Axis_norm, &RightBox.ObbCenterPos));
		Dist = fabsf(B1 - B2);

		// 2 - 3. Dist�� A * 0.5 + B * 0.5 �� ��
		if (Dist > A + B)
			return false; //�浹 ����
	}

	return true;
}

bool CCollision_Manager::IsSphereCollision(CCollider* _pLeft, CCollider* _pRight)
{
	if (!_pLeft || !_pRight)
	{
		return false;
	}

	D3DXVECTOR3 CenterDiff = _pRight->Get_Collider_Position() - _pLeft->Get_Collider_Position();
	float Dist = D3DXVec3Length(&CenterDiff);
	Dist = fabsf(Dist);

	float LeftRadius = _pLeft->Get_Collider_Size().x;
	float RightRadius = _pRight->Get_Collider_Size().x;

	if (Dist > LeftRadius + RightRadius)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool CCollision_Manager::IsOBB_To_SphereCollision(CCollider* _pLeft, CCollider* _pRight)
{
	return false;
}

void CCollision_Manager::Free()
{
	__super::Free();

	delete this;
}

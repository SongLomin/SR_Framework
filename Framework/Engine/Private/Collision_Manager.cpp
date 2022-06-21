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
	CheckGroup(COLLISION_TYPE::PLAYER, COLLISION_TYPE::MONSTER);
	CheckGroup(COLLISION_TYPE::MONSTER, COLLISION_TYPE::MONSTER);
}

void CCollision_Manager::Tick()
{
	for (UINT iRow = 0; iRow < (UINT)COLLISION_TYPE::TYPE_END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)COLLISION_TYPE::TYPE_END; ++iCol) // 체크 박스 반만 해야되기 때문에 컬럼은 row부터
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((COLLISION_TYPE)iRow, (COLLISION_TYPE)iCol);
			}
		}
	}
}

void CCollision_Manager::CheckGroup(COLLISION_TYPE _eLeft, COLLISION_TYPE _eRight)
{
	UINT iRow = (UINT)_eLeft; // 행
	UINT iCol = (UINT)_eRight; // 열

	if (iRow > iCol)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol)) // 이미 그 자리가 1이면
		m_arrCheck[iRow] &= ~(1 << iCol); // 빼주고
	else
		m_arrCheck[iRow] |= (1 << iCol); // 1을 컬럼 만큼 밀어서 넣어줌..?
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

	for (auto iter = m_ColliderList[(UINT)collisontype].begin(); iter != m_ColliderList[(UINT)collisontype].end(); ++iter)
	{
		if (*iter == pCollider)
		{
			m_ColliderList[(UINT)collisontype].erase(iter);
			return;
		}

	}
}

void CCollision_Manager::CollisionGroupUpdate(COLLISION_TYPE _eLeft, COLLISION_TYPE _eRight)
{
	list<CCollider*>& LeftList = m_ColliderList[(UINT)_eLeft];
	list<CCollider*>& RightList = m_ColliderList[(UINT)_eRight];

	map<ULONGLONG, bool>::iterator iter;

	for (auto LeftIter = LeftList.begin(); LeftIter != LeftList.end(); ++LeftIter)
	{
		for (auto RightIter = RightList.begin(); RightIter != RightList.end(); ++RightIter)
		{
			if (*LeftIter == *RightIter) // 나 자신과 충돌 방지
				continue;

			COLLIDER_ID ID;
			ID.Left_id = (*LeftIter)->Get_ID();		// 4바이트
			ID.Right_id = (*RightIter)->Get_ID();		// 4바이트
			//합쳐서 나온 8바이트는 절대 안겹침.

			iter = m_mapColInfo.find(ID.ID);

			//충돌 정보가 아예 미등록 상태인 경우
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false)); // 아예 등록조차 안되있던 상황이므로 맵에 추가
				iter = m_mapColInfo.find(ID.ID); // 넣은 값 다시 이터로 받고
			}

			//진짜 충돌 검사
			if (Is3DCollision((*LeftIter), (*RightIter)))
			{
				//현재 충돌 중
				if (iter->second) // 지금도 충돌중인데 이전에도 충돌중인 상황
				{
					if (!(*LeftIter) || !(*RightIter)) // 둘중 하나가 유효하지 않을 경우
					{
						(*LeftIter)->Get_Owner()->On_Collision_Exit((*RightIter));
						(*RightIter)->Get_Owner()->On_Collision_Exit((*LeftIter));
						iter->second = false;
					}
					else
					{
						(*LeftIter)->Get_Owner()->On_Collision_Stay((*RightIter));
						(*RightIter)->Get_Owner()->On_Collision_Stay((*LeftIter));

					}


				}
				else // 이번에 최초 충돌
				{
					if (!(*LeftIter) && !(*RightIter)) // 둘다 활성화일 때만 실행
					{
						(*LeftIter)->Get_Owner()->On_Collision_Enter((*RightIter));
						(*RightIter)->Get_Owner()->On_Collision_Enter((*LeftIter));
						iter->second = true;

					}
				}
			}
			else // 현재 충돌중이지 않음
			{
				if (iter->second) // 방금까지 충돌중이었음, 충돌이 막 벗어나진 시점
				{
					(*LeftIter)->Get_Owner()->On_Collision_Exit((*RightIter));
					(*RightIter)->Get_Owner()->On_Collision_Exit((*LeftIter));
					iter->second = false;

				}
			}
		}

	}
}

bool CCollision_Manager::Is3DCollision(CCollider* _pLeft, CCollider* _pRight)
{
	if (!(_pLeft->Get_Collider_Shape() == COLLIDER_SHAPE::OBB)
		&& !(_pRight->Get_Collider_Shape() == COLLIDER_SHAPE::OBB))
	{
		return IsOBBCollision(_pLeft, _pRight);
	}// 사각 - 사각
	else
	{
		return IsSphereCollision(_pLeft, _pRight);
	}// 사각 - 원, 원 - 원
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

	// 2. 축을 기준으로 검산 
	for (int i = 0; i < 3; ++i)
	{
		// 기준이 되는 축 생성
		D3DXVECTOR3 Axis_norm;
		D3DXVec3Normalize(&Axis_norm, &Axis_c1[i]);

		// 2 - 1. 축에대한 길이 A와 B 도출
		map<float, UINT> mValue_Right;
		map<float, UINT> mValue_Left;
		UINT minIndex_Right, maxIndex_Right;
		UINT minIndex_Left, maxIndex_Left;

		//가장 짧은길이의 정점을 찾아낸다.
		for (int v = 0; v < sizeof(RightBox.tVertex) / sizeof(D3DXVECTOR3); ++v)
		{
			mValue_Right.insert(make_pair(fabsf(D3DXVec3Dot(&Axis_norm, &RightBox.tVertex[v])), v));
			mValue_Left.insert(make_pair(fabsf(D3DXVec3Dot(&Axis_norm, &LeftBox.tVertex[v])), v));
		}


		// 비교될 상대 대상의 최단, 최장 정점의 Index 번호

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


		// 1, 3, 4 순서로 가장 큼
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

		// 2 - 2. 두 원점에대한 축의 내적연산으로 길이 Dist 도출

		B1 = (D3DXVec3Dot(&Axis_norm, &LeftBox.ObbCenterPos));
		B2 = (D3DXVec3Dot(&Axis_norm, &RightBox.ObbCenterPos));
		Dist = fabsf(B1 - B2);

		// 2 - 3. Dist와 A * 0.5 + B * 0.5 를 비교
		if (Dist > A + B)
			return false; //충돌 안함
		// Dist < A + B 충돌 함
	}

	// 2. 축을 기준으로 검산 
	for (int i = 0; i < 3; ++i)
	{
		D3DXVECTOR3 Axis_norm;
		D3DXVec3Normalize(&Axis_norm, &Axis_c2[i]);

		// 2 - 1. 축에대한 길이 A와 B 도출
		map<float, UINT> mValue_Right;
		map<float, UINT> mValue_Left;
		UINT minIndex_Right, maxIndex_Right;
		UINT minIndex_Left, maxIndex_Left;

		//가장 짧은길이의 정점을 찾아낸다.
		for (int v = 0; v < sizeof(RightBox.tVertex) / sizeof(D3DXVECTOR3); ++v)
		{
			mValue_Right.insert(make_pair(fabsf(D3DXVec3Dot(&Axis_norm, &RightBox.tVertex[v])), v));
			mValue_Left.insert(make_pair(fabsf(D3DXVec3Dot(&Axis_norm, &LeftBox.tVertex[v])), v));
		}


		// 비교될 상대 대상의 최단, 최장 정점의 Index 번호

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


		// 1, 3, 4 순서로 가장 큼
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

		// 2 - 2. 두 원점에대한 축의 내적연산으로 길이 Dist 도출

		B1 = (D3DXVec3Dot(&Axis_norm, &LeftBox.ObbCenterPos));
		B2 = (D3DXVec3Dot(&Axis_norm, &RightBox.ObbCenterPos));
		Dist = fabsf(B1 - B2);

		// 2 - 3. Dist와 A * 0.5 + B * 0.5 를 비교
		if (Dist > A + B)
			return false; //충돌 안함
	}

	return true;
}

bool CCollision_Manager::IsSphereCollision(CCollider* _pLeft, CCollider* _pRight)
{
	D3DXVECTOR3 CenterDiff = _pRight->Get_Collider_Position() - _pLeft->Get_Collider_Position();
	float Dist = D3DXVec3Length(&CenterDiff);
	Dist = fabsf(Dist);

	float LeftRadius = _pLeft->Get_Collider_Size().x * 0.5f;
	float RightRadius = _pRight->Get_Collider_Size().x * 0.5f;

	if (Dist > LeftRadius + RightRadius)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void CCollision_Manager::Free()
{
	__super::Free();

	delete this;
}

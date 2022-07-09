#include "Targeting.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "GameObject.h"

CTargeting::CTargeting()
{
}

void CTargeting::Make_Player_TargetList(list<CGameObject*>* pLayer, CTransform* pTransform, _float fDist)
{
	if (nullptr == pLayer)
		return;

	Clear_Targeting();

	if (m_eTargetMode == TARGETMODE::TARGET_MULTIRAY)
	{
		CTransform* CameraTransform = GAMEINSTANCE->Get_Camera(CURRENT_CAMERA)->Get_Transform();


		for (auto iter = pLayer->begin();
			iter != pLayer->end();
			++iter)
		{
			_float3 MonsterPos = (*iter)->Get_Component<CTransform>()->Get_World_State(CTransform::STATE_POSITION);

			_float3 CameraPos = CameraTransform->Get_World_State(CTransform::STATE_POSITION);


			RAY MouseRay = CMath_Utillity::Get_MouseRayInWorldSpace();
			D3DXVec3Normalize(&MouseRay.Dir, &MouseRay.Dir);

			_float3 MonsterRay = MonsterPos - MouseRay.Pos;

			_float Dotproduct = D3DXVec3Dot(&MouseRay.Dir, &MonsterRay);

			if (Dotproduct > 0.f)
			{
				_float3 Projection = Dotproduct * MouseRay.Dir;

				Projection += MouseRay.Pos;

				_float3 Length = MonsterPos - Projection;

				_float Range = D3DXVec3Length(&Length);



				if (Range < fDist)
				{
					m_pTargeting.emplace(Range, (*iter));
					(*iter)->Set_WeakPtr(&m_pTargeting[Range]);
				}
			}
		}
	}

	if (m_eTargetMode == TARGETMODE::TARGET_MULTIWIDE)
	{
		for (auto iter = pLayer->begin();
			iter != pLayer->end();
			++iter)
		{
			_float3 TargetPos = (*iter)->Get_Component<CTransform>()->Get_World_State(CTransform::STATE_POSITION);
			if (GAMEINSTANCE->IsIn(&TargetPos))
			{
				_float3 MyLook = pTransform->Get_World_State(CTransform::STATE_LOOK);
				_float3 MyPos = pTransform->Get_World_State(CTransform::STATE_POSITION);

				D3DXVec3Normalize(&MyLook, &MyLook);

				_float3 TargetPos = (*iter)->Get_Component<CTransform>()->Get_World_State(CTransform::STATE_POSITION);


				_float3 TargetRay = TargetPos - MyPos;

				_float Dotproduct = D3DXVec3Dot(&TargetRay, &MyLook);

				if (Dotproduct > 0.f)
				{
					_float3 Projection = Dotproduct * MyLook;

					Projection += MyPos;

					_float3 Length = TargetPos - Projection;

					_float Range = D3DXVec3Length(&Length);

					m_pTargeting.emplace(Range, (*iter));
					(*iter)->Set_WeakPtr(&m_pTargeting[Range]);
				}
			}
		}
	}
}

void CTargeting::Make_AI_TargetList(list<CGameObject*>* pTarget, CTransform* pTransform, _float fDist)
{
	if (nullptr == pTarget)
		return;

	for (auto& iter = m_pTargeting.begin(); iter != m_pTargeting.end();)
	{
		
		if (iter->second == nullptr)
		{
			iter = m_pTargeting.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	if (!m_pTargeting.empty())
		return;

	Clear_Targeting();

	_float3 ObjectLook = pTransform->Get_World_State(CTransform::STATE_LOOK);
	_float3 ObjectPos = pTransform->Get_World_State(CTransform::STATE_POSITION);

	D3DXVec3Normalize(&ObjectLook, &ObjectLook);

	for (auto iter = pTarget->begin();
		iter != pTarget->end();
		++iter)
	{
		_float3 TargetPos = (*iter)->Get_Component<CTransform>()->Get_World_State(CTransform::STATE_POSITION);


		_float3 TargetRay = TargetPos - ObjectPos;

		_float Dotproduct = D3DXVec3Dot(&TargetRay, &ObjectLook);

		if (Dotproduct > 0.f)
		{
			_float3 Projection = Dotproduct * ObjectLook;

			Projection += ObjectPos;

			_float3 Length = TargetPos - Projection;

			_float Range = D3DXVec3Length(&Length);


			if (Range < fDist)
			{
				m_pTargeting.emplace(Range, (*iter));
				(*iter)->Set_WeakPtr(&m_pTargeting[Range]);
			}
		}
	}

}

void CTargeting::Make_TargetList_Distance(list<CGameObject*>* pTarget, _float3 _vPosition, _float _fRange)
{//À¯µµÅº ¿ë
	if (nullptr == pTarget)
		return;

	for (auto& iter = m_pTargeting.begin(); iter != m_pTargeting.end();)
	{

		if (iter->second == nullptr)
		{
			iter = m_pTargeting.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	if (!m_pTargeting.empty())
		return;

	Clear_Targeting();


	for (auto iter = pTarget->begin();
		iter != pTarget->end();
		++iter)
	{
		_float3 vTargetPos = (*iter)->Get_Component<CTransform>()->Get_World_State(CTransform::STATE_POSITION);

		_float fDistance = D3DXVec3Length(&(vTargetPos - _vPosition));
		if (_fRange > fDistance)
		{
			m_pTargeting.emplace(fDistance, (*iter));
			(*iter)->Set_WeakPtr(&m_pTargeting[fDistance]);
		}
	}
}

void CTargeting::Add_TargetList_Distance(list<CGameObject*>* pTarget, _float3 _vPosition, _float _fRange, _bool _bIsClear)
{

	if (_bIsClear)
	{
		Clear_Targeting();
	}

	if (!pTarget)
		return;

	for (auto iter = pTarget->begin();
		iter != pTarget->end();
		++iter)
	{
		_float3 vTargetPos = (*iter)->Get_Component<CTransform>()->Get_World_State(CTransform::STATE_POSITION);

		_float fDistance = D3DXVec3Length(&(vTargetPos - _vPosition));
		if (_fRange > fDistance)
		{
			m_pTargeting.emplace(fDistance, (*iter));
			(*iter)->Set_WeakPtr(&m_pTargeting[fDistance]);
		}
	}
}

CGameObject* CTargeting::Get_Nearest_Target_Distance(list<CGameObject*>* pTarget, _float3 _vPosition, _float _fRange)
{
	Clear_Targeting();

	if (!pTarget)
		return nullptr;

	for (auto iter = pTarget->begin();
		iter != pTarget->end();
		++iter)
	{
		_float3 vTargetPos = (*iter)->Get_Component<CTransform>()->Get_World_State(CTransform::STATE_POSITION);

		_float fDistance = D3DXVec3Length(&(vTargetPos - _vPosition));
		if (_fRange > fDistance)
		{
			m_pTargeting.emplace(fDistance, (*iter));
			(*iter)->Set_WeakPtr(&m_pTargeting[fDistance]);
		}
	}

	return nullptr;
}

bool CTargeting::IsTargetEmpty()
{
	for (auto& iter = m_pTargeting.begin(); iter != m_pTargeting.end();)
	{

		if (iter->second == nullptr)
		{
			iter = m_pTargeting.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	return m_pTargeting.empty();
}



void CTargeting::Clear_Targeting()
{
	//return_Weakptr

	/*for (auto iter = m_pTargeting.begin(); iter != m_pTargeting.end();)
	{
		if (iter->second)
		{
			iter->second->Return_WeakPtr(&m_pTargeting[iter->first]);
		}
	}*/

	for (auto& elem : m_pTargeting)
	{
		if (elem.second)
			elem.second->Return_WeakPtr(&elem.second);
	}
	m_pTargeting.clear();
}


CTargeting* CTargeting::Create()
{
	CREATE_PIPELINE(CTargeting);
}

CComponent* CTargeting::Clone(void* pArg)
{
	CLONE_PIPELINE(CTargeting);
}

void CTargeting::Free()
{
	__super::Free();

	for (auto& elem : m_pTargeting)
	{
		if (elem.second)
			elem.second->Return_WeakPtr(&elem.second);
	}
	m_pTargeting.clear();


	delete this;
}

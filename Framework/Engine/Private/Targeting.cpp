#include "Targeting.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "GameObject.h"

CTargeting::CTargeting()
{
}

void CTargeting::Make_TargetList(list<CGameObject*>* pLayer, _float fDist)
{
	if (nullptr == pLayer)
		return;

	Clear_Targeting();

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


void CTargeting::Clear_Targeting()
{
	//return_Weakptr
	for (auto& elem : m_pTargeting)
	{
		if(elem.second)
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

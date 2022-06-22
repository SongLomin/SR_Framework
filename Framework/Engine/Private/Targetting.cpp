#include "Targetting.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "GameObject.h"

CTargetting::CTargetting()
{
}



void CTargetting::Update_Targetting()
{
	m_pTargetting.clear();
}

void CTargetting::Make_TargetList(list<CGameObject*>* pLayer)
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

			_float3 Lenght = MonsterPos - Projection;

			_float Range = D3DXVec3Length(&Lenght);



			if (Range < 7.f)
			{
				m_pTargetting.push_back(*iter);

				for (auto iter : m_pTargetting)
				{
					
					_float3 vWorldPos = (*iter).Get_Component<CTransform>()->Get_World_State(CTransform::STATE_POSITION);
					CMath_Utillity::WorldToScreen(&vWorldPos, &vWorldPos);
					
					GAMEINSTANCE->Add_Text(
						_point{ (long)vWorldPos.x, 
						(long)vWorldPos.y},
						D3DCOLOR_ARGB(255, 130, 255, 0),
						0.0f,
						L"Targetting SUCCESS !",
						1);

				}
			}
		}
	}
}


CTargetting* CTargetting::Create()
{
	CREATE_PIPELINE(CTargetting);
}

CComponent* CTargetting::Clone(void* pArg)
{
	CLONE_PIPELINE(CTargetting);
}

void CTargetting::Free()
{
	__super::Free();

	delete this;
}

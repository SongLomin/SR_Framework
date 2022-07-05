#include "stdafx.h"
#include "Planet_Venus.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "Level_Loading.h"
CPlanet_Venus::CPlanet_Venus()
{
}

CPlanet_Venus::CPlanet_Venus(const CPlanet_Venus& Prototype)
{
	*this = Prototype;
}

HRESULT CPlanet_Venus::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CPlanet_Venus::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(1.f, 100.f, 300.f));


	return S_OK;
}

void CPlanet_Venus::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	_float3 MouseEndPos;
	RAY	MouseWorldPos;
	MouseWorldPos = CMath_Utillity::Get_MouseRayInWorldSpace();
	MouseEndPos = MouseWorldPos.Pos + (MouseWorldPos.Dir * 10000.f);

	if (KEY_INPUT(KEY::LBUTTON, KEY_STATE::HOLD) && !m_bLevelChange)
	{
		if (true == CMath_Utillity::Picking_VIBuffer(m_pVIBufferCom, m_pTransformCom, MouseWorldPos, &MouseEndPos))
		{
			GAMEINSTANCE->Get_CurrentLevel()->Change_Level(this);
			m_bLevelChange = true;
			return;
		}

	}

	CCamera* pCurrentCam = GAMEINSTANCE->Get_Camera();

	ISVALID(pCurrentCam, );

	_float3 CamWorldPos = pCurrentCam->Get_Transform()->Get_World_State(CTransform::STATE_POSITION);
	_float3 MyWorldPos;
	MyWorldPos.x = 1.f + CamWorldPos.x;
	MyWorldPos.y = 100.f + CamWorldPos.y;
	MyWorldPos.z = 300.f + CamWorldPos.z;


	m_pTransformCom->Set_State(CTransform::STATE_POSITION, MyWorldPos, true);
	
}

void CPlanet_Venus::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);


	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);

	LookAtCamera();

}

HRESULT CPlanet_Venus::Render()
{
	m_pTransformCom->Scaling(_float3(80.f, 80.f, 50.f), true);

	m_pTransformCom->Bind_WorldMatrix();

	_float3 ScreenPos = _float3(0.f, 0.f, 0.f);

	CMath_Utillity::WorldToScreen(&m_pTransformCom->Get_State(CTransform::STATE_POSITION, true), &ScreenPos);



	_float3 Look = m_pTransformCom->Get_State(CTransform::STATE_LOOK, true);

	//GAMEINSTANCE->Add_Text(_point{ (LONG)ScreenPos.x, (LONG)ScreenPos.y }, TEXT("%d, %d, %d"), 3, (_uint)Look.x, (_uint)Look.y, (_uint)Look.z);

	GAMEINSTANCE->Add_Text(_point{ (LONG)ScreenPos.x + 20, (LONG)ScreenPos.y }, TEXT("Venus Planet \n 저 위험 구역 \n 임무 : 기체 조작연습  \n 난이도 :『★』 \n 보상 : XXX"), 0);

	m_pRendererCom->Bind_Texture(0);

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 253);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pVIBufferCom->Render();

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pRendererCom->UnBind_Texture();



	return S_OK;
}


HRESULT CPlanet_Venus::SetUp_Components()
{

	Add_Component<CTransform>();

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);
	m_pRendererCom->Set_Textures_From_Key(TEXT("Planet"), MEMORY_TYPE::MEMORY_STATIC);


	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);

	return S_OK;
}

void CPlanet_Venus::LookAtCamera()
{
	_float4x4		ViewMatrix;

	DEVICE->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, *(_float3*)&ViewMatrix.m[0][0], true);
	m_pTransformCom->Set_State(CTransform::STATE_UP, *(_float3*)&ViewMatrix.m[1][0], true);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, *(_float3*)&ViewMatrix.m[2][0], true);

}

CPlanet_Venus* CPlanet_Venus::Create()
{
	CREATE_PIPELINE(CPlanet_Venus);
}

CGameObject* CPlanet_Venus::Clone(void* pArg)
{
	CLONE_PIPELINE(CPlanet_Venus);
}

void CPlanet_Venus::Free()
{
	__super::Free();

	RETURN_WEAKPTR(m_pTransformCom);
	RETURN_WEAKPTR(m_pRendererCom);
	RETURN_WEAKPTR(m_pVIBufferCom);

	delete this;
}

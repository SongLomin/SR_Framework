#include "stdafx.h"
#include "Planet_Sun.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "Level_Loading.h"


CPlanet_Sun::CPlanet_Sun()
{
}

CPlanet_Sun::CPlanet_Sun(const CPlanet_Sun& Prototype)
{
	*this = Prototype;
}

HRESULT CPlanet_Sun::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CPlanet_Sun::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(200.f, 100.f, 400.f));


	return S_OK;
}

void CPlanet_Sun::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	_float3 MouseEndPos;
	RAY	MouseWorldPos;
	MouseWorldPos = CMath_Utillity::Get_MouseRayInWorldSpace();
	MouseEndPos = MouseWorldPos.Pos + (MouseWorldPos.Dir * 10000.f);

	if (KEY_INPUT(KEY::LBUTTON, KEY_STATE::HOLD))
	{

		/*if (true == CMath_Utillity::Picking_VIBuffer(m_pVIBufferCom, m_pTransformCom, MouseWorldPos, &MouseEndPos))
		{
			if (FAILED(GAMEINSTANCE->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(LEVEL_GAMEPLAY))))
				return;
		}*/


	}

	_float3 CamWorldPos = GAMEINSTANCE->Get_Camera()->Get_Transform()->Get_World_State(CTransform::STATE_POSITION);
	_float3 MyWorldPos;
	MyWorldPos.x = 200.f + CamWorldPos.x;
	MyWorldPos.y = 100.f + CamWorldPos.y;
	MyWorldPos.z = 400.f + CamWorldPos.z;


	m_pTransformCom->Set_State(CTransform::STATE_POSITION, MyWorldPos, true);

}

void CPlanet_Sun::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);


	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);

	LookAtCamera();

}

HRESULT CPlanet_Sun::Render()
{
	m_pTransformCom->Scaling(_float3(100.f, 100.f, 50.f), true);

	m_pTransformCom->Bind_WorldMatrix();

	_float3 ScreenPos = _float3(0.f, 0.f, 0.f);

	CMath_Utillity::WorldToScreen(&m_pTransformCom->Get_State(CTransform::STATE_POSITION, true), &ScreenPos);

	GAMEINSTANCE->Add_Text(_point{ (LONG)ScreenPos.x + 40, (LONG)ScreenPos.y - 10 }, TEXT("Sun \n 보스 구역 \n [Warring]"), 0);
	
	m_pRendererCom->Bind_Texture(4);

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 253);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pVIBufferCom->Render();

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pRendererCom->UnBind_Texture();



	return S_OK;
}


HRESULT CPlanet_Sun::SetUp_Components()
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

void CPlanet_Sun::LookAtCamera()
{
	_float4x4		ViewMatrix;

	DEVICE->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, *(_float3*)&ViewMatrix.m[0][0], true);
	m_pTransformCom->Set_State(CTransform::STATE_UP, *(_float3*)&ViewMatrix.m[1][0], true);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, *(_float3*)&ViewMatrix.m[2][0], true);

}

CPlanet_Sun* CPlanet_Sun::Create()
{
	CREATE_PIPELINE(CPlanet_Sun);
}

CGameObject* CPlanet_Sun::Clone(void* pArg)
{
	CLONE_PIPELINE(CPlanet_Sun);
}

void CPlanet_Sun::Free()
{
	__super::Free();

	RETURN_WEAKPTR(m_pTransformCom);
	RETURN_WEAKPTR(m_pRendererCom);
	RETURN_WEAKPTR(m_pVIBufferCom);

	delete this;
}

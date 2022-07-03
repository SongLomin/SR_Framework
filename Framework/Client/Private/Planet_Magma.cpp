#include "stdafx.h"
#include "Planet_Magma.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "Level_Loading.h"


CPlanet_Magma::CPlanet_Magma()
{
}

CPlanet_Magma::CPlanet_Magma(const CPlanet_Magma& Prototype)
{
	*this = Prototype;
}

HRESULT CPlanet_Magma::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CPlanet_Magma::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(300.f, 150.f, 200.f));


	return S_OK;
}

void CPlanet_Magma::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	_float3 MouseEndPos;
	RAY	MouseWorldPos;
	MouseWorldPos = CMath_Utillity::Get_MouseRayInWorldSpace();
	MouseEndPos = MouseWorldPos.Pos + (MouseWorldPos.Dir * 10000.f);

	if (KEY_INPUT(KEY::LBUTTON, KEY_STATE::HOLD))
	{

		if (true == CMath_Utillity::Picking_VIBuffer(m_pVIBufferCom, m_pTransformCom, MouseWorldPos, &MouseEndPos))
		{
			GAMEINSTANCE->Get_CurrentLevel()->Change_Level();
			return;
		}
	}

	_float3 CamWorldPos = GAMEINSTANCE->Get_Camera()->Get_Transform()->Get_World_State(CTransform::STATE_POSITION);
	_float3 MyWorldPos;
	MyWorldPos.x = 300.f + CamWorldPos.x;
	MyWorldPos.y = 150.f + CamWorldPos.y;
	MyWorldPos.z = 200.f + CamWorldPos.z;


	m_pTransformCom->Set_State(CTransform::STATE_POSITION, MyWorldPos, true);


}

void CPlanet_Magma::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);


	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);

	LookAtCamera();

}

HRESULT CPlanet_Magma::Render()
{
	m_pTransformCom->Scaling(_float3(100.f, 100.f, 50.f), true);

	m_pTransformCom->Bind_WorldMatrix();

	_float3 ScreenPos = _float3(0.f, 0.f, 0.f);

	CMath_Utillity::WorldToScreen(&m_pTransformCom->Get_State(CTransform::STATE_POSITION, true), &ScreenPos);

	GAMEINSTANCE->Add_Text(_point{ (LONG)ScreenPos.x + 40, (LONG)ScreenPos.y - 10 }, TEXT("Margma Planet \n 고 위험 구역 \n 임무 : 제한 시간 내 모든 기체 파괴  \n 난이도 :『★★★★★★』 \n 보상 : XXX"), 0);

	m_pRendererCom->Bind_Texture(2);

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 253);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pVIBufferCom->Render();

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pRendererCom->UnBind_Texture();



	return S_OK;
}


HRESULT CPlanet_Magma::SetUp_Components()
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

void CPlanet_Magma::LookAtCamera()
{
	_float4x4		ViewMatrix;

	DEVICE->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, *(_float3*)&ViewMatrix.m[0][0], true);
	m_pTransformCom->Set_State(CTransform::STATE_UP, *(_float3*)&ViewMatrix.m[1][0], true);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, *(_float3*)&ViewMatrix.m[2][0], true);

}

CPlanet_Magma* CPlanet_Magma::Create()
{
	CREATE_PIPELINE(CPlanet_Magma);
}

CGameObject* CPlanet_Magma::Clone(void* pArg)
{
	CLONE_PIPELINE(CPlanet_Magma);
}

void CPlanet_Magma::Free()
{
	__super::Free();

	RETURN_WEAKPTR(m_pTransformCom);
	RETURN_WEAKPTR(m_pRendererCom);
	RETURN_WEAKPTR(m_pVIBufferCom);

	delete this;
}


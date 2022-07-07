#include "stdafx.h"
#include "Planet_Exo.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "Level_Loading.h"
#include "Dive.h"

CPlanet_Exo::CPlanet_Exo()
{
}

CPlanet_Exo::CPlanet_Exo(const CPlanet_Exo& Prototype)
{
	*this = Prototype;
}

HRESULT CPlanet_Exo::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CPlanet_Exo::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(-250.f, 200.f, 250.f));

	m_pDiveUi = GAMEINSTANCE->Add_GameObject<CDive>(LEVEL_SELECTPLANET, TEXT("Dive"));
	m_pDiveUi->Set_Enable(false);


	return S_OK;
}

void CPlanet_Exo::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	Enter_Planet();

}

void CPlanet_Exo::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);


	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);


}

HRESULT CPlanet_Exo::Render()
{

	m_pTransformCom->Bind_WorldMatrix();


	m_pRendererCom->Bind_Texture(1);

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 253);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pVIBufferCom->Render();

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pRendererCom->UnBind_Texture();



	return S_OK;
}


HRESULT CPlanet_Exo::SetUp_Components()
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

void CPlanet_Exo::LookAtCamera()
{
	_float4x4		ViewMatrix;

	DEVICE->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, *(_float3*)&ViewMatrix.m[0][0], true);
	m_pTransformCom->Set_State(CTransform::STATE_UP, *(_float3*)&ViewMatrix.m[1][0], true);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, *(_float3*)&ViewMatrix.m[2][0], true);

}

void CPlanet_Exo::Enter_Planet()
{

	CCamera* pCurrentCam = GAMEINSTANCE->Get_Camera();

	ISVALID(pCurrentCam, );

	_float3 CamWorldPos = pCurrentCam->Get_Transform()->Get_World_State(CTransform::STATE_POSITION);
	_float3 MyWorldPos;
	MyWorldPos.x = -250.f + CamWorldPos.x;
	MyWorldPos.y = 200.f + CamWorldPos.y;
	MyWorldPos.z = 250.f + CamWorldPos.z;


	m_pTransformCom->Set_State(CTransform::STATE_POSITION, MyWorldPos, true);

	LookAtCamera();

	m_pTransformCom->Scaling(_float3(100.f, 100.f, 50.f), true);

	_float3 MouseEndPos;
	RAY	MouseWorldRay;
	MouseWorldRay = CMath_Utillity::Get_MouseRayInWorldSpace();
	MouseEndPos = MouseWorldRay.Pos + (MouseWorldRay.Dir * 10000.f);

	_float3 ScreenPos = _float3(0.f, 0.f, 0.f);

	CMath_Utillity::WorldToScreen(&m_pTransformCom->Get_State(CTransform::STATE_POSITION, true), &ScreenPos);

	if (true == CMath_Utillity::Picking_VIBuffer(m_pVIBufferCom, m_pTransformCom, MouseWorldRay, &MouseEndPos))
	{
		m_pDiveUi->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)ScreenPos.x + 40, (LONG)ScreenPos.y - 10 }, TEXT("Exo Planet \n �� ���� ���� \n �ӹ� : ��� ��ü �ı� \n ���̵� :���ڡڡڡڡ�\n ���� : XXX"), 0);

		if (KEY_INPUT(KEY::F, KEY_STATE::HOLD) && !m_bLevelChange)
		{
			GAMEINSTANCE->Get_CurrentLevel()->Change_Level(this, LEVEL::LEVLE_EXOPLANET);
			m_bLevelChange = true;
			return;
		}
	}

	else
	{
		m_pDiveUi->Set_Enable(false);
	}
}

CPlanet_Exo* CPlanet_Exo::Create()
{
	CREATE_PIPELINE(CPlanet_Exo);
}

CGameObject* CPlanet_Exo::Clone(void* pArg)
{
	CLONE_PIPELINE(CPlanet_Exo);
}

void CPlanet_Exo::Free()
{
	__super::Free();

	RETURN_WEAKPTR(m_pTransformCom);
	RETURN_WEAKPTR(m_pRendererCom);
	RETURN_WEAKPTR(m_pVIBufferCom);

	delete this;
}

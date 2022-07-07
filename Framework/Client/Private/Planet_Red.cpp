#include "stdafx.h"
#include "Planet_Red.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "Level_Loading.h"


CPlanet_Red::CPlanet_Red()
{
}

CPlanet_Red::CPlanet_Red(const CPlanet_Red& Prototype)
{
	*this = Prototype;
}

HRESULT CPlanet_Red::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CPlanet_Red::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(0.f, 20.f, 30.f));


	return S_OK;
}

void CPlanet_Red::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


	//CCamera* pCurrentCam = GAMEINSTANCE->Get_Camera();

	//ISVALID(pCurrentCam, );

	//_float3 CamWorldPos = pCurrentCam->Get_Transform()->Get_World_State(CTransform::STATE_POSITION);
	//_float3 MyWorldPos;
	//MyWorldPos.x = 0.f + CamWorldPos.x;
	//MyWorldPos.y = 200.f + CamWorldPos.y;
	//MyWorldPos.z = 300.f + CamWorldPos.z;


	//m_pTransformCom->Set_State(CTransform::STATE_POSITION, MyWorldPos, true);


	LookAtCamera();

	//m_pTransformCom->Scaling(_float3(100.f, 100.f, 50.f), true);

	_float3 PickedPos = _float3(0.f, 0.f, 0.f);
	RAY	MouseWorldRay;
	MouseWorldRay = CMath_Utillity::Get_MouseRayInWorldSpace();
	_float3 ScreenPos = _float3(0.f, 0.f, 0.f);

	CMath_Utillity::WorldToScreen(&m_pTransformCom->Get_State(CTransform::STATE_POSITION, true), &ScreenPos);

	if (true == CMath_Utillity::Picking_VIBuffer(m_pVIBufferCom, m_pTransformCom, MouseWorldRay, &PickedPos))
	{
		m_pDiveUi->Set_Enable(true);
		GAMEINSTANCE->Add_Text(_point{ (LONG)ScreenPos.x + 40, (LONG)ScreenPos.y - 10 }, TEXT("Red Planet \n 고 위험 구역 \n 임무 : 모든 기체 파괴 \n 난이도 :『★★★★』  \n 보상 : XXX"), 0);
	}

	else
	{


	if (KEY_INPUT(KEY::RBUTTON, KEY_STATE::TAP))
	{
		system("cls");

		printf("마우스 레이 좌표: %f, %f, %f /  Dir: %f, %f, %f\n", MouseWorldRay.Pos.x, MouseWorldRay.Pos.y, MouseWorldRay.Pos.z, MouseWorldRay.Dir.x, MouseWorldRay.Dir.y, MouseWorldRay.Dir.z);

		_float4x4 CamWorld = GAMEINSTANCE->Get_Camera()->Get_CameraWorldMat();

		printf("카메라 월드 좌표: %f, %f, %f /  Dir: %f, %f, %f\n", CamWorld._41, CamWorld._42, CamWorld._43, CamWorld._31, CamWorld._32, CamWorld._33);
		printf("Picked Position: %f, %f, %f\n", PickedPos.x, PickedPos.y, PickedPos.z);

		PickedPos.x -= CamWorld._41;
		PickedPos.y -= CamWorld._42;
		PickedPos.z -= CamWorld._43;
		printf("Picked Position - CamPos : %f, %f, %f\n", PickedPos.x, PickedPos.y, PickedPos.z);
	}


	//MouseEndPos = MouseWorldRay.Pos + (MouseWorldRay.Dir * 10000.f);


	
	
	

	if (KEY_INPUT(KEY::F, KEY_STATE::HOLD) && !m_bLevelChange)
	{

		if (true == CMath_Utillity::Picking_VIBuffer(m_pVIBufferCom, m_pTransformCom, MouseWorldRay, &PickedPos))
		{
			GAMEINSTANCE->Get_CurrentLevel()->Change_Level(this,LEVEL::LEVEL_REDPLANET);
			m_bLevelChange = true;
			return;
		}


	}

	CCamera* pCurrentCam = GAMEINSTANCE->Get_Camera();

	ISVALID(pCurrentCam, );

	_float3 CamWorldPos = pCurrentCam->Get_Transform()->Get_World_State(CTransform::STATE_POSITION);
	_float3 MyWorldPos;
	MyWorldPos.x = 0.f + CamWorldPos.x;
	MyWorldPos.y = 200.f + CamWorldPos.y;
	MyWorldPos.z = 300.f + CamWorldPos.z;


	m_pTransformCom->Set_State(CTransform::STATE_POSITION, MyWorldPos, true);


}

void CPlanet_Red::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);


	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);

	LookAtCamera();

}

HRESULT CPlanet_Red::Render()
{
	m_pTransformCom->Scaling(_float3(100.f, 100.f, 50.f), true);

	m_pTransformCom->Bind_WorldMatrix();

	_float3 ScreenPos = _float3(0.f, 0.f, 0.f);

	CMath_Utillity::WorldToScreen(&m_pTransformCom->Get_State(CTransform::STATE_POSITION, true), &ScreenPos);

	

	GAMEINSTANCE->Add_Text(_point{ (LONG)ScreenPos.x + 40, (LONG)ScreenPos.y - 10 }, TEXT("Red Planet \n 고 위험 구역 \n 임무 : 모든 기체 파괴 \n 난이도 :『★★★★』  \n 보상 : XXX"), 0);

	//m_pRendererCom->Bind_Texture(3);

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 253);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);*/
	

	m_pVIBufferCom->Render();

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//m_pRendererCom->UnBind_Texture();



	return S_OK;
}


HRESULT CPlanet_Red::SetUp_Components()
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

void CPlanet_Red::LookAtCamera()
{
	_float4x4		ViewMatrix;

	DEVICE->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, *(_float3*)&ViewMatrix.m[0][0], true);
	m_pTransformCom->Set_State(CTransform::STATE_UP, *(_float3*)&ViewMatrix.m[1][0], true);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, *(_float3*)&ViewMatrix.m[2][0], true);

}

CPlanet_Red* CPlanet_Red::Create()
{
	CREATE_PIPELINE(CPlanet_Red);
}

CGameObject* CPlanet_Red::Clone(void* pArg)
{
	CLONE_PIPELINE(CPlanet_Red);
}

void CPlanet_Red::Free()
{
	__super::Free();

	RETURN_WEAKPTR(m_pTransformCom);
	RETURN_WEAKPTR(m_pRendererCom);
	RETURN_WEAKPTR(m_pVIBufferCom);

	delete this;
}


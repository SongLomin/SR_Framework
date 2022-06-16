#include "stdafx.h"
#include "..\Public\BackGround.h"
#include "GameInstance.h"
#include "Dummy.h"
#include <tchar.h>
#include "Posin.h"
#include "CameraPosin.h"
#include "Cam_Free.h"
#include "Cam_TPS.h"
#include "Ring.h"

CBackGround::CBackGround()
{

}

CBackGround::CBackGround(const CBackGround & Prototype)
{
}

HRESULT CBackGround::Initialize_Prototype()
{
	/* 백엔드로부터 값ㅇ를 어덩오낟. */

	return S_OK;
}

HRESULT CBackGround::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	
	return S_OK;
}

void CBackGround::Tick(_float fTimeDelta)
{
	ISVALID(m_pTransformCom);

	if (KEY_INPUT(KEY::W, KEY_STATE::HOLD))
		m_pTransformCom->Go_Straight(fTimeDelta);

	if (KEY_INPUT(KEY::S, KEY_STATE::HOLD))
		m_pTransformCom->Go_Backward(fTimeDelta);

	if (KEY_INPUT(KEY::D, KEY_STATE::HOLD))
		m_pTransformCom->Turn(_float3(0.f, 1.f, 0.f), fTimeDelta);

	if (KEY_INPUT(KEY::A, KEY_STATE::HOLD))
		m_pTransformCom->Turn(_float3(0.f, 1.f, 0.f), fTimeDelta * -1.f);

	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		m_pTransformCom->Go_Straight(fTimeDelta);
		m_pTransformCom->Go_Up(fTimeDelta * 0.3f);
	}

	if (GetKeyState(VK_CONTROL) & 0x8000)
	{
		m_pTransformCom->Go_Up(-(fTimeDelta * 0.3f));
	}

	if (GetKeyState(VK_TAB) & 0x8000)
		m_pTransformCom->Rotation(_float3(0.f, 1.f, 0.f), D3DXToRadian(120.0f));

	if (GetKeyState('Z') & 0x8000)
	{
		m_pStatusCom->Add_Status(CStatus::STATUSID::STATUS_HP, -1.f);
	}

}

void CBackGround::LateTick(_float fTimeDelta)
{
	if (nullptr == m_pRendererCom)
		return;

	
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_PRIORITY, this);
}

HRESULT CBackGround::Render()
{
	//_float4x4		ViewMatrix, ProjMatrix;

	//D3DXMatrixLookAtLH(&ViewMatrix, &_float3(0.f, 35.f, -10.f), &_float3(0.f, 0.f, 0.f), &_float3(0.f, 1.f, 0.f));
	//D3DXMatrixPerspectiveFovLH(&ProjMatrix, D3DXToRadian(60.0f), (_float)g_iWinCX / g_iWinCY, 02.f, 300.f);

	m_pTransformCom->Bind_WorldMatrix();
	//DEVICE->SetTransform(D3DTS_VIEW, &ViewMatrix);
	//DEVICE->SetTransform(D3DTS_PROJECTION, &ProjMatrix);


	/*GAMEINSTANCE->Add_Text("HP: %d", 내  HP, 위치, 컬러);*/
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pRendererCom->Bind_Texture(0);
	m_pMeshCubeCom->Render();
	m_pRendererCom->UnBind_Texture();

	
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}

HRESULT CBackGround::SetUp_Components()
{

	//약포인터: 원본 객체가 삭제되면 약포인터로 등록된 포인터들도 nullptr로 바뀐다.
	//댕글링 포인터를 방지하기 위해 사용한다.
	
	CStatus::STATUS		Status;
	Status.fHp = 10.f;
	Status.fAttack = 7.f;
	Status.fArmor = 5.f;

	m_pStatusCom = Add_Component<CStatus>(&Status);
	m_pStatusCom->Set_WeakPtr(&m_pStatusCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);
	m_pRendererCom->Set_Textures_From_Key(TEXT("Test"), MEMORY_TYPE::MEMORY_DYNAMIC);

	/*m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);*/

	m_pMeshCubeCom = Add_Component<CMesh_Cube>();
	m_pMeshCubeCom->Set_WeakPtr(&m_pMeshCubeCom);
	
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.fSpeedPerSec = 5.0f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);

	m_pTransformCom = Add_Component<CTransform>(&TransformDesc);
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);
	m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(0.f, 1.f, 0.f));

	CGameObject* MyChild = GAMEINSTANCE->Add_GameObject<CDummy>(CURRENT_LEVEL, TEXT("Dummy"));
	MyChild->Get_Component<CTransform>()->Set_Parent(m_pTransformCom);

	MyChild = GAMEINSTANCE->Add_GameObject<CPosin>(CURRENT_LEVEL, TEXT("Posin"));
	MyChild->Get_Component<CTransform>()->Set_Parent(m_pTransformCom);
	m_pTransformCom->Add_Child(MyChild->Get_Component<CTransform>());

	MyChild = GAMEINSTANCE->Add_GameObject<CRing>(CURRENT_LEVEL, TEXT("Ring"));
	MyChild->Get_Component<CTransform>()->Set_Parent(m_pTransformCom);
	m_pTransformCom->Add_Child(MyChild->Get_Component<CTransform>());

	MyChild = GAMEINSTANCE->Add_GameObject<CCameraPosin>(CURRENT_LEVEL, TEXT("CameraPosin"));
	MyChild->Get_Component<CTransform>()->Set_Parent(m_pTransformCom);

	

	CGameObject* Free_Cam = GAMEINSTANCE->Add_GameObject<CCam_TPS>(CURRENT_LEVEL, TEXT("Camera"));
	Free_Cam->Get_Component<CCamera>()->Set_Param(D3DXToRadian(65.0f), (_float)g_iWinCX / g_iWinCY, 0.2f, 300.f);
	Free_Cam->Get_Component<CTransform>()->Set_Parent(m_pTransformCom);
	m_pTransformCom->Add_Child(Free_Cam->Get_Component<CTransform>());

	((CCameraPosin*)MyChild)->Link_CameraTransfrom(Free_Cam->Get_Component<CTransform>());


	return S_OK;
}

CBackGround * CBackGround::Create()
{
	CREATE_PIPELINE(CBackGround);
}

CGameObject * CBackGround::Clone(void* pArg)
{
	CLONE_PIPELINE(CBackGround);
}

void CBackGround::Free()
{
	__super::Free();
	
	delete this;
}

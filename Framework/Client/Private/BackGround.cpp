#include "stdafx.h"
#include "..\Public\BackGround.h"
#include "GameInstance.h"
#include "Dummy.h"
#include <tchar.h>
#include "Posin.h"
#include "Cam_Free.h"
#include "Cam_TPS.h"

CBackGround::CBackGround()
{

}

CBackGround::CBackGround(const CBackGround & Prototype)
{
}

HRESULT CBackGround::Initialize_Prototype()
{
	/* �鿣��κ��� ������ �����. */

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

	m_pRigidBodyCom->Add_DirZ(0.f);
	//m_pRigidBodyCom->Add_DirY(0.f);
	m_pRigidBodyCom->Add_RotationY(0.f);

	if (GetKeyState('W') & 0x8000)
		m_pRigidBodyCom->Add_DirZ(0.1f);

	if (GetKeyState('S') & 0x8000)
		m_pRigidBodyCom->Add_DirZ(-0.1f);

	if (GetKeyState('D') & 0x8000)
		m_pRigidBodyCom->Add_RotationY( 0.3f);

	if (GetKeyState('A') & 0x8000)
		m_pRigidBodyCom->Add_RotationY(-0.3f);

	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		m_pRigidBodyCom->Add_Jump();
	}

	if (GetKeyState('Z') & 0x8000)
	{
		m_pStatusCom->Add_Status(CStatus::STATUSID::STATUS_HP, -1.f);
	}

	m_pRigidBodyCom->Update_Transform(fTimeDelta);

	

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


	/*GAMEINSTANCE->Add_Text("HP: %d", ��  HP, ��ġ, �÷�);*/
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pRendererCom->Bind_Texture(0);
	m_pMeshCubeCom->Render();
	m_pRendererCom->UnBind_Texture();

	
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}

HRESULT CBackGround::SetUp_Components()
{

	//��������: ���� ��ü�� �����Ǹ� �������ͷ� ��ϵ� �����͵鵵 nullptr�� �ٲ��.
	//��۸� �����͸� �����ϱ� ���� ����Ѵ�.
	
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

	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.m_fOwnerSpeed = 5.f;
	RigidBodyDesc.m_fOwnerRadSpeed= D3DXToRadian(90.0f);

	RigidBodyDesc.m_fFrictional = 0.05f;
	RigidBodyDesc.m_fRadFrictional =0.05f;

	m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);

	CGameObject* MyChild = GAMEINSTANCE->Add_GameObject<CDummy>(CURRENT_LEVEL, TEXT("Dummy"));
	MyChild->Get_Component<CTransform>()->Set_Parent(m_pTransformCom);

	MyChild = GAMEINSTANCE->Add_GameObject<CPosin>(CURRENT_LEVEL, TEXT("Posin"));
	MyChild->Get_Component<CTransform>()->Set_Parent(m_pTransformCom);
	
	m_pTransformCom->Add_Child(MyChild->Get_Component<CTransform>());

	CGameObject* Free_Cam = GAMEINSTANCE->Add_GameObject<CCam_TPS>(CURRENT_LEVEL, TEXT("Camera"));
	Free_Cam->Get_Component<CCamera>()->Set_Param(D3DXToRadian(65.0f), (_float)g_iWinCX / g_iWinCY, 0.2f, 300.f);
	Free_Cam->Get_Component<CTransform>()->Set_Parent(m_pTransformCom);
	m_pTransformCom->Add_Child(Free_Cam->Get_Component<CTransform>());


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

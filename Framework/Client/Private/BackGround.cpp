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
#include "Bullet.h"

CBackGround::CBackGround()
{

}

CBackGround::CBackGround(const CBackGround & Prototype)
{
	*this = Prototype;
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

	m_pRigidBodyCom->Add_DirZ(0.f);
	//m_pRigidBodyCom->Add_DirY(0.f);
	m_pRigidBodyCom->Add_RotationY(0.f);

	if (KEY_INPUT(KEY::W, KEY_STATE::HOLD))
		m_pRigidBodyCom->Add_DirZ(0.1f);

	if (KEY_INPUT(KEY::S, KEY_STATE::HOLD))
		m_pRigidBodyCom->Add_DirZ(-0.1f);

	if (KEY_INPUT(KEY::D, KEY_STATE::HOLD))
		m_pRigidBodyCom->Add_RotationY( 0.3f);

	if (KEY_INPUT(KEY::A, KEY_STATE::HOLD))
		m_pRigidBodyCom->Add_RotationY(-0.3f);

	if (KEY_INPUT(KEY::SPACE, KEY_STATE::HOLD))
	{
		m_pRigidBodyCom->Add_Jump();
	}

	if (KEY_INPUT(KEY::Z, KEY_STATE::TAP))
	{
		m_pStatusCom->Add_Status(CStatus::STATUSID::STATUS_HP, -1.f);
	}

	if (KEY_INPUT(KEY::CTRL, KEY_STATE::TAP))
	{
		CGameObject* Bullet = GAMEINSTANCE->Add_GameObject<CBullet>(CURRENT_LEVEL, TEXT("Bullet"));
		
		((CBullet*)Bullet)->Link_CameraPosinTransform(m_pCameraPosin->Get_Component<CTransform>());
	}


	if (KEY_INPUT(KEY::Q, KEY_STATE::TAP))
	{
		GAMEINSTANCE->Add_GameObject<CRing>(CURRENT_LEVEL, TEXT("Ring"), m_pTransformCom);
	}

	

	m_pRigidBodyCom->Update_Transform(fTimeDelta);

	


	TEXTINFO Info;
	Info.color = D3DCOLOR_ARGB(255, 0, 255, 0);
	Info.rcTemp = { 100, g_iWinCY - 100, 10000, 10000 };
	
	_uint hp = (_uint)m_pStatusCom->Get_Status().fHp;
	_tchar szText[MAX_PATH] = L"HP : %d";
 
	wsprintf(Info.szBuff, szText, hp);

	GAMEINSTANCE->Add_Text(&Info);

}

void CBackGround::LateTick(_float fTimeDelta)
{
	if (nullptr == m_pRendererCom)
		return;

	
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_PRIORITY, this);
}

HRESULT CBackGround::Render()
{
	m_pTransformCom->Bind_WorldMatrix();
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

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);
	m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(0.f, 1.f, 0.f));

	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.m_fOwnerSpeed = 5.f;
	RigidBodyDesc.m_fOwnerRadSpeed= D3DXToRadian(90.0f);

	RigidBodyDesc.m_fFrictional = 0.05f;      // 마찰력
	RigidBodyDesc.m_fRadFrictional = 0.03f;    // Rad마찰력

	m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);

	CGameObject* MyChild = GAMEINSTANCE->Add_GameObject<CDummy>(CURRENT_LEVEL, TEXT("Dummy"), m_pTransformCom);

	GAMEINSTANCE->Add_GameObject<CPosin>(CURRENT_LEVEL, TEXT("Posin"), m_pTransformCom);
	

	m_pCameraPosin = (CCameraPosin*)GAMEINSTANCE->Add_GameObject<CCameraPosin>(CURRENT_LEVEL, TEXT("CameraPosin"), m_pTransformCom);
	
	

	CGameObject* Free_Cam = GAMEINSTANCE->Add_GameObject<CCam_TPS>(CURRENT_LEVEL, TEXT("Camera"), m_pTransformCom);
	Free_Cam->Get_Component<CCamera>()->Set_Param(D3DXToRadian(65.0f), (_float)g_iWinCX / g_iWinCY, 0.2f, 300.f);

	m_pCameraPosin->Link_CameraTransfrom(Free_Cam->Get_Component<CTransform>());



	

       

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

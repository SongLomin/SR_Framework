#include "stdafx.h"
#include "CameraPosin.h"
#include "GameInstance.h"
#include "Bullet.h"
#include <Math_Utillity.h>

CCameraPosin::CCameraPosin()
{
}

CCameraPosin::CCameraPosin(const CCameraPosin& Prototype)
{
	*this = Prototype;
	//m_szName = L"Posin_Dir";
	Add_Component<CTransform>();
}

HRESULT CCameraPosin::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCameraPosin::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);


	m_pMeshCom = Add_Component<CMesh_Cube>();
	m_pMeshCom->Set_WeakPtr(&m_pMeshCom);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(0.0f, 1.5f, 0.f));
	m_pTransformCom->Scaling(_float3(0.5f, 0.5f, 0.5f));
	return S_OK;

}

void CCameraPosin::Tick(_float fTimeDelta)
{
	//if (KEY_INPUT(KEY::R, KEY_STATE::HOLD))
	//{
	//	_float4x4 MyWorldMat = m_pTransformCom->Get_WorldMatrix();
	//	_float3 MyPos{ MyWorldMat._41, MyWorldMat._42, MyWorldMat._43};

	//	/*_float4x4 CamWorldMat = GAMEINSTANCE->Get_Camera()->Get_CameraWorldMat();

	//	_float3 CamPos{ CamWorldMat._41, CamWorldMat._42, CamWorldMat._43 };*/
	//	_float3 MyScreenPos;

	//	CMath_Utillity::WorldToScreen(&MyPos, &MyScreenPos);

	//	GAMEINSTANCE->Add_Text(
	//		_point{ (long)MyScreenPos.x, (long)MyScreenPos.y },
	//		L"º´¼öÇü",
	//		0);
	//}

	LookAt_CamTPS();
}

void CCameraPosin::LateTick(_float fTimeDelta)
{
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);

}

HRESULT CCameraPosin::Render()
{
	m_pTransformCom->Bind_WorldMatrix();

	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pRendererCom->Bind_Texture(1);
	m_pMeshCom->Render();
	m_pRendererCom->UnBind_Texture();

	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}

void CCameraPosin::Link_CameraTransfrom(CTransform* pTransform)
{
	m_pCameraTransformCom = pTransform;

	m_pCameraTransformCom->Set_WeakPtr(&m_pTransformCom);
}


HRESULT CCameraPosin::SetUp_Components()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();


	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr((void**)&m_pTransformCom);

	
	

	return S_OK;
}

void CCameraPosin::LookAt_CamTPS()
{
	if(m_pCameraTransformCom)
		m_pTransformCom->LookAt(m_pCameraTransformCom);
}

CCameraPosin* CCameraPosin::Create()
{
	CREATE_PIPELINE(CCameraPosin);
}

CGameObject* CCameraPosin::Clone(void* pArg)
{
	CLONE_PIPELINE(CCameraPosin);
}

void CCameraPosin::Free()
{
	__super::Free();

	delete this;
}

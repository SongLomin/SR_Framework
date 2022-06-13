#include "stdafx.h"
#include "..\Public\BackGround.h"
#include "GameInstance.h"
#include "Dummy.h"

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
	ISVALID(m_pTransformCom, );
	

	if (GetKeyState(VK_UP) & 0x8000)
		m_pTransformCom->Go_Straight(fTimeDelta);

	if (GetKeyState(VK_DOWN) & 0x8000)
		m_pTransformCom->Go_Backward(fTimeDelta);

	if (GetKeyState(VK_RIGHT) & 0x8000)
		m_pTransformCom->Turn(_float3(0.f, 1.f, 0.f), fTimeDelta);

	if (GetKeyState(VK_LEFT) & 0x8000)
		m_pTransformCom->Turn(_float3(0.f, 1.f, 0.f), fTimeDelta * -1.f);

	if (GetKeyState(VK_TAB) & 0x8000)
		m_pTransformCom->Rotation(_float3(0.f, 1.f, 0.f), D3DXToRadian(120.0f));

}

void CBackGround::LateTick(_float fTimeDelta)
{
	if (nullptr == m_pRendererCom)
		return;

	
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_PRIORITY, this);
}

HRESULT CBackGround::Render()
{
	_float4x4		ViewMatrix, ProjMatrix;

	D3DXMatrixLookAtLH(&ViewMatrix, &_float3(0.f, 35.f, -10.f), &_float3(0.f, 0.f, 0.f), &_float3(0.f, 1.f, 0.f));
	D3DXMatrixPerspectiveFovLH(&ProjMatrix, D3DXToRadian(60.0f), (_float)g_iWinCX / g_iWinCY, 02.f, 300.f);

	m_pTransformCom->Bind_WorldMatrix();
	DEVICE->SetTransform(D3DTS_VIEW, &ViewMatrix);
	DEVICE->SetTransform(D3DTS_PROJECTION, &ProjMatrix);

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pRendererCom->Update_Textures(0);
	m_pVIBufferCom->Render();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}

HRESULT CBackGround::SetUp_Components()
{

	//약포인터: 원본 객체가 삭제되면 약포인터로 등록된 포인터들도 nullptr로 바뀐다.
	//댕글링 포인터를 방지하기 위해 사용한다.

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);
	m_pRendererCom->Set_Textures_From_Key(TEXT("Test"), MEMORY_TYPE::MEMORY_DYNAMIC);

	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);
	
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.fSpeedPerSec = 5.0f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);

	m_pTransformCom = Add_Component<CTransform>(&TransformDesc);
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	CGameObject* MyChild = GAMEINSTANCE->Add_GameObject<CDummy>(2, TEXT("Dummy"));
	MyChild->Get_Component<CTransform>()->Set_Parent(m_pTransformCom);
	

	return S_OK;
}

CBackGround * CBackGround::Create()
{
	CBackGround*		pInstance = new CBackGround();

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CBackGround");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CBackGround::Clone(void* pArg)
{
	CBackGround*		pInstance = new CBackGround(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Created : CBackGround");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBackGround::Free()
{
	__super::Free();

	delete this;
}

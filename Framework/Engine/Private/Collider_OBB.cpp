#include "Collider_OBB.h"
#include "GameInstance.h"

CCollider_OBB::CCollider_OBB(const CCollider_OBB& Prototype)
{
    *this = Prototype;

}

HRESULT CCollider_OBB::Initialize_Prototype()
{
    m_eShape = COLLIDER_SHAPE::OBB;
    return S_OK;
}

HRESULT CCollider_OBB::Initialize(void* pArg)
{
    m_eCollision_Type = *(COLLISION_TYPE*)pArg;
    m_iID = g_iNextID++;

    GAMEINSTANCE->Add_Collider(this);

	//디버깅용 메쉬 생성
	//m_iNumVertices = 24;
	//m_iNumPrimitive = 12;
	//m_dwFVF = VTXTEX::FVF;

	//if (nullptr == LPDEVICE)
	//	return E_FAIL;

	//if (FAILED(D3DXCreateMeshFVF(
	//	m_iNumPrimitive,
	//	m_iNumVertices,
	//	D3DXMESH_MANAGED,
	//	m_dwFVF,
	//	DEVICE,
	//	&m_pMesh)))
	//	return E_FAIL;

	//VTXTEX* vertices = nullptr;
	//m_pMesh->LockVertexBuffer(0, (void**)&vertices);
	////front
	//vertices[0] = VTXTEX(D3DXVECTOR3(-1.f, -1.f, -1.f), D3DXVECTOR2(0.f, 0.f));
	//vertices[1] = VTXTEX(D3DXVECTOR3(-1.f, 1.f, -1.f), D3DXVECTOR2(0.f, 1.f));
	//vertices[2] = VTXTEX(D3DXVECTOR3(1.f, 1.f, -1.f), D3DXVECTOR2(1.f, 1.f));
	//vertices[3] = VTXTEX(D3DXVECTOR3(1.f, -1.f, -1.f), D3DXVECTOR2(1.f, 0.f));

	////back
	//vertices[4] = VTXTEX(D3DXVECTOR3(-1.f, -1.f, 1.f), D3DXVECTOR2(0.f, 0.f));
	//vertices[5] = VTXTEX(D3DXVECTOR3(1.f, -1.f, 1.f), D3DXVECTOR2(0.f, 1.f));
	//vertices[6] = VTXTEX(D3DXVECTOR3(1.f, 1.f, 1.f), D3DXVECTOR2(1.f, 1.f));
	//vertices[7] = VTXTEX(D3DXVECTOR3(-1.f, 1.f, 1.f), D3DXVECTOR2(1.f, 0.f));

	////top
	//vertices[8] = VTXTEX(D3DXVECTOR3(-1.f, 1.f, -1.f), D3DXVECTOR2(0.f, 0.f));
	//vertices[9] = VTXTEX(D3DXVECTOR3(-1.f, 1.f, 1.f), D3DXVECTOR2(0.f, 1.f));
	//vertices[10] = VTXTEX(D3DXVECTOR3(1.f, 1.f, 1.f), D3DXVECTOR2(1.f, 1.f));
	//vertices[11] = VTXTEX(D3DXVECTOR3(1.f, 1.f, -1.f), D3DXVECTOR2(1.f, 0.f));

	////bottom
	//vertices[12] = VTXTEX(D3DXVECTOR3(-1.f, -1.f, -1.f), D3DXVECTOR2(0.f, 0.f));
	//vertices[13] = VTXTEX(D3DXVECTOR3(1.f, -1.f, -1.f), D3DXVECTOR2(0.f, 1.f));
	//vertices[14] = VTXTEX(D3DXVECTOR3(1.f, -1.f, 1.f), D3DXVECTOR2(1.f, 1.f));
	//vertices[15] = VTXTEX(D3DXVECTOR3(-1.f, -1.f, 1.f), D3DXVECTOR2(1.f, 0.f));

	////left
	//vertices[16] = VTXTEX(D3DXVECTOR3(-1.f, -1.f, 1.f), D3DXVECTOR2(0.f, 0.f));
	//vertices[17] = VTXTEX(D3DXVECTOR3(-1.f, 1.f, 1.f), D3DXVECTOR2(0.f, 1.f));
	//vertices[18] = VTXTEX(D3DXVECTOR3(-1.f, 1.f, -1.f), D3DXVECTOR2(1.f, 1.f));
	//vertices[19] = VTXTEX(D3DXVECTOR3(-1.f, -1.f, -1.f), D3DXVECTOR2(1.f, 0.f));

	////right
	//vertices[20] = VTXTEX(D3DXVECTOR3(1.f, -1.f, -1.f), D3DXVECTOR2(0.f, 0.f));
	//vertices[21] = VTXTEX(D3DXVECTOR3(1.f, 1.f, -1.f), D3DXVECTOR2(0.f, 1.f));
	//vertices[22] = VTXTEX(D3DXVECTOR3(1.f, 1.f, 1.f), D3DXVECTOR2(1.f, 1.f));
	//vertices[23] = VTXTEX(D3DXVECTOR3(1.f, -1.f, 1.f), D3DXVECTOR2(1.f, 0.f));

	//m_pMesh->UnlockVertexBuffer();

	//WORD* indices = 0;
	//m_pMesh->LockIndexBuffer(0, (void**)&indices);

	////front
	//indices[0] = 0; indices[1] = 1; indices[2] = 2;
	//indices[3] = 0; indices[4] = 2; indices[5] = 3;

	////back
	//indices[6] = 4; indices[7] = 5; indices[8] = 6;
	//indices[9] = 4; indices[10] = 6; indices[11] = 7;

	////top
	//indices[12] = 8; indices[13] = 9; indices[14] = 10;
	//indices[15] = 8; indices[16] = 10; indices[17] = 11;

	////bottom
	//indices[18] = 12; indices[19] = 13; indices[20] = 14;
	//indices[21] = 12; indices[22] = 14; indices[23] = 15;

	////left
	//indices[24] = 16; indices[25] = 17; indices[26] = 18;
	//indices[27] = 16; indices[28] = 18; indices[29] = 19;

	////right
	//indices[30] = 20; indices[31] = 21; indices[32] = 22;
	//indices[33] = 20; indices[34] = 22; indices[35] = 23;

	//m_pMesh->UnlockIndexBuffer();

	//DWORD* attributeBuffer = 0;
	//m_pMesh->LockAttributeBuffer(0, &attributeBuffer);

	//for (int i = 0; i < m_iNumPrimitive; ++i)
	//{
	//	attributeBuffer[i] = 0;
	//}

	//m_pMesh->UnlockAttributeBuffer();


	//vector<DWORD> adjacencyBuffer(m_iNumPrimitive * 3);
	//m_pMesh->GenerateAdjacency(0.f, &adjacencyBuffer[0]);

	//m_pMesh->OptimizeInplace(
	//	D3DXMESHOPT_ATTRSORT |
	//	D3DXMESHOPT_COMPACT |
	//	D3DXMESHOPT_VERTEXCACHE,
	//	&adjacencyBuffer[0],
	//	0, 0, 0
	//);


    return S_OK;
}



void CCollider_OBB::Set_Collider_Size(const _float3& _Size)
{
    m_OBBInfo.SetSize(_Size);
}

void CCollider_OBB::Tick(_float _TimeDelta)
{
    if (m_pMyTransformCom)
    {
        m_OBBInfo.SetMatrix(&m_pMyTransformCom->Get_WorldMatrix());
    }
}

void CCollider_OBB::LateTick(_float fTimeDelta)
{
}

HRESULT CCollider_OBB::Render()
{
	/*DEVICE->SetRenderState(D3DRS_FILLMODE, _D3DFILLMODE::D3DFILL_WIREFRAME);

	m_pMesh->DrawSubset(0);

	DEVICE->SetRenderState(D3DRS_FILLMODE, _D3DFILLMODE::D3DFILL_SOLID);*/

    return S_OK;
}

_float3 CCollider_OBB::Get_Collider_Size()
{
    return m_OBBInfo.ObbSize;
}

_float3 CCollider_OBB::Get_Collider_Position()
{
    return m_OBBInfo.ObbCenterPos;
}


CCollider_OBB* CCollider_OBB::Create()
{
    CREATE_PIPELINE(CCollider_OBB);
}

CComponent* CCollider_OBB::Clone(void* pArg)
{
    CLONE_PIPELINE(CCollider_OBB);
}

void CCollider_OBB::Free()
{
    __super::Free();

    delete this;

}
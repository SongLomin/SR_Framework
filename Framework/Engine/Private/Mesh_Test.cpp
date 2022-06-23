#include "Mesh_Test.h"
#include"GameInstance.h"

CMesh_Test::CMesh_Test()
{
}

CMesh_Test::CMesh_Test(const CMesh_Test& Prototype)
{
    *this = Prototype;
}

HRESULT CMesh_Test::Initialize_Prototype()
{
	

	D3DXLoadMeshFromX(TEXT("../Bin/Resources/Textures/Terrain/ship6.x"), D3DXMESH_MANAGED,
		DEVICE, &m_pAdj, &m_pMtrl, &m_pEffectInstances,	
		&m_iNumMtrl, &m_pMesh);

	m_dwNumSubsets = 1;

	ofstream fout("output.txt");



	VTXCOLOR* vertices = nullptr;
	DWORD vtxSize = 0;
	vtxSize = m_pMesh->GetNumVertices();
	vector<VTXCOLOR> Vtx_Vector;

	WORD* indices = 0;
	DWORD indexSize = 0;
	indexSize = m_pMesh->GetNumFaces() * 3;
	vector<WORD> Index_Vector;

	//����
	int Diffuse[4]{ 255, 160, 160, 160 };


	m_pMesh->LockVertexBuffer(0, (void**)&vertices);
	Vtx_Vector.reserve(vtxSize);

	fout << "////////////////////////	����	////////////////////////\n";
	fout << "// 1. �޽� ��ӹ޴� �ڽ� �޽� �����\n";
	fout << "// 2. �ڽ� �޽��� Initialize_Prototype�� ���� ���� �ٿ��ֱ�\n";
	fout << "///////////////////////////////////////////////////////////\n\n";

	fout << "m_iNumVertices = " << vtxSize << ";\n";
	fout << "m_iNumPrimitive = " << indexSize/3 << ";\n";
	fout << "m_dwFVF = VTXCOLOR::FVF;\n\n";
	fout << "m_dwNumSubsets = 1;\n";
	fout << "if (FAILED(Create_EmptyMesh()))\n";
	fout << "{\n";
	fout << "	MSG_BOX(\"Failed to Create_EmptyMesh : CMesh_Cube\");\n";
	fout << "	return E_FAIL;\n";
	fout << "}\n";

	fout << "VTXCOLOR* vertices = nullptr;\n";
	fout << "m_pMesh->LockVertexBuffer(0, (void**)&vertices);\n\n";
	

	for (_uint i = 0; i < vtxSize; i++)
	{
		//Vtx_Vector.push_back(VTXCOLOR(_float3(0.f, 0.f, 0.f), _float3(0.f, 0.f, 0.f), D3DCOLOR_ARGB(255, 0, 0, 0)));
		Vtx_Vector.push_back(vertices[i]);
		fout << "vertices["<<i<<"] = VTXCOLOR(_float3("<< vertices[i].vPosition.x<<", " << vertices[i].vPosition.y <<", "<< vertices[i].vPosition.z << 
			"), _float3(" << vertices[i].vNorm.x << ", " << vertices[i].vNorm.y << ", " << vertices[i].vNorm.z <<
			"), D3DCOLOR_ARGB("<< Diffuse[0]<< ", "<< Diffuse[1] <<", " << Diffuse[2] << ", "<< Diffuse[3] <<"));\n";
	}

	fout << "m_pMesh->UnlockVertexBuffer();\n\n";
	fout << "WORD* indices = 0;\n";
	fout << "m_pMesh->LockIndexBuffer(0, (void**)&indices);\n\n";

	m_pMesh->UnlockVertexBuffer();

	m_pMesh->LockIndexBuffer(0, (void**)&indices);

	Index_Vector.reserve(indexSize);

	for (_uint i = 0; i < indexSize; i++)
	{
		Index_Vector.push_back(indices[i]);
		fout << "indices["<<i<<"] = "<< indices[i] << ";	";
		if (i % 3 == 2)
			fout << "\n";
	}

	fout << "m_pMesh->UnlockIndexBuffer();\n\n";
	fout << "DWORD*	attributeBuffer = 0;\n";
	fout << "m_pMesh->LockAttributeBuffer(0, &attributeBuffer);\n\n";

	fout << "for (int i = 0; i <" << indexSize / 3 << "; ++i)\n";
	fout << "{\n";
	fout << "	attributeBuffer[i] = 0;\n";
	fout << "}\n";
	fout << "m_pMesh->UnlockAttributeBuffer();\n";
	fout << "vector<DWORD> adjacencyBuffer(m_iNumPrimitive*3);\n";
	fout << "m_pMesh->GenerateAdjacency(0.f, &adjacencyBuffer[0]);\n\n";
	fout << "m_pMesh->OptimizeInplace(\n";
	fout << "	D3DXMESHOPT_ATTRSORT |\n";
	fout << "	D3DXMESHOPT_COMPACT |\n";
	fout << "	D3DXMESHOPT_VERTEXCACHE,\n";
	fout << "		&adjacencyBuffer[0],\n";
	fout << "	0, 0, 0\n";
	fout << ");\n\n";
	fout << "return S_OK;\n";


	m_pMesh->UnlockIndexBuffer();
	fout.close();

	return S_OK;
}

HRESULT CMesh_Test::Initialize(void* pArg)
{
    return S_OK;
}

CMesh_Test* CMesh_Test::Create()
{
	CREATE_PIPELINE(CMesh_Test);
}

CComponent* CMesh_Test::Clone(void* pArg)
{
	CLONE_PIPELINE(CMesh_Test);
}

void CMesh_Test::Free()
{
	__super::Free();

	delete this;

}

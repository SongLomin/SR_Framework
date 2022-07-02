#include "Get_Lucky.h"
#include "GameInstance.h"

IMPLEMENT_SINGLETON(Get_Lucky)

void Get_Lucky::Team_EverSpace()
{
	//파싱할 x파일 경로 수정
	D3DXLoadMeshFromX(TEXT("../Bin/Resources/Textures/Terrain/StarShip.x"), D3DXMESH_MANAGED,
		DEVICE, &m_pAdj, &m_pMtrl, &m_pEffectInstances,
		&m_iNumMtrl, &m_pMesh);

	m_dwNumSubsets = 1;

	DWORD fuck = m_pMesh->GetFVF();
	int i = 0;
	//출력될 파일 경로는 Framework\Client\Default의 아래 이름
	ofstream fout("Past_Initialize_Prototype.cpp");
	
	VTXNORMAL* vertices = nullptr;
	DWORD vtxSize = 0;
	vtxSize = m_pMesh->GetNumVertices();
	vector<VTXNORMAL> Vtx_Vector;

	WORD* indices = 0;
	DWORD indexSize = 0;
	indexSize = m_pMesh->GetNumFaces() * 3;
	vector<WORD> Index_Vector;

	//설정하고 싶은 색깔!!!!
	//int Diffuse[4]{ 255, 40, 40, 40 };


	m_pMesh->LockVertexBuffer(0, (void**)&vertices);
	Vtx_Vector.reserve(vtxSize);

	fout << "////////////////////////	사용법	////////////////////////\n";
	fout << "// 1. 메쉬 상속받는 자식 메쉬 만들기\n";
	fout << "// 2. 자식 메쉬의 Initialize_Prototype에 전부 복사 붙여넣기\n";
	fout << "///////////////////////////////////////////////////////////\n\n";

	fout << "m_iNumVertices = " << vtxSize << ";\n";
	fout << "m_iNumPrimitive = " << indexSize / 3 << ";\n";
	fout << "m_dwFVF = VTXNORMAL::FVF;\n\n";
	fout << "m_dwNumSubsets = 1;\n";
	fout << "if (FAILED(Create_EmptyMesh()))\n";
	fout << "{\n";
	fout << "	MSG_BOX(\"Failed to Create_EmptyMesh : CMesh_Cube\");\n";
	fout << "	return E_FAIL;\n";
	fout << "}\n";

	fout << "VTXNORMAL* vertices = nullptr;\n";
	fout << "m_pMesh->LockVertexBuffer(0, (void**)&vertices);\n\n";


	for (_uint i = 0; i < vtxSize; i++)
	{
		//Vtx_Vector.push_back(VTXNORMAL(_float3(0.f, 0.f, 0.f), _float3(0.f, 0.f, 0.f), D3DCOLOR_ARGB(255, 0, 0, 0)));
		Vtx_Vector.push_back(vertices[i]);
		
		fout << fixed;
		fout.precision(2);
		fout << "vertices[" << i << "] = VTXNORMAL(_float3(" << vertices[i].vPosition.x << ", " << vertices[i].vPosition.y << ", " << vertices[i].vPosition.z <<
			"), _float3(" << vertices[i].vNorm.x << ", " << vertices[i].vNorm.y << ", " << vertices[i].vNorm.z <<
			"));\n";
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
		fout << "indices[" << i << "] = " << indices[i] << ";	";
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
}

void Get_Lucky::Free()
{
	delete this;


}

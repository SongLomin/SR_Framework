#include "Mesh_ShinShip.h"
#include "GameInstance.h"

CMesh_ShinShip::CMesh_ShinShip()
{
}

CMesh_ShinShip::CMesh_ShinShip(const CMesh_ShinShip& Prototype)
{
	*this = Prototype;

	if (!m_pMesh)
	{
		return;
	}

	ID3DXMesh* pCloneMesh = nullptr;
	m_pMesh->CloneMeshFVF(m_pMesh->GetOptions(), m_pMesh->GetFVF(), DEVICE, &pCloneMesh);
	m_pMesh = pCloneMesh;
}

HRESULT CMesh_ShinShip::Initialize_Prototype()
{
	m_iNumVertices = 108;
	m_iNumPrimitive = 64;
	m_dwFVF = VTXDEFAULT::FVF;

	m_dwNumSubsets = 1;
	if (FAILED(Create_EmptyMesh()))
	{
		MSG_BOX("Failed to Create_EmptyMesh : CMesh_Cube");
		return E_FAIL;
	}
	VTXDEFAULT* vertices = nullptr;
	m_pMesh->LockVertexBuffer(0, (void**)&vertices);

	vertices[0] = VTXDEFAULT(_float3(2.27, 0.45, -1.08), _float3(0.00, -0.87, 0.49), _float2(0.56, 1.00));
	vertices[1] = VTXDEFAULT(_float3(-2.48, -0.89, -3.46), _float3(0.00, -0.87, 0.49), _float2(0.56, 0.55));
	vertices[2] = VTXDEFAULT(_float3(-2.30, 0.45, -1.06), _float3(0.00, -0.87, 0.49), _float2(0.37, 0.66));
	vertices[3] = VTXDEFAULT(_float3(-2.32, 0.45, 1.15), _float3(0.00, -1.00, 0.00), _float2(0.19, 0.56));
	vertices[4] = VTXDEFAULT(_float3(2.29, 0.45, 1.15), _float3(0.00, -1.00, 0.00), _float2(0.19, 0.17));
	vertices[5] = VTXDEFAULT(_float3(2.27, 0.45, -1.08), _float3(0.00, -1.00, 0.00), _float2(0.00, 0.17));
	vertices[6] = VTXDEFAULT(_float3(-2.30, 0.45, -1.06), _float3(0.00, -1.00, 0.00), _float2(0.00, 0.56));
	vertices[7] = VTXDEFAULT(_float3(-2.46, -0.89, 3.50), _float3(-0.00, -0.87, -0.49), _float2(0.72, 1.00));
	vertices[8] = VTXDEFAULT(_float3(2.29, 0.45, 1.15), _float3(-0.00, -0.87, -0.49), _float2(0.72, 0.56));
	vertices[9] = VTXDEFAULT(_float3(-2.32, 0.45, 1.15), _float3(-0.00, -0.87, -0.49), _float2(0.56, 0.91));
	vertices[10] = VTXDEFAULT(_float3(-2.33, 1.29, -1.06), _float3(-1.00, -0.04, -0.01), _float2(0.81, 0.00));
	vertices[11] = VTXDEFAULT(_float3(-2.32, 1.28, 1.15), _float3(-1.00, -0.04, -0.01), _float2(0.82, 0.19));
	vertices[12] = VTXDEFAULT(_float3(-2.31, 0.45, 1.15), _float3(-1.00, -0.04, -0.01), _float2(0.89, 0.19));
	vertices[13] = VTXDEFAULT(_float3(-2.28, 0.46, -1.07), _float3(-1.00, -0.04, -0.01), _float2(0.89, 0.00));
	vertices[14] = VTXDEFAULT(_float3(-2.32, 1.28, 1.15), _float3(0.00, -0.00, 1.00), _float2(0.98, 1.00));
	vertices[15] = VTXDEFAULT(_float3(2.29, 1.29, 1.15), _float3(0.00, -0.00, 1.00), _float2(0.98, 0.62));
	vertices[16] = VTXDEFAULT(_float3(2.29, 0.45, 1.14), _float3(0.00, -0.00, 1.00), _float2(0.91, 0.62));
	vertices[17] = VTXDEFAULT(_float3(-2.31, 0.45, 1.15), _float3(0.00, -0.00, 1.00), _float2(0.91, 1.00));
	vertices[18] = VTXDEFAULT(_float3(2.29, 1.29, 1.15), _float3(1.00, -0.02, -0.01), _float2(0.81, 0.19));
	vertices[19] = VTXDEFAULT(_float3(2.29, 1.29, -1.06), _float3(1.00, -0.02, -0.01), _float2(0.81, 0.00));
	vertices[20] = VTXDEFAULT(_float3(2.26, 0.45, -1.06), _float3(1.00, -0.02, -0.01), _float2(0.74, 0.00));
	vertices[21] = VTXDEFAULT(_float3(2.29, 0.45, 1.14), _float3(1.00, -0.02, -0.01), _float2(0.74, 0.19));
	vertices[22] = VTXDEFAULT(_float3(2.29, 1.29, -1.06), _float3(0.00, 0.00, -1.00), _float2(0.97, 0.56));
	vertices[23] = VTXDEFAULT(_float3(-2.33, 1.29, -1.06), _float3(0.00, 0.00, -1.00), _float2(0.97, 0.17));
	vertices[24] = VTXDEFAULT(_float3(-2.28, 0.46, -1.07), _float3(0.00, 0.00, -1.00), _float2(0.90, 0.18));
	vertices[25] = VTXDEFAULT(_float3(2.26, 0.45, -1.06), _float3(0.00, 0.00, -1.00), _float2(0.90, 0.55));
	vertices[26] = VTXDEFAULT(_float3(-2.28, 0.46, -1.07), _float3(-0.00, -1.00, -0.00), _float2(0.56, 0.55));
	vertices[27] = VTXDEFAULT(_float3(-2.31, 0.45, 1.15), _float3(-0.00, -1.00, -0.00), _float2(0.74, 0.56));
	vertices[28] = VTXDEFAULT(_float3(2.29, 0.45, 1.14), _float3(-0.00, -1.00, -0.00), _float2(0.74, 0.17));
	vertices[29] = VTXDEFAULT(_float3(2.26, 0.45, -1.06), _float3(-0.00, -1.00, -0.00), _float2(0.56, 0.17));
	vertices[30] = VTXDEFAULT(_float3(2.29, 1.29, -1.06), _float3(-0.00, 1.00, 0.00), _float2(0.91, 0.61));
	vertices[31] = VTXDEFAULT(_float3(2.29, 1.29, 1.15), _float3(-0.00, 1.00, 0.00), _float2(0.72, 0.62));
	vertices[32] = VTXDEFAULT(_float3(-2.32, 1.28, 1.15), _float3(-0.00, 1.00, 0.00), _float2(0.72, 1.00));
	vertices[33] = VTXDEFAULT(_float3(-2.33, 1.29, -1.06), _float3(-0.00, 1.00, 0.00), _float2(0.91, 0.99));
	vertices[34] = VTXDEFAULT(_float3(2.29, 1.29, -1.06), _float3(0.44, 0.90, -0.00), _float2(0.90, 0.37));
	vertices[35] = VTXDEFAULT(_float3(4.00, 0.46, -0.69), _float3(0.44, 0.90, -0.00), _float2(0.74, 0.41));
	vertices[36] = VTXDEFAULT(_float3(4.01, 0.46, 0.76), _float3(0.44, 0.90, -0.00), _float2(0.74, 0.53));
	vertices[37] = VTXDEFAULT(_float3(2.29, 1.29, 1.15), _float3(0.44, 0.90, -0.00), _float2(0.90, 0.56));
	vertices[38] = VTXDEFAULT(_float3(2.29, 0.45, 1.15), _float3(0.01, -1.00, -0.00), _float2(0.89, 0.19));
	vertices[39] = VTXDEFAULT(_float3(4.01, 0.46, 0.76), _float3(0.01, -1.00, -0.00), _float2(0.74, 0.22));
	vertices[40] = VTXDEFAULT(_float3(4.00, 0.46, -0.69), _float3(0.01, -1.00, -0.00), _float2(0.74, 0.34));
	vertices[41] = VTXDEFAULT(_float3(2.26, 0.45, -1.06), _float3(0.01, -1.00, -0.00), _float2(0.89, 0.37));
	vertices[42] = VTXDEFAULT(_float3(4.01, 0.46, 0.76), _float3(0.22, 0.01, 0.97), _float2(0.07, 0.17));
	vertices[43] = VTXDEFAULT(_float3(2.29, 0.45, 1.15), _float3(0.22, 0.01, 0.97), _float2(0.07, 0.02));
	vertices[44] = VTXDEFAULT(_float3(2.29, 1.29, 1.15), _float3(0.22, 0.01, 0.97), _float2(0.00, 0.02));
	vertices[45] = VTXDEFAULT(_float3(2.29, 1.29, -1.06), _float3(0.22, 0.01, -0.98), _float2(0.96, 0.01));
	vertices[46] = VTXDEFAULT(_float3(2.27, 0.45, -1.08), _float3(0.22, 0.01, -0.98), _float2(0.90, 0.04));
	vertices[47] = VTXDEFAULT(_float3(4.00, 0.46, -0.69), _float3(0.22, 0.01, -0.98), _float2(0.96, 0.17));
	vertices[48] = VTXDEFAULT(_float3(-2.46, -0.89, 3.50), _float3(0.00, 0.85, 0.53), _float2(0.19, 0.56));
	vertices[49] = VTXDEFAULT(_float3(-2.32, 0.61, 1.14), _float3(0.00, 0.85, 0.53), _float2(0.00, 0.67));
	vertices[50] = VTXDEFAULT(_float3(2.29, 0.61, 1.14), _float3(0.00, 0.85, 0.53), _float2(0.19, 1.00));
	vertices[51] = VTXDEFAULT(_float3(-2.46, -0.89, 3.50), _float3(0.43, 0.06, 0.90), _float2(0.98, 0.56));
	vertices[52] = VTXDEFAULT(_float3(2.29, 0.61, 1.14), _float3(0.43, 0.06, 0.90), _float2(0.98, 0.11));
	vertices[53] = VTXDEFAULT(_float3(2.29, 0.45, 1.15), _float3(0.43, 0.06, 0.90), _float2(0.97, 0.11));
	vertices[54] = VTXDEFAULT(_float3(-2.32, 0.45, 1.15), _float3(-1.00, 0.01, -0.05), _float2(0.99, 0.99));
	vertices[55] = VTXDEFAULT(_float3(-2.32, 0.61, 1.14), _float3(-1.00, 0.01, -0.05), _float2(1.00, 1.00));
	vertices[56] = VTXDEFAULT(_float3(-2.46, -0.89, 3.50), _float3(-1.00, 0.01, -0.05), _float2(1.00, 0.76));
	vertices[57] = VTXDEFAULT(_float3(-2.48, -0.89, -3.46), _float3(-0.00, -0.85, 0.53), _float2(0.37, 0.55));
	vertices[58] = VTXDEFAULT(_float3(-2.29, 0.63, -1.05), _float3(-0.00, -0.85, 0.53), _float2(0.19, 0.66));
	vertices[59] = VTXDEFAULT(_float3(2.26, 0.61, -1.06), _float3(-0.00, -0.85, 0.53), _float2(0.37, 1.00));
	vertices[60] = VTXDEFAULT(_float3(-2.30, 0.45, -1.06), _float3(-1.00, 0.07, 0.04), _float2(0.98, 0.77));
	vertices[61] = VTXDEFAULT(_float3(-2.48, -0.89, -3.46), _float3(-1.00, 0.07, 0.04), _float2(0.99, 1.00));
	vertices[62] = VTXDEFAULT(_float3(-2.29, 0.63, -1.05), _float3(-1.00, 0.07, 0.04), _float2(0.99, 0.76));
	vertices[63] = VTXDEFAULT(_float3(-2.48, -0.89, -3.46), _float3(0.42, 0.12, -0.90), _float2(1.00, 0.11));
	vertices[64] = VTXDEFAULT(_float3(2.27, 0.45, -1.08), _float3(0.42, 0.12, -0.90), _float2(0.98, 0.55));
	vertices[65] = VTXDEFAULT(_float3(2.26, 0.61, -1.06), _float3(0.42, 0.12, -0.90), _float2(1.00, 0.56));
	vertices[66] = VTXDEFAULT(_float3(-2.62, 3.37, 0.01), _float3(0.00, -0.10, 0.99), _float2(0.19, 0.14));
	vertices[67] = VTXDEFAULT(_float3(-1.95, 3.37, -0.00), _float3(0.00, -0.10, 0.99), _float2(0.19, 0.19));
	vertices[68] = VTXDEFAULT(_float3(2.29, 1.29, -0.00), _float3(0.00, -0.10, 0.99), _float2(0.37, 0.55));
	vertices[69] = VTXDEFAULT(_float3(-2.59, 1.29, -0.24), _float3(0.00, -0.10, 0.99), _float2(0.37, 0.14));
	vertices[70] = VTXDEFAULT(_float3(-2.60, 1.29, -0.01), _float3(0.00, -0.10, 0.99), _float2(0.37, 0.14));
	vertices[71] = VTXDEFAULT(_float3(2.29, 1.29, -0.00), _float3(0.00, -0.11, -0.99), _float2(0.55, 0.14));
	vertices[72] = VTXDEFAULT(_float3(-1.95, 3.37, -0.00), _float3(0.00, -0.11, -0.99), _float2(0.37, 0.49));
	vertices[73] = VTXDEFAULT(_float3(-2.62, 3.37, 0.01), _float3(0.00, -0.11, -0.99), _float2(0.37, 0.55));
	vertices[74] = VTXDEFAULT(_float3(-2.60, 1.29, -0.01), _float3(0.00, -0.11, -0.99), _float2(0.55, 0.54));
	vertices[75] = VTXDEFAULT(_float3(-2.59, 1.28, 0.26), _float3(0.00, -0.11, -0.99), _float2(0.55, 0.54));
	vertices[76] = VTXDEFAULT(_float3(-2.36, 1.21, -0.12), _float3(-1.00, 0.00, -0.01), _float2(0.13, 0.11));
	vertices[77] = VTXDEFAULT(_float3(-2.36, 1.22, 0.04), _float3(-1.00, 0.00, -0.01), _float2(0.13, 0.10));
	vertices[78] = VTXDEFAULT(_float3(-2.36, 1.21, 0.21), _float3(-1.00, 0.00, -0.01), _float2(0.13, 0.08));
	vertices[79] = VTXDEFAULT(_float3(-2.36, 1.19, 0.36), _float3(-1.00, 0.00, -0.01), _float2(0.13, 0.07));
	vertices[80] = VTXDEFAULT(_float3(-2.37, 1.16, 0.51), _float3(-1.00, 0.00, -0.01), _float2(0.12, 0.06));
	vertices[81] = VTXDEFAULT(_float3(-2.37, 1.11, 0.63), _float3(-1.00, 0.00, -0.01), _float2(0.12, 0.05));
	vertices[82] = VTXDEFAULT(_float3(-2.37, 1.06, 0.74), _float3(-1.00, 0.00, -0.01), _float2(0.11, 0.04));
	vertices[83] = VTXDEFAULT(_float3(-2.37, 1.00, 0.81), _float3(-1.00, 0.00, -0.01), _float2(0.11, 0.03));
	vertices[84] = VTXDEFAULT(_float3(-2.37, 0.94, 0.86), _float3(-1.00, 0.00, -0.01), _float2(0.10, 0.03));
	vertices[85] = VTXDEFAULT(_float3(-2.37, 0.87, 0.88), _float3(-1.00, 0.00, -0.01), _float2(0.10, 0.03));
	vertices[86] = VTXDEFAULT(_float3(-2.37, 0.80, 0.86), _float3(-1.00, 0.00, -0.01), _float2(0.09, 0.03));
	vertices[87] = VTXDEFAULT(_float3(-2.37, 0.74, 0.81), _float3(-1.00, 0.00, -0.01), _float2(0.09, 0.03));
	vertices[88] = VTXDEFAULT(_float3(-2.37, 0.68, 0.73), _float3(-1.00, 0.00, -0.01), _float2(0.08, 0.04));
	vertices[89] = VTXDEFAULT(_float3(-2.37, 0.63, 0.63), _float3(-1.00, 0.00, -0.01), _float2(0.08, 0.05));
	vertices[90] = VTXDEFAULT(_float3(-2.37, 0.59, 0.50), _float3(-1.00, 0.00, -0.01), _float2(0.08, 0.06));
	vertices[91] = VTXDEFAULT(_float3(-2.36, 0.56, 0.35), _float3(-1.00, 0.00, -0.01), _float2(0.07, 0.07));
	vertices[92] = VTXDEFAULT(_float3(-2.36, 0.54, 0.20), _float3(-1.00, 0.00, -0.01), _float2(0.07, 0.08));
	vertices[93] = VTXDEFAULT(_float3(-2.36, 0.53, 0.03), _float3(-1.00, 0.00, -0.01), _float2(0.07, 0.10));
	vertices[94] = VTXDEFAULT(_float3(-2.36, 0.54, -0.13), _float3(-1.00, 0.00, -0.01), _float2(0.07, 0.11));
	vertices[95] = VTXDEFAULT(_float3(-2.36, 0.56, -0.29), _float3(-1.00, 0.00, -0.01), _float2(0.08, 0.13));
	vertices[96] = VTXDEFAULT(_float3(-2.36, 0.59, -0.43), _float3(-1.00, 0.00, -0.01), _float2(0.08, 0.14));
	vertices[97] = VTXDEFAULT(_float3(-2.35, 0.64, -0.56), _float3(-1.00, 0.00, -0.01), _float2(0.08, 0.15));
	vertices[98] = VTXDEFAULT(_float3(-2.35, 0.69, -0.66), _float3(-1.00, 0.00, -0.01), _float2(0.09, 0.16));
	vertices[99] = VTXDEFAULT(_float3(-2.35, 0.75, -0.74), _float3(-1.00, 0.00, -0.01), _float2(0.09, 0.16));
	vertices[100] = VTXDEFAULT(_float3(-2.35, 0.82, -0.79), _float3(-1.00, 0.00, -0.01), _float2(0.10, 0.17));
	vertices[101] = VTXDEFAULT(_float3(-2.35, 0.88, -0.80), _float3(-1.00, 0.00, -0.01), _float2(0.10, 0.17));
	vertices[102] = VTXDEFAULT(_float3(-2.35, 0.95, -0.79), _float3(-1.00, 0.00, -0.01), _float2(0.11, 0.17));
	vertices[103] = VTXDEFAULT(_float3(-2.35, 1.01, -0.74), _float3(-1.00, 0.00, -0.01), _float2(0.11, 0.16));
	vertices[104] = VTXDEFAULT(_float3(-2.35, 1.07, -0.66), _float3(-1.00, 0.00, -0.01), _float2(0.12, 0.16));
	vertices[105] = VTXDEFAULT(_float3(-2.35, 1.12, -0.55), _float3(-1.00, 0.00, -0.01), _float2(0.12, 0.15));
	vertices[106] = VTXDEFAULT(_float3(-2.36, 1.17, -0.43), _float3(-1.00, 0.00, -0.01), _float2(0.13, 0.14));
	vertices[107] = VTXDEFAULT(_float3(-2.36, 1.20, -0.28), _float3(-1.00, 0.00, -0.01), _float2(0.13, 0.12));
	
	for (int i = 0; i < m_iNumVertices; i++)
	{
		vertices[i].vPosition = CMath_Utillity::Rotate_Vec3(_float3(0.f, -D3DXToRadian(90.f), 0.f), vertices[i].vPosition);
		vertices[i].vNorm = CMath_Utillity::Rotate_Vec3(_float3(0.f, -D3DXToRadian(90.f), 0.f), vertices[i].vNorm);
	}
	
	m_pMesh->UnlockVertexBuffer();

	WORD* indices = 0;
	m_pMesh->LockIndexBuffer(0, (void**)&indices);

	indices[0] = 2;	indices[1] = 1;	indices[2] = 0;
	indices[3] = 6;	indices[4] = 5;	indices[5] = 4;
	indices[6] = 6;	indices[7] = 4;	indices[8] = 3;
	indices[9] = 9;	indices[10] = 8;	indices[11] = 7;
	indices[12] = 13;	indices[13] = 12;	indices[14] = 11;
	indices[15] = 13;	indices[16] = 11;	indices[17] = 10;
	indices[18] = 17;	indices[19] = 16;	indices[20] = 15;
	indices[21] = 17;	indices[22] = 15;	indices[23] = 14;
	indices[24] = 21;	indices[25] = 20;	indices[26] = 19;
	indices[27] = 21;	indices[28] = 19;	indices[29] = 18;
	indices[30] = 25;	indices[31] = 24;	indices[32] = 23;
	indices[33] = 25;	indices[34] = 23;	indices[35] = 22;
	indices[36] = 29;	indices[37] = 28;	indices[38] = 27;
	indices[39] = 29;	indices[40] = 27;	indices[41] = 26;
	indices[42] = 33;	indices[43] = 32;	indices[44] = 31;
	indices[45] = 33;	indices[46] = 31;	indices[47] = 30;
	indices[48] = 37;	indices[49] = 36;	indices[50] = 35;
	indices[51] = 37;	indices[52] = 35;	indices[53] = 34;
	indices[54] = 41;	indices[55] = 40;	indices[56] = 39;
	indices[57] = 41;	indices[58] = 39;	indices[59] = 38;
	indices[60] = 44;	indices[61] = 43;	indices[62] = 42;
	indices[63] = 47;	indices[64] = 46;	indices[65] = 45;
	indices[66] = 50;	indices[67] = 49;	indices[68] = 48;
	indices[69] = 53;	indices[70] = 52;	indices[71] = 51;
	indices[72] = 56;	indices[73] = 55;	indices[74] = 54;
	indices[75] = 59;	indices[76] = 58;	indices[77] = 57;
	indices[78] = 62;	indices[79] = 61;	indices[80] = 60;
	indices[81] = 65;	indices[82] = 64;	indices[83] = 63;
	indices[84] = 70;	indices[85] = 69;	indices[86] = 68;
	indices[87] = 70;	indices[88] = 68;	indices[89] = 67;
	indices[90] = 70;	indices[91] = 67;	indices[92] = 66;
	indices[93] = 75;	indices[94] = 74;	indices[95] = 73;
	indices[96] = 75;	indices[97] = 73;	indices[98] = 72;
	indices[99] = 75;	indices[100] = 72;	indices[101] = 71;
	indices[102] = 107;	indices[103] = 106;	indices[104] = 105;
	indices[105] = 107;	indices[106] = 105;	indices[107] = 104;
	indices[108] = 107;	indices[109] = 104;	indices[110] = 103;
	indices[111] = 107;	indices[112] = 103;	indices[113] = 102;
	indices[114] = 107;	indices[115] = 102;	indices[116] = 101;
	indices[117] = 107;	indices[118] = 101;	indices[119] = 100;
	indices[120] = 107;	indices[121] = 100;	indices[122] = 99;
	indices[123] = 107;	indices[124] = 99;	indices[125] = 98;
	indices[126] = 107;	indices[127] = 98;	indices[128] = 97;
	indices[129] = 107;	indices[130] = 97;	indices[131] = 96;
	indices[132] = 107;	indices[133] = 96;	indices[134] = 95;
	indices[135] = 107;	indices[136] = 95;	indices[137] = 94;
	indices[138] = 107;	indices[139] = 94;	indices[140] = 93;
	indices[141] = 107;	indices[142] = 93;	indices[143] = 92;
	indices[144] = 107;	indices[145] = 92;	indices[146] = 91;
	indices[147] = 107;	indices[148] = 91;	indices[149] = 90;
	indices[150] = 107;	indices[151] = 90;	indices[152] = 89;
	indices[153] = 107;	indices[154] = 89;	indices[155] = 88;
	indices[156] = 107;	indices[157] = 88;	indices[158] = 87;
	indices[159] = 107;	indices[160] = 87;	indices[161] = 86;
	indices[162] = 107;	indices[163] = 86;	indices[164] = 85;
	indices[165] = 107;	indices[166] = 85;	indices[167] = 84;
	indices[168] = 107;	indices[169] = 84;	indices[170] = 83;
	indices[171] = 107;	indices[172] = 83;	indices[173] = 82;
	indices[174] = 107;	indices[175] = 82;	indices[176] = 81;
	indices[177] = 107;	indices[178] = 81;	indices[179] = 80;
	indices[180] = 107;	indices[181] = 80;	indices[182] = 79;
	indices[183] = 107;	indices[184] = 79;	indices[185] = 78;
	indices[186] = 107;	indices[187] = 78;	indices[188] = 77;
	indices[189] = 107;	indices[190] = 77;	indices[191] = 76;
	m_pMesh->UnlockIndexBuffer();

	DWORD* attributeBuffer = 0;
	m_pMesh->LockAttributeBuffer(0, &attributeBuffer);

	for (int i = 0; i < 64; ++i)
	{
		attributeBuffer[i] = 0;
	}
	m_pMesh->UnlockAttributeBuffer();
	vector<DWORD> adjacencyBuffer(m_iNumPrimitive * 3);
	m_pMesh->GenerateAdjacency(0.f, &adjacencyBuffer[0]);

	m_pMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&adjacencyBuffer[0],
		0, 0, 0
	);

	return S_OK;

}

HRESULT CMesh_ShinShip::Initialize(void* pArg)
{
	return S_OK;
}

HRESULT CMesh_ShinShip::Render_Mesh()
{
	DEVICE->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL);
	m_pMesh->DrawSubset(0);

	return S_OK;
}

CMesh_ShinShip* CMesh_ShinShip::Create()
{
	CREATE_PIPELINE(CMesh_ShinShip);
}

CComponent* CMesh_ShinShip::Clone(void* pArg)
{
	CLONE_PIPELINE(CMesh_ShinShip);
}

void CMesh_ShinShip::Free()
{
	__super::Free();

	delete this;
}
